#include "functions.h"


void setF(CvMat *F, CouplePoints ps);//F中ps区域置1
void setR(CvMat *R, CouplePoints ps);//R中ps对角置1,2或者置3（单独点）
void setP(vector<GrayLevel> &P, IplImage *img, CouplePoints ps);//ps区域四角像素值加到P

bool canF(CvMat *F, CouplePoints ps);//判断R中[x,y]点是否已经用过


/************************************************************************/
/* 
	高宽比例：默认值NO_LIMIT，即没有比例限制
	方向优先：默认值ROW_FIRST，即行优先
*/
/************************************************************************/
void RNAMencoding(IplImage *img, double epsilon, vector<GrayLevel> &P, vector<char> &Q, vector<CouplePoints> &blks, int &frag_num, int HWratio, int DIRpriority)
{
	CvMat *R = cvCreateMat(img->height, img->width, CV_32FC1);
	CvMat *F = cvCreateMat(img->height, img->width, CV_32FC1);

	cvmSetZero(R);
	cvmSetZero(F);

	int r, c;
	int x1, y1, x2, y2;
	uchar *ptr;
	CouplePoints ps;


	for(r = 0; r < F->rows; r++)
	{
		ptr = (uchar *)(F->data.ptr + r*F->step);

		for(c = 0; c < F->cols; c++)
		{
			x1 = c;
			y1 = r;

			if(ptr[x1] != 0)
				continue;

			x2 = x1;
			y2 = y1;

			setPS(ps, x1, y1, x2, y2);
			if(DIRpriority == DIA_FIRST)//1.对角线搜索
			{
				while(x2<img->width && y2<img->height && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
				{
					x2++;
					y2++;
					setPS(ps, x1, y1, x2, y2);
				}
				x2--;
				y2--;

				int temp_x2 = x2 + 1;
				int temp_y2 = y2 + 1;


				//对角线方向停止，横向继续
				setPS(ps, x1, y1, temp_x2, y2);
				while(temp_x2<img->width && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
				{
					temp_x2++;
					setPS(ps, x1, y1, temp_x2, y2);
				}
				temp_x2--;
				//对角线方向停止，纵向继续
				setPS(ps, x1, y1, x2, temp_y2);
				while(temp_y2<img->height && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
				{
					temp_y2++;
					setPS(ps, x1, y1, x2, temp_y2);
				}
				temp_y2--;

				if(temp_x2 - x2 > temp_y2 - y2)//[对角线 + 横向] 更大
				{
					x2 = temp_x2;
				}
				else//[对角线 + 纵向] 更大
				{
					y2 = temp_y2;
				}
			}
			else
			{

				if(DIRpriority == ROW_FIRST)//行优先
				{
					while(x2<img->width && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
					{
						x2++;
						setPS(ps, x1, y1, x2, y2);
					}
					x2--;
					setPS(ps, x1, y1, x2, y2);
					while(y2<img->height && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
					{
						y2++;
						setPS(ps, x1, y1, x2, y2);
					}
					y2--;
				}
				else//列优先
				{
					while(y2<img->height && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
					{
						y2++;
						setPS(ps, x1, y1, x2, y2);
					}
					y2--;
					setPS(ps, x1, y1, x2, y2);
					while(x2<img->width && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
					{
						x2++;
						setPS(ps, x1, y1, x2, y2);
					}
					x2--;
				}

			}

			if(HWratio != NO_LIMIT)//有长宽比例限制
			{
				if( (x2-x1+1)/(y2-y1+1) > HWratio )
				{
					//宽度过大
					x2 = (y2-y1+1)*HWratio + x1-1;
				}
				else
				{
					if( (y2-y1+1)/(x2-x1+1) >HWratio )
					{
						//长度过大
						y2 = (x2-x1+1)*HWratio + y1-1;
					}
				}
			}

			setPS(ps, x1, y1, x2, y2);

			blks.push_back(ps);
			setF(F, ps);
			setR(R, ps);
			setP(P, img, ps);
		}
	}

	frag_num = calFragNum(P, R);

	switch (METHOD)
	{
	case METHOD_NAM:
		CompressCoordinate(R, Q);//坐标矩阵压缩
		break;
	case METHOD_FRAG_NAM:
		Fragment_CompressCoordinate(R, Q, frag_num);//分段编码压缩
		break;
	case METHOD_AC_NAM:
		AC_CompressCoordinate(R, _nsym, _count);
		break;
	case METHOD_AC_FRAG_NAM:
		AC_Fragment_CompressCoordinate(R, _nsym, _count, frag_num);
		break;
	}

	
	//
	//
	//
	//copyMat(cm1, R);
	//dispIline(R, 484);
}


void setF(CvMat *F, CouplePoints ps)
{
	for(int r = ps.y1; r <= ps.y2; r++)
	{
		uchar *ptr = (uchar *)(F->data.ptr + r*F->step);
		for(int c = ps.x1; c <= ps.x2; c++)
		{
			ptr[c] = 1;
		}
	}
}

void setR(CvMat *R, CouplePoints ps)
{
	uchar *ptr = (uchar *)(R->data.ptr + ps.y1*R->step);
	if(ps.x1 == ps.x2 && ps.y1 == ps.y2)
	{
		//单独点
		ptr[ps.x1] = 3;
	}
	else
	{
		ptr[ps.x1] = 1;
		ptr = (uchar *)(R->data.ptr + ps.y2*R->step);
		ptr[ps.x2] = 2;
	}
}

void setP(vector<GrayLevel> &P, IplImage *img, CouplePoints ps)
{
	GrayLevel gl;
	uchar *ptr = (uchar *)(img->imageData + ps.y1 * img->widthStep);

	if(ps.x1 == ps.x2 && ps.y1 == ps.y2)//单独点
	{
		gl.g1 = ptr[ps.x1];
		gl.g2 = -1;
		gl.g3 = -1;
		gl.g4 = -1;
	}
	else if(ps.x1 == ps.x2)//单列
	{
		gl.g1 = ptr[ps.x1];
		ptr = (uchar *)(img->imageData + ps.y2 * img->widthStep);
		gl.g4 = ptr[ps.x2];
		gl.g2 = -1;
		gl.g3 = -1;
	}
	else if(ps.y1 == ps.y2)//单行
	{
		gl.g1 = ptr[ps.x1];
		gl.g4 = ptr[ps.x2];
		gl.g2 = -1;
		gl.g3 = -1;
	}
	else//普通块
	{
		gl.g1 = ptr[ps.x1];
		gl.g2 = ptr[ps.x2];
		ptr = (uchar *)(img->imageData + ps.y2 * img->widthStep);
		gl.g3 = ptr[ps.x1];
		gl.g4 = ptr[ps.x2];
	}

	P.push_back(gl);
}


bool canF(CvMat *F, CouplePoints ps)
{
	uchar *ptr = (uchar *)(F->data.ptr + ps.y1*F->step);
	
	if(ptr[ps.x2] == 1)
		return false;
	ptr = (uchar *)(F->data.ptr + ps.y2*F->step);
	if(ptr[ps.x1] == 1)
		return false;
	if(ptr[ps.x2] == 1)
		return false;

	return true;
}
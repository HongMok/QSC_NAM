#include "functions.h"


void setF(CvMat *F, CouplePoints ps);//F��ps������1
void setR(CvMat *R, CouplePoints ps);//R��ps�Խ���1,2������3�������㣩
void setP(vector<GrayLevel> &P, IplImage *img, CouplePoints ps);//ps�����Ľ�����ֵ�ӵ�P

bool canF(CvMat *F, CouplePoints ps);//�ж�R��[x,y]���Ƿ��Ѿ��ù�


/************************************************************************/
/* 
	�߿������Ĭ��ֵNO_LIMIT����û�б�������
	�������ȣ�Ĭ��ֵROW_FIRST����������
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
			if(DIRpriority == DIA_FIRST)//1.�Խ�������
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


				//�Խ��߷���ֹͣ���������
				setPS(ps, x1, y1, temp_x2, y2);
				while(temp_x2<img->width && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
				{
					temp_x2++;
					setPS(ps, x1, y1, temp_x2, y2);
				}
				temp_x2--;
				//�Խ��߷���ֹͣ���������
				setPS(ps, x1, y1, x2, temp_y2);
				while(temp_y2<img->height && IsHomogeneousBlock(img, ps, epsilon) == true && canF(F, ps))
				{
					temp_y2++;
					setPS(ps, x1, y1, x2, temp_y2);
				}
				temp_y2--;

				if(temp_x2 - x2 > temp_y2 - y2)//[�Խ��� + ����] ����
				{
					x2 = temp_x2;
				}
				else//[�Խ��� + ����] ����
				{
					y2 = temp_y2;
				}
			}
			else
			{

				if(DIRpriority == ROW_FIRST)//������
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
				else//������
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

			if(HWratio != NO_LIMIT)//�г����������
			{
				if( (x2-x1+1)/(y2-y1+1) > HWratio )
				{
					//��ȹ���
					x2 = (y2-y1+1)*HWratio + x1-1;
				}
				else
				{
					if( (y2-y1+1)/(x2-x1+1) >HWratio )
					{
						//���ȹ���
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
		CompressCoordinate(R, Q);//�������ѹ��
		break;
	case METHOD_FRAG_NAM:
		Fragment_CompressCoordinate(R, Q, frag_num);//�ֶα���ѹ��
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
		//������
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

	if(ps.x1 == ps.x2 && ps.y1 == ps.y2)//������
	{
		gl.g1 = ptr[ps.x1];
		gl.g2 = -1;
		gl.g3 = -1;
		gl.g4 = -1;
	}
	else if(ps.x1 == ps.x2)//����
	{
		gl.g1 = ptr[ps.x1];
		ptr = (uchar *)(img->imageData + ps.y2 * img->widthStep);
		gl.g4 = ptr[ps.x2];
		gl.g2 = -1;
		gl.g3 = -1;
	}
	else if(ps.y1 == ps.y2)//����
	{
		gl.g1 = ptr[ps.x1];
		gl.g4 = ptr[ps.x2];
		gl.g2 = -1;
		gl.g3 = -1;
	}
	else//��ͨ��
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
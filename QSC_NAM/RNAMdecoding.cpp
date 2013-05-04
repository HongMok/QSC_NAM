#include "functions.h"


void addBlock(CouplePoints ps, CvMat *R, vector<CouplePoints> &blks);
bool canR(CvMat *R, int x, int y);

void RNAMdecoding(IplImage *img, double epsilon, vector<GrayLevel> &P, vector<char> &Q, int &frag_num)
{
	CvMat *R = cvCreateMat(img->height, img->width, CV_32FC1);
	vector<CouplePoints> blks;

	switch (METHOD)
	{
	case METHOD_NAM:
		DecompressCoordinate(R, Q);
		break;
	case METHOD_FRAG_NAM:
		Fragment_DecompressCoordinate(R, Q, frag_num);//分段编码压缩
		break;
	case METHOD_AC_NAM:
		AC_DecompressCoordinate(R, _nsym, _count);
		break;
	case METHOD_AC_FRAG_NAM:
		AC_Fragment_DecompressCoordinate(R, _nsym, _count, frag_num);
		break;
	}

	//DecompressCoordinate(R, Q);
	//Fragment_DecompressCoordinate(R, Q, frag_num);//分段编码压缩
	//AC_Fragment_DecompressCoordinate(R, _bit_len, _count, frag_num);
	//AC_DecompressCoordinate(R, _bit_len, _count);
	//cout<<isSameMat(cm1, R);
	//copyMat(R, cm1);

	uchar *ptr;
	int x1, y1, x2, y2;
	CouplePoints ps;
	int t;
	for(int r = 0; r < R->rows; r++)
	{
		ptr = (uchar *)(R->data.ptr + r * R->step);
		for(int c = 0; c < R->cols; c++)
		{
			t = (int)ptr[c];
			if((int)ptr[c] != 1 && (int)ptr[c] != 3)//非块起点
				continue;

			x1 = c;
			y1 = r;
			x2 = x1;
			y2 = y1;

			if((int)ptr[c] == 3)//单独点
			{
				setPS(ps, x1, y1, x2, y2);
				addBlock(ps, R, blks);
			}

			else if((int)ptr[c] == 1)//普通块
			{
				do 
				{
					x2++;
				} while (x2 < img->width && canR(R, x2, y2));
				t= (int)ptr[x2];
				if((int)ptr[x2] == 2)//单行
				{
					setPS(ps, x1, y1, x2, y2);
					addBlock(ps, R, blks);
					continue;
				}
				else
				{
					x2--;
					do 
					{
						y2++;
					} while (y2 < img->height && canR(R, x2, y2));
					setPS(ps, x1, y1, x2, y2);
					addBlock(ps, R, blks);
				}
			}
		}
	}


	//ShowSegmentation(img, blks);
	RefineImage(img, blks, P);
}



void addBlock(CouplePoints ps, CvMat *R, vector<CouplePoints> &blks)
{
	uchar *ptr;
	for(int r = ps.y1; r <= ps.y2; r++)
	{
		ptr = (uchar *)(R->data.ptr + r*R->step);
		for(int c = ps.x1; c <= ps.x2; c++)
		{
			ptr[c] = 9;//置为已用
		}
	}

	blks.push_back(ps);
}


bool canR(CvMat *R, int x, int y)
{
	uchar *ptr = (uchar *)(R->data.ptr + y * R->step);
	if(ptr[x] == 0)
		return true;
	else
		return false;
}
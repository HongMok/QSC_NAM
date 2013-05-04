#include "functions.h"


void refine(IplImage *img, CouplePoints ps, GrayLevel gl);//块上色


void RefineImage(IplImage *img, vector<CouplePoints> &blks, vector<GrayLevel> &P)
{
	for(int i = 0; i < blks.size(); i++)
	{
		refine(img, blks[i], P[i]);
	}
}


void refine(IplImage *img, CouplePoints ps, GrayLevel gl)
{
	int x1 = ps.x1;
	int y1 = ps.y1;
	int x2 = ps.x2;
	int y2 = ps.y2;

	int g1 = gl.g1;
	int g2 = gl.g2;
	int g3 = gl.g3;
	int g4 = gl.g4;
	
	uchar *ptr = (uchar *)img->imageData + y1 * img->widthStep;
	int x, y;
	double r1, r2;
	double g5, g6, gest;

	if(x1 == x2 && y1 == y2)//单独点
	{
		ptr[x1] = g1;
	}
	else if(x1 == x2)//单列
	{
		for(y = y1; y <= y2; y++)
		{
			ptr = (uchar *)img->imageData + y * img->widthStep;
			r1 = (double)(y-y1)/(y2-y1);
			gest = g1 + (g4 - g1) * r1;
			ptr[x1] = gest;
		}
	}
	else if(y1 == y2)//单行
	{
		for(x = x1; x <= x2; x++)
		{
			r2 = (double)(x-x1)/(x2-x1);
			gest = g1 + (g4 - g1) * r2;
			ptr[x] = gest;
		}
	}
	else//普通块
	{
		for(y = y1; y <= y2; y++)
		{
			ptr = (uchar *)img->imageData + y * img->widthStep;
			for(x = x1; x <= x2; x++)
			{
				r1 = (double)(y-y1)/(y2-y1);
				r2 = (double)(x-x1)/(x2-x1);
				g5 = g1 + (g2 - g1) * r2;
				g6 = g3 + (g4 - g3) * r2;
				gest = g5 + (g6 - g5) * r1;
				ptr[x] = gest;
			}
		}
	}
}
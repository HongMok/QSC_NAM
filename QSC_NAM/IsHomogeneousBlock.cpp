#include "functions.h"


/************************************************************************/
/* 
	IsHomogeneousBlock	--	判断是否为同类块
	epslison:double		--	判断筏值
*/
/************************************************************************/
bool IsHomogeneousBlock(IplImage *img, CouplePoints ps, double epsilon)
{
	uchar *ptrtemp;
	uchar *ptr;
	double g;
	double r1, r2;
	uchar g1, g2, g3, g4;
	double g5, g6, gest;
	int x, y;
	int x1 = ps.x1;
	int y1 = ps.y1;
	int x2 = ps.x2;
	int y2 = ps.y2;

	if(x1 < x2 && y1 < y2)
	{
		ptrtemp = (uchar *)img->imageData + img->widthStep * y1;
		g1 = ptrtemp[x1];
		g2 = ptrtemp[x2];
		ptrtemp = (uchar *)img->imageData + img->widthStep * y2;
		g3 = ptrtemp[x1];
		g4 = ptrtemp[x2];

		for(y = y1; y <= y2; y++)
		{
			ptr = (uchar *)img->imageData + img->widthStep * y;
			for(x = x1; x <= x2; x++)
			{
				g = (double)ptr[x];
				r1 = (double)(y - y1)/(y2 - y1);
				r2 = (double)(x - x1)/(x2 - x1);

				g5 = (double)g1 + (g2 - g1) * r2;
				g6 = (double)g3 + (g4 - g3) * r2;
				gest = g5 + (g6 - g5) * r1;

				if(g-gest > epsilon || gest - g > epsilon)
					return false;
			}
		}
	}
	else if(x1 < x2 && y1 == y2)//单行
	{
		ptrtemp = (uchar *)img->imageData + img->widthStep * y1;
		g1 = ptrtemp[x1];
		g2 = ptrtemp[x2];
		for(x = x1; x <= x2; x++)
		{
			r2 = (double)(x - x1)/(x2 - x1);
			gest = (double)g1 + (g2 - g1) * r2;
			g = (double)ptrtemp[x];
			if(g-gest > epsilon || gest - g > epsilon)
				return false;
		}
	}
	else if(x1 == x2 && y1 < y2)//单列
	{
		ptrtemp = (uchar *)img->imageData + img->widthStep * y1;
		g1 = ptrtemp[x1];
		ptrtemp = (uchar *)img->imageData + img->widthStep * y2;
		g3 = ptrtemp[x1];

		for(y = y1; y <= y2; y++)
		{
			ptr = (uchar *)img->imageData + img->widthStep * y;
			r1 = (double)(y - y1)/(y2 - y1);
			gest = (double)g1 + (g3 - g1) * r1;
			g = (double)ptr[x1];
			if(g-gest > epsilon || gest - g > epsilon)
				return false;
		}
	}
	
	else;//单独点

	return true;
}
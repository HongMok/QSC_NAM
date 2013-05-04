#include "functions.h"

bool isSameMat(CvMat *R1, CvMat *R2)
{
	for(int r = 0; r < R1->rows; r++)
	{
		uchar *ptr1 = (uchar *)R1->data.ptr + r * R1->step;
		uchar *ptr2 = (uchar *)R2->data.ptr + r * R2->step;

		for(int c = 0; c < R1->cols; c++)
		{
			int t1 = (int)ptr1[c];
			int t2 = (int)ptr2[c];
			if(t1 != t2)
				return false;
		}
	}

	return true;
}
#include "functions.h"

void copyMat(CvMat *R1, CvMat *R2)//°ÑR2¸´ÖÆ¸øR1
{
	for(int r = 0; r < R1->rows; r++)
	{
		uchar *ptr1 = (uchar *)R1->data.ptr + r * R1->step;
		uchar *ptr2 = (uchar *)R2->data.ptr + r * R2->step;

		for(int c = 0; c < R1->cols; c++)
		{
			ptr1[c] = ptr2[c];
		}
	}
}
#include "functions.h"

void img2mat(IplImage *srcImg, CvMat *R)
{
	//CvMat *R = cvCreateMat(srcImg->height, srcImg->width, CV_32FC1);
	uchar *iptr = (uchar *)srcImg->imageData;
	uchar *rptr = (uchar *)R->data.ptr;
	for(int h = 0; h < R->rows; h++)
	{
		iptr = (uchar *)(srcImg->imageData + h * srcImg->widthStep);
		rptr = (uchar *)(R->data.ptr + h * R->step);
		for(int w = 0; w < R->cols; w++)
		{
			rptr[w] = (uchar)iptr[w];
		}
	}
}
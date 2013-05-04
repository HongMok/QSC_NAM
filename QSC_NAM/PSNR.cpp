#include "functions.h"

/************************************************************************/
/* 
	计算PSNR(peak signal to noise ratio)，峰值信噪比
*/
/************************************************************************/
double PSNR ( IplImage *img1 , IplImage *imggest ) //计算PSNR

{
	int M = img1->height;
	int N = img1->width;

	double temp=0;
	double temp1=0;

	for(int y = 0;y<M;y++)
	{
		uchar* ptr1 = (uchar*) (img1->imageData+y*img1->widthStep);
		uchar* ptrg = (uchar*) (imggest->imageData+y*imggest->widthStep);

		for (int x = 0;x<N;x++)
		{
			temp+=pow((double)(ptr1[x]-ptrg[x]),2);
		}
	}


	temp1=10*log10 (255.0*255*M*N/temp);
	return (temp1);


}
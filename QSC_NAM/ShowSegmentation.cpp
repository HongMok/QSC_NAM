#include "functions.h"

/************************************************************************/
/* 
	显示分割示意图
*/
/************************************************************************/
void ShowSegmentation(IplImage *sketch, vector<CouplePoints> &C)
{
	//画示意图
	cvNamedWindow("分割示意图", CV_WINDOW_AUTOSIZE);

	//创建素描图像
	for(int y = 0;y<sketch->height;y++)             
	{
		uchar* ptrsketch = (uchar*) (sketch->imageData+y*sketch->widthStep);

		for (int x = 0;x<sketch->width;x++)
		{
			ptrsketch[x]=255;
		}
	}
	//素描图像初始化完成
	for (int i=0 ; i<C.size();i++)
	{
		if (C[i].x1==0&&C[i].y1==0)
			cvRectangle(sketch,cvPoint(C[i].x1,C[i].y1),cvPoint(C[i].x2,C[i].y2),cvScalar(0x00,0x00,0x00));
		else   if (C[i].x1==0&&C[i].y1!=0)
			cvRectangle(sketch,cvPoint(C[i].x1,C[i].y1-1),cvPoint(C[i].x2,C[i].y2),cvScalar(0x00,0x00,0x00));
		else   if (C[i].x1!=0&&C[i].y1==0)
			cvRectangle(sketch,cvPoint(C[i].x1-1,C[i].y1),cvPoint(C[i].x2,C[i].y2),cvScalar(0x00,0x00,0x00));
		else   if (C[i].x1!=0&&C[i].y1!=0)
			cvRectangle(sketch,cvPoint(C[i].x1-1,C[i].y1-1),cvPoint(C[i].x2,C[i].y2),cvScalar(0x00,0x00,0x00));

	}
	cvShowImage("分割示意图",sketch);//载入转化后的灰度图像 
}
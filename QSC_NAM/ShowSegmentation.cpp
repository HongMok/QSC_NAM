#include "functions.h"

/************************************************************************/
/* 
	��ʾ�ָ�ʾ��ͼ
*/
/************************************************************************/
void ShowSegmentation(IplImage *sketch, vector<CouplePoints> &C)
{
	//��ʾ��ͼ
	cvNamedWindow("�ָ�ʾ��ͼ", CV_WINDOW_AUTOSIZE);

	//��������ͼ��
	for(int y = 0;y<sketch->height;y++)             
	{
		uchar* ptrsketch = (uchar*) (sketch->imageData+y*sketch->widthStep);

		for (int x = 0;x<sketch->width;x++)
		{
			ptrsketch[x]=255;
		}
	}
	//����ͼ���ʼ�����
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
	cvShowImage("�ָ�ʾ��ͼ",sketch);//����ת����ĻҶ�ͼ�� 
}
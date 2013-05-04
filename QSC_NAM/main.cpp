#include "functions.h"


/************************************************************************/
/* 
�������ã�

	1.���г�������
	2.ԭʼͼ���ַ
	3.epsilon
	4.��������������         ����������ƣ�-1�������ƣ�
	5.�ҿ鷽�����ȼ�           ���ݷ������ȼ���1�������ȣ� 2�������ȣ� 3���Խ�����
	6.�������                ������ţ� 1��NAM; 2.FRAG_NAM; 3.AC_NAM; 4.AC_FRAG_NAM;
	7.����ԭʼ�Ҷ�ͼ���ַ
	8.��������ͼ���ַ
	9.�ֿ�ʾ��ͼ��ַ
*/
/************************************************************************/

int main(int argc, char **argv)
{
	//test();
	//return 0;

	if(argc != 9)
		return -1;

	char *filename = argv[1];
	double epsilon = atof(argv[2]);

	int r = int(atof(argv[3]));//����������ƣ�-1�������ƣ�
	int t = int(atof(argv[4])); //���ݷ������ȼ���1�������ȣ� 2�������ȣ� 3���Խ�����

	METHOD = int(atof(argv[5]));//������ţ� 1��NAM; 2.FRAG_NAM; 3.AC_NAM; 4.AC_FRAG_NAM;

	char *save_srcimg = argv[6];
	char *save_desimg = argv[7];
	char *save_sketchimg = argv[8];

	IplImage *srcImg = cvLoadImage(filename, 0);
	if(srcImg == NULL)
	{
		cout<<"����ͼ��Ϊ��"<<endl;
		return 0;
	}
	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", srcImg);

	vector<GrayLevel> P;
	vector<char> Q;
	vector<CouplePoints> blks;

	time_t start_t = clock();

	int frag_num = 1; //�ֶ���

	RNAMencoding(srcImg, epsilon, P, Q, blks, frag_num, r, t);

	cout<<"������ʱ��"<<clock() - start_t<<" ms"<<endl;


	IplImage *sketch = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U,1); 
	ShowSegmentation(sketch, blks);

	


	IplImage *desImg = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U, 0);
	start_t = clock();
	RNAMdecoding(desImg, epsilon, P, Q, frag_num);
	cout<<"������ʱ��"<<clock() - start_t<<" ms"<<endl;
	cvNamedWindow("����ָ�", CV_WINDOW_AUTOSIZE);
	cvShowImage("����ָ�", desImg);

	
	cout<<endl;
	cout<<"������"<<blks.size()<<endl;
	cout<<"��ɫ���ȣ�"<<P.size()<<endl;
	cout<<"������ȣ�"<<Q.size()<<endl;

	cout<<endl;
	cout<<"epsilon: "<<epsilon<<endl;
	cout<<"BPP: "<<BPP(P, srcImg->height, srcImg->widthStep, Q)<<endl;
	cout<<"PSNR: "<<PSNR(srcImg, desImg)<<endl;

	cout<<endl;
	
	cout<<"�����������"<<calCodingPoint(P)<<endl;
	cout<<"ÿ�зֶ�����"<<frag_num<<endl;

	
	cvSaveImage(save_srcimg, srcImg);
	cvSaveImage(save_desimg, desImg);
	cvSaveImage(save_sketchimg, sketch);


	cvReleaseImage(&srcImg);
	cvReleaseImage(&desImg);
	cvReleaseImage(&sketch);
	cvWaitKey(0);
	cvDestroyAllWindows();


	
	return 0;
}
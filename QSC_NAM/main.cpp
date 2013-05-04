#include "functions.h"


/************************************************************************/
/* 
参数配置：

	1.运行程序名称
	2.原始图像地址
	3.epsilon
	4.长宽最大比例限制         长宽比例限制，-1：无限制；
	5.找块方向优先级           横纵方向优先级，1：横优先； 2：纵优先； 3：对角优先
	6.方法序号                方法序号： 1：NAM; 2.FRAG_NAM; 3.AC_NAM; 4.AC_FRAG_NAM;
	7.保存原始灰度图像地址
	8.保存解码后图像地址
	9.分块示意图地址
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

	int r = int(atof(argv[3]));//长宽比例限制，-1：无限制；
	int t = int(atof(argv[4])); //横纵方向优先级，1：横优先； 2：纵优先； 3：对角优先

	METHOD = int(atof(argv[5]));//方法序号： 1：NAM; 2.FRAG_NAM; 3.AC_NAM; 4.AC_FRAG_NAM;

	char *save_srcimg = argv[6];
	char *save_desimg = argv[7];
	char *save_sketchimg = argv[8];

	IplImage *srcImg = cvLoadImage(filename, 0);
	if(srcImg == NULL)
	{
		cout<<"输入图像为空"<<endl;
		return 0;
	}
	cvNamedWindow("原图", CV_WINDOW_AUTOSIZE);
	cvShowImage("原图", srcImg);

	vector<GrayLevel> P;
	vector<char> Q;
	vector<CouplePoints> blks;

	time_t start_t = clock();

	int frag_num = 1; //分段数

	RNAMencoding(srcImg, epsilon, P, Q, blks, frag_num, r, t);

	cout<<"编码用时："<<clock() - start_t<<" ms"<<endl;


	IplImage *sketch = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U,1); 
	ShowSegmentation(sketch, blks);

	


	IplImage *desImg = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U, 0);
	start_t = clock();
	RNAMdecoding(desImg, epsilon, P, Q, frag_num);
	cout<<"解码用时："<<clock() - start_t<<" ms"<<endl;
	cvNamedWindow("解码恢复", CV_WINDOW_AUTOSIZE);
	cvShowImage("解码恢复", desImg);

	
	cout<<endl;
	cout<<"块数："<<blks.size()<<endl;
	cout<<"颜色表长度："<<P.size()<<endl;
	cout<<"坐标表长度："<<Q.size()<<endl;

	cout<<endl;
	cout<<"epsilon: "<<epsilon<<endl;
	cout<<"BPP: "<<BPP(P, srcImg->height, srcImg->widthStep, Q)<<endl;
	cout<<"PSNR: "<<PSNR(srcImg, desImg)<<endl;

	cout<<endl;
	
	cout<<"编码点总数："<<calCodingPoint(P)<<endl;
	cout<<"每行分段数："<<frag_num<<endl;

	
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
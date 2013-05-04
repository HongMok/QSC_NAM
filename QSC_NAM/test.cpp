#include "functions.h"

void CompressCoordinate2 ( CvMat *&R , vector<char> &Q )  //坐标数据压缩
{
	


	int M = R->height;
	int N = R->width;
	int c=0;
	int k=0;
	int count=0;
	uchar* ptr = (uchar*) (R->data.ptr);

	for(int y = 0; y<M; y++)
	{
		ptr = (uchar*) (R->data.ptr+y*R->step);
		c=0;
		k=0;
		count=0;

		for (int x=0; x<N; x++)            //扫描
		{ 
			if(ptr[x]==0) continue;
			else if(ptr[x]==1) {Q.push_back('1');Q.push_back('1');}  //1
			else if(ptr[x]==2) {Q.push_back('1');Q.push_back('0');Q.push_back('1');}//2
			else if(ptr[x]==3) {Q.push_back('1');Q.push_back('0');Q.push_back('0');}//孤立

			int b = ceil(log((double)(N-c-count))/log(2.0));		 
			k=x-c-count;
			if (b==0) b=1;
			char* p = new char[b];
			for (int i=0;i<b;i++)
				p[i]='0';
			//DectoBin( p , k) ;    //转为二进制
			p = dec2binstr(k, b);
			for (int j=b-1;j>=0;j--)
				Q.push_back(p[j]);		 
			c = x;//记录点
			count=1;


		}
		if(ptr[N-1]==0) {Q.push_back('0');}
	}

}

void test()
{

	IplImage *srcImg = cvLoadImage("save.bmp", 0);
	CvMat *R = cvCreateMat(srcImg->height, srcImg->width, CV_32FC1);
	//cvConvert(srcImg, R);
	img2mat(srcImg, R);
	//return ;
	/*
	//CvMat *R = cvCreateMat(2, 12, CV_32FC1);
	uchar *ptr = (uchar *)R->data.ptr;
	
	ptr[0] = 1;
	ptr[1] = 2;
	ptr[2] = 3;
	ptr[3] = 0;

	ptr[4] = 0;
	ptr[5] = 0;
	ptr[6] = 0;
	ptr[7] = 0;

	ptr[8] = 1;
	ptr[9] = 2;
	ptr[10] = 3;
	ptr[11] = 1;

	ptr = (uchar *)R->data.ptr + R->step;
	
	ptr[0] = 0;
	ptr[1] = 0;
	ptr[2] = 0;
	ptr[3] = 0;

	ptr[4] = 0;
	ptr[5] = 0;
	ptr[6] = 0;
	ptr[7] = 0;

	ptr[8] = 0;
	ptr[9] = 0;
	ptr[10] =0;
	ptr[11] = 1;
	//cvZero(R);
	*/
	/*
	uchar *ptr = (uchar *)R->data.ptr;
	ptr[0] = 0;
	ptr[1] = 1;
	ptr[2] = 0;
	ptr[3] = 1;
	ptr = (uchar *)R->data.ptr + 1*R->step;
	ptr[0] = 0;
	ptr[1] = 0;
	ptr[2] = 2;
	ptr[3] = 1;
	ptr = (uchar *)R->data.ptr + 2*R->step;
	ptr[0] = 2;
	ptr[1] = 3;
	ptr[2] = 0;
	ptr[3] = 0;
	*/
	
	cout<<"before: "<<endl;
	for(int h = 0; h < R->rows; h++)
	{
		uchar *ptr2 = (uchar *)(R->data.ptr + h * R->step);
		for(int w = 0; w < R->cols; w++)
		{
			cout<<(float)ptr2[w]<<" ";
		}
		cout<<endl;
	}

	vector<char> Q;
	//CompressCoordinate(R, Q);
	Fragment_CompressCoordinate(R, Q, 3);
	int bit_len, count;
	//AC_CompressCoordinate(R, _nsym, _count);
	//AC_Fragment_CompressCoordinate(R, _nsym, _count, 3);

	for(int i = 0; i < Q.size(); i++)
	{
		cout<<Q[i]<<" ";
	}
	cout<<endl<<"after: "<<endl;
	//AC_DecompressCoordinate(R, _nsym, _count);
	//AC_Fragment_DecompressCoordinate(R, _nsym, _count, 3);
	//DecompressCoordinate(R, Q);
	Fragment_DecompressCoordinate(R, Q, 3);
	for(int h = 0; h < R->rows; h++)
	{
		uchar *ptr2 = (uchar *)(R->data.ptr + h * R->step);
		for(int w = 0; w < R->cols; w++)
		{
			cout<<(float)ptr2[w]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"size: "<<Q.size()<<endl;
	
}


void dispIline(CvMat *R, int i)
{
	uchar *ptr = (uchar *)R->data.ptr + i * R->step;
	for(int i = 0; i < R->width; i++)
	{
		cout<<(int)ptr[i];
		if((i+1)%4 == 0)
			cout<<" ";
	}
}
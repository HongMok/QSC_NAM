#include "functions.h"

void writeNum(vector<int> &Q, int num);

void writeDist(vector<int> &Q, int dist);

void AC_CompressCoordinate(CvMat *R, int &NSYM, int &count)
{
	vector<int> Q;

	for(int h = 0; h < R->height; h++)
	{
		uchar *ptr = (uchar *)(R->data.ptr + h * R->step);
		bool left_zero = true;
		int c = -1; //前一次出现非零的位置

		for(int w = 0; w < R->width; w++)
		{
			if(ptr[w] == 0)
			{
				left_zero = true;
				continue;
			}

			left_zero = false;


			writeNum(Q, ptr[w]);

			if(c == (R->width - 2) )//最后两个点都要编码的话，最后一个的距离不用编码
			{
				c = c + 1;
				continue;
			}

			writeDist(Q, w-c-1);

			c = w;
		}
		if(left_zero == true)
			Q.push_back(0);
	}

	
	//bit_len = calBitLen(Q);
	NSYM = calMaxNum(Q);
	count = Q.size();
	ac_compress_array(Q, NSYM);
}


void writeNum(vector<int> &Q, int num)
{
	Q.push_back(num);
}


void writeDist(vector<int> &Q, int dist)
{
	dist += 4;
	Q.push_back(dist);
}
#include "functions.h"

void writeNum(vector<char> &Q, int num);

void writeDist(vector<char> &Q, int &b, int w, int c, int len);

void CompressCoordinate(CvMat *R, vector<char> &Q)
{
	for(int h = 0; h < R->height; h++)
	{
		uchar *ptr = (uchar *)(R->data.ptr + h * R->step);
		bool left_zero = true;
		int c = -1; //前一次出现非零的位置
		int b = 0;

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
			
			writeDist(Q, b, w, c, R->width);
			
			c = w;
		}
		if(left_zero == true)
			Q.push_back('0');//整行都是0
	}

	_coor_table_size = Q.size();
}


void writeNum(vector<char> &Q, int num)
{
	switch(num)
	{
	case 1://左上角
		VectorAddStr(Q, "11", 2);
		break;
	case 2://右下角
		VectorAddStr(Q, "101", 3);
		break;
	case 3://单独点
		VectorAddStr(Q, "100", 3);
		break;
	}
}

void writeDist(vector<char> &Q, int &b, int w, int c, int len)
{
	b = ceil(log(double(len - 1 - c))/log(2.0));
	if(b == 0)
		b = 1;
	char *str = dec2binstr(w-c-1, b);
	//char *str = advanced_dec2binstr(w-c-1, b);
	VectorAddStr(Q, str, b);
}
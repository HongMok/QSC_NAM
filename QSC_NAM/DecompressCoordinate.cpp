#include "functions.h"

void readNum(vector<char> &Q, int &qi, int &b, int &c, int &type_num, int len);
void readDist(vector<char> &Q, int &qi, int &b, int &c, int &d);

void DecompressCoordinate(CvMat *R, vector<char> &Q)
{
	cvmSetZero(R);

	int qi = 0;//Q下标
	uchar *ptr = (uchar *)(R->data.ptr);
	int h = 0;//第几行
	int c = -1; //前一次出现非零的位置
	int b = 0;//记录d需要比特位位数
	int d = 0; //与前一次出现非零位置的距离
	int type_num; //非零点的值

	while(true)
	{
		if(Q[qi] == '1')
		{
			
			readNum(Q, qi, b, c, type_num, R->width);

			if(c != R->width - 2)
			{
				readDist(Q, qi, b, c, d);
				
			}
			else
			{
				c = c + 1;
			}

			ptr[c] = type_num;
		}


		bool isLineEnd = false;
		if(c == (R->width-1) || Q[qi] == '0')
		{
			if( c == (R->width-1))
				isLineEnd = true;

			h++;

			if(h >= R->height)
				return;//最后一行处理后返回
			ptr = (uchar *)(R->data.ptr + h*R->step);//下一行

			b = d = 0;
			c = -1;

			if(isLineEnd == false && Q[qi] == '0')
				qi++;
		}
	}
	
}


void readNum(vector<char> &Q, int &qi, int &b, int &c, int &type_num, int len)
{
	b = ceil(log(double(len - 1 - c))/log(2.0));
	if(b == 0)
		b = 1;

	if(Q[qi+1] == '1')//1左上角
	{
		qi += 2;
		type_num = 1;
	}
	else
	{
		if(Q[qi+2] == '1')//2右下角
		{
			qi += 3;
			type_num = 2;
		}
		else//3单独点
		{
			qi += 3;
			type_num = 3;
		}
	}
}

void readDist(vector<char> &Q, int &qi, int &b, int &c, int &d)
{
	d = binstr2dec(Q, qi, b);
	//d = advanced_binstr2dec(Q, qi, b);
	c = c + 1 + d;//跳过d位0

	qi += b;//跳过记录d的b个位
}
#include "functions.h"

void AC_DecompressCoordinate(CvMat *R, int NSYM, int count)
{
	vector<int> Q;
	ac_decompress_array(Q, NSYM, count);

	cvmSetZero(R);

	int qi = 0;//Q下标
	uchar *ptr = (uchar *)(R->data.ptr);
	int h = 0;//第几行
	int c = -1; //前一次出现非零的位置
	int d = 0; //与前一次出现非零位置的距离
	int type_num; //非零点的值

	while(true)
	{
		if(Q[qi] != 0)
		{
			//read num
			type_num = Q[qi++];

			if(c != R->width - 2)
			{
				//read dist
				d = Q[qi++] - 4;
				c = c + 1 + d;
			}
			else
			{
				c = c + 1;
			}

			ptr[c] = type_num;
		}


		bool isLineEnd = false;
		if(c == (R->width-1) || Q[qi] == 0)
		{
			if( c == (R->width-1))
				isLineEnd = true;

			h++;

			if(h >= R->height)
				return;//最后一行处理后返回
			ptr = (uchar *)(R->data.ptr + h*R->step);//下一行

			d = 0;
			c = -1;

			if(isLineEnd == false && Q[qi] == 0)
				qi++;
		}
	}

}


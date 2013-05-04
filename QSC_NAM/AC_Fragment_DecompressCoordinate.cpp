#include "functions.h"


void AC_Fragment_DecompressCoordinate(CvMat *R, int NSYM, int count, int frag_num)
{
	vector<int> Q;
	ac_decompress_array(Q, NSYM, count);

	cvmSetZero(R);

	int unit_len = (int)ceil((double)R->width / frag_num);
	int start_i = 0;

	int qi = 0;//Q下标
	uchar *ptr = (uchar *)(R->data.ptr);
	int h = 0;//第几行
	int c = -1; //前一次出现非零的位置
	int d = 0; //与前一次出现非零位置的距离
	int type_num; //非零点的值
	int frag_line_count = 0;//每行段数数

	while(true)
	{
		if(Q[qi] != 0)
		{
			//read_num(Q, qi, b, c, type_num, unit_len);
			type_num = Q[qi++];

			if(c != unit_len - 2)
			{
				//read_dist(Q, qi, b, c, d);
				d = Q[qi++];
				c = c + d;
			}
			c += 1;

			ptr[start_i+c] = type_num;
		}

		if((start_i + c) == (R->width-1) || c == (unit_len - 1) || Q[qi] == 0)
		{
			bool isFragEnd = false;
			if(c == (unit_len - 1))
				isFragEnd = true;

			bool isLineEnd = false;
			if( (start_i + c) == (R->width-1))
				isLineEnd = true;

			frag_line_count++;
			start_i += unit_len;

			if(frag_line_count == frag_num)
			{
				frag_line_count = 0;
				start_i = 0;

				h++;
				if(h >= R->height)
					return;//最后一行处理后返回
				ptr = (uchar *)(R->data.ptr + h*R->step);//下一行
			}


			d = 0;
			c = -1;


			if(isLineEnd == false && isFragEnd == false && Q[qi] == 0)
				qi++;
		}
	}

}



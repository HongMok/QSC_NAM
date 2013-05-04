#include "functions.h"


void write_num(vector<char> &Q, int num);
void write_dist(vector<char> &Q, int &b, int ui, int c, int unit_len);


void Fragment_CompressCoordinate(CvMat *R, vector<char> &Q, int frag_num)
{
	int unit_len = (int)ceil((double)R->width / frag_num);
	int start_i;
	uchar *ptr;
	bool left_zero;
	int c; //前一次出现非零的位置
	int b;

	for(int h = 0; h < R->height; h++)
	{
		uchar *ptr = (uchar *)(R->data.ptr + h * R->step);

		for(int fi = 0; fi < frag_num; fi++)
		{
			left_zero = true;
			c = -1; //前一次出现非零的位置
			b = 0;

			start_i = fi * unit_len;
			for(int ui = 0; ui < unit_len; ui++)
			{
				int ci = start_i + ui;

				if(ci >= R->width)
					break;//最后一段长度可能不够unit_len

				if(ptr[ci] == 0)
				{
					left_zero = true;
					continue;
				}

				left_zero = false;

				write_num(Q, ptr[ci]);

				if(c == unit_len - 2)//最后两个是编码点，则最后一个不用编码距离
				{
					c = c + 1;
					continue;
				}
				write_dist(Q, b, ui, c, unit_len);

				c = ui;
			}
			if(left_zero == true)
				Q.push_back('0');//段剩余全部为0
		}
	}

	_coor_table_size = Q.size();
}


void write_num(vector<char> &Q, int num)
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


void write_dist(vector<char> &Q, int &b, int ui, int c, int unit_len)
{
	b = ceil(log(double(unit_len - 1 - c))/log(2.0));
	if(b == 0)
		b = 1;
	char *str = dec2binstr(ui-c-1, b);
	//char *str = advanced_dec2binstr(w-c-1, b);
	VectorAddStr(Q, str, b);
}


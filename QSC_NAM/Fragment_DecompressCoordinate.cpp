#include "functions.h"


void read_num(vector<char> &Q, int &qi, int &b, int &c, int &type_num, int unit_len);
void read_dist(vector<char> &Q, int &qi, int &b, int &c, int &d);

void Fragment_DecompressCoordinate(CvMat *R, vector<char> &Q, int frag_num)
{
	cvmSetZero(R);

	int unit_len = (int)ceil((double)R->width / frag_num);
	int start_i = 0;

	int qi = 0;//Q下标
	uchar *ptr = (uchar *)(R->data.ptr);
	int h = 0;//第几行
	int c = -1; //前一次出现非零的位置
	int b = 0;//记录d需要比特位位数
	int d = 0; //与前一次出现非零位置的距离
	int type_num; //非零点的值
	int frag_line_count = 0;//每行段数数

	while(true)
	{
		if(Q[qi] == '1')
		{
			read_num(Q, qi, b, c, type_num, unit_len);
			
			if(c == unit_len - 2)
			{
				c = c + 1;
			}
			else
			{
				read_dist(Q, qi, b, c, d);
			}
			

			ptr[start_i+c] = type_num;
		}
		
		if((start_i + c) == (R->width-1) || c == (unit_len - 1) || Q[qi] == '0')
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
			

			b = d = 0;
			c = -1;

			
			if(isLineEnd == false && isFragEnd == false && Q[qi] == '0')
				qi++;
		}
	}

}




void read_num(vector<char> &Q, int &qi, int &b, int &c, int &type_num, int unit_len)
{
	b = ceil(log(double(unit_len - 1 - c))/log(2.0));
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


void read_dist(vector<char> &Q, int &qi, int &b, int &c, int &d)
{
	d = binstr2dec(Q, qi, b);
	//d = advanced_binstr2dec(Q, qi, b);
	c = c + 1 + d;//跳过d位0
	

	qi += b;//跳过记录d的b个位
}

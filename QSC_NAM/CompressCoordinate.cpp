#include "functions.h"

void writeNum(vector<char> &Q, int num);

void writeDist(vector<char> &Q, int &b, int w, int c, int len);

void CompressCoordinate(CvMat *R, vector<char> &Q)
{
	for(int h = 0; h < R->height; h++)
	{
		uchar *ptr = (uchar *)(R->data.ptr + h * R->step);
		bool left_zero = true;
		int c = -1; //ǰһ�γ��ַ����λ��
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

			if(c == (R->width - 2) )//��������㶼Ҫ����Ļ������һ���ľ��벻�ñ���
			{
				c = c + 1;
				continue;
			}
			
			writeDist(Q, b, w, c, R->width);
			
			c = w;
		}
		if(left_zero == true)
			Q.push_back('0');//���ж���0
	}

	_coor_table_size = Q.size();
}


void writeNum(vector<char> &Q, int num)
{
	switch(num)
	{
	case 1://���Ͻ�
		VectorAddStr(Q, "11", 2);
		break;
	case 2://���½�
		VectorAddStr(Q, "101", 3);
		break;
	case 3://������
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
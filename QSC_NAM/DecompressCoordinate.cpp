#include "functions.h"

void readNum(vector<char> &Q, int &qi, int &b, int &c, int &type_num, int len);
void readDist(vector<char> &Q, int &qi, int &b, int &c, int &d);

void DecompressCoordinate(CvMat *R, vector<char> &Q)
{
	cvmSetZero(R);

	int qi = 0;//Q�±�
	uchar *ptr = (uchar *)(R->data.ptr);
	int h = 0;//�ڼ���
	int c = -1; //ǰһ�γ��ַ����λ��
	int b = 0;//��¼d��Ҫ����λλ��
	int d = 0; //��ǰһ�γ��ַ���λ�õľ���
	int type_num; //������ֵ

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
				return;//���һ�д���󷵻�
			ptr = (uchar *)(R->data.ptr + h*R->step);//��һ��

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

	if(Q[qi+1] == '1')//1���Ͻ�
	{
		qi += 2;
		type_num = 1;
	}
	else
	{
		if(Q[qi+2] == '1')//2���½�
		{
			qi += 3;
			type_num = 2;
		}
		else//3������
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
	c = c + 1 + d;//����dλ0

	qi += b;//������¼d��b��λ
}
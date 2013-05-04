#include "functions.h"

void AC_DecompressCoordinate(CvMat *R, int NSYM, int count)
{
	vector<int> Q;
	ac_decompress_array(Q, NSYM, count);

	cvmSetZero(R);

	int qi = 0;//Q�±�
	uchar *ptr = (uchar *)(R->data.ptr);
	int h = 0;//�ڼ���
	int c = -1; //ǰһ�γ��ַ����λ��
	int d = 0; //��ǰһ�γ��ַ���λ�õľ���
	int type_num; //������ֵ

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
				return;//���һ�д���󷵻�
			ptr = (uchar *)(R->data.ptr + h*R->step);//��һ��

			d = 0;
			c = -1;

			if(isLineEnd == false && Q[qi] == 0)
				qi++;
		}
	}

}


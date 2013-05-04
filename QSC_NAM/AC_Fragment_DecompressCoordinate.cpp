#include "functions.h"


void AC_Fragment_DecompressCoordinate(CvMat *R, int NSYM, int count, int frag_num)
{
	vector<int> Q;
	ac_decompress_array(Q, NSYM, count);

	cvmSetZero(R);

	int unit_len = (int)ceil((double)R->width / frag_num);
	int start_i = 0;

	int qi = 0;//Q�±�
	uchar *ptr = (uchar *)(R->data.ptr);
	int h = 0;//�ڼ���
	int c = -1; //ǰһ�γ��ַ����λ��
	int d = 0; //��ǰһ�γ��ַ���λ�õľ���
	int type_num; //������ֵ
	int frag_line_count = 0;//ÿ�ж�����

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
					return;//���һ�д���󷵻�
				ptr = (uchar *)(R->data.ptr + h*R->step);//��һ��
			}


			d = 0;
			c = -1;


			if(isLineEnd == false && isFragEnd == false && Q[qi] == 0)
				qi++;
		}
	}

}



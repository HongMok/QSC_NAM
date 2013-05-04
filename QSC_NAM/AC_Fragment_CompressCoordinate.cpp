#include "functions.h"


void AC_Fragment_CompressCoordinate(CvMat *R, int &NSYM, int &count, int frag_num)
{
	vector<int> Q;

	int unit_len = (int)ceil((double)R->width / frag_num);
	int start_i;
	uchar *ptr;
	bool left_zero;
	int c; //ǰһ�γ��ַ����λ��

	for(int h = 0; h < R->height; h++)
	{
		uchar *ptr = (uchar *)(R->data.ptr + h * R->step);

		for(int fi = 0; fi < frag_num; fi++)
		{
			left_zero = true;
			c = -1; //ǰһ�γ��ַ����λ��

			start_i = fi * unit_len;
			for(int ui = 0; ui < unit_len; ui++)
			{
				int ci = start_i + ui;

				if(ci >= R->width)
					break;//���һ�γ��ȿ��ܲ���unit_len

				if(ptr[ci] == 0)
				{
					left_zero = true;
					continue;
				}

				left_zero = false;

				//write_num(Q, ptr[ci]);
				Q.push_back(int(ptr[ci]));

				if(c == unit_len - 2)//��������Ǳ���㣬�����һ�����ñ������
				{
					c = c + 1;
					continue;
				}
				//write_dist(Q, b, ui, c, unit_len);
				Q.push_back(ui-c-1);

				c = ui;
			}
			if(left_zero == true)
				Q.push_back(0);//��ʣ��ȫ��Ϊ0
		}
	}

	//bit_len = calBitLen(Q);
	NSYM = calMaxNum(Q);
	count = Q.size();
	ac_compress_array(Q, NSYM);
}



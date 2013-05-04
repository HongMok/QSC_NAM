#include "functions.h"


/************************************************************************/
/* 
	����BPP(bits per pixel),ÿ����ɫ��λ
*/
/************************************************************************/
double BPP ( vector<GrayLevel> &P ,int M , int N , vector<char> &Q )  //����BPP
{
	int t1 = 0;//��ͨ������
	int t2 = 0;//���е���
	int t3 = 0;//������

	for(int i = 0; i < P.size(); i++)
	{
		if(P[i].g2 == -1)
		{
			if(P[i].g3 == -1 && P[i].g4 == -1)//������
				t3++;
			else//���е���
				t2++;
		}
		else//��ͨ
			t1++;
	}

	int sum = t1 * 32 + t2 * 16 + t3 * 8;

	int qsize = _coor_table_size;

	double b = (double)(qsize + sum)/(M*N);
	return b;
}
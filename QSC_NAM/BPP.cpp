#include "functions.h"


/************************************************************************/
/* 
	计算BPP(bits per pixel),每像素色彩位
*/
/************************************************************************/
double BPP ( vector<GrayLevel> &P ,int M , int N , vector<char> &Q )  //计算BPP
{
	int t1 = 0;//普通块类型
	int t2 = 0;//单行单列
	int t3 = 0;//单独点

	for(int i = 0; i < P.size(); i++)
	{
		if(P[i].g2 == -1)
		{
			if(P[i].g3 == -1 && P[i].g4 == -1)//单独点
				t3++;
			else//单行单列
				t2++;
		}
		else//普通
			t1++;
	}

	int sum = t1 * 32 + t2 * 16 + t3 * 8;

	int qsize = _coor_table_size;

	double b = (double)(qsize + sum)/(M*N);
	return b;
}
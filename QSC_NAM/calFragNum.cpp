#include "functions.h"


int calFragNum(vector<GrayLevel> &P, CvMat *R)
{
	int totalNum = calCodingPoint(P);

	int d = totalNum / R->rows; //ÿ��ƽ����d�������

	int k = (int)ceil(log(double(d))/log(2.0));

	int frag_num = 1;

	for(int i = 0; i < k; i++)
		frag_num *= 2;

	return frag_num;
}
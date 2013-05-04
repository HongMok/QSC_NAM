#include "functions.h"

int calCodingPoint(vector<GrayLevel> &P)
{
	int t3 = 0;//单独点

	for(int i = 0; i < P.size(); i++)
	{
		if(P[i].g3 == -1 && P[i].g4 == -1)//单独点
			t3++;
	}

	int sum = 2 * (P.size() - t3) + 1 * t3;

	return sum;
}
#include "functions.h"


int calMaxNum(vector<int> &Q)
{
	int maxNum = 0;
	for(int i = 0; i < Q.size(); i++)
	{
		if(Q[i] > maxNum)
			maxNum = Q[i];
	}

	return maxNum + 1;
}
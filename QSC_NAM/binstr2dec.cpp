#include "functions.h"

int binstr2dec(vector<char> &Q, int start_i, int len)
{
	int d = 0;
	int t;
	for(int i = 0; i < len; i++)
	{
		t = (int)Q[start_i+i] - '0';
		t <<= (len - 1 - i);
		d += t;
	}

	return d;
}
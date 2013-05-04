#include "functions.h"

void VectorAddStr(vector<char> &Q, char *str, int len)
{
	for (int i = 0; i < len; i++)
	{
		Q.push_back(str[i]);
	}
}
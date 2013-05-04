#include "functions.h"

char *dec2binstr(int d, int len)
{
	char *str;
	str = new char[len];
	for(int i = 0; i < len; i++)
	{
		str[len - 1 - i] = (d & 0x1) + 48;	//0µÄasciiÂëÎª48
		d >>= 1;
	}
	return str;
}
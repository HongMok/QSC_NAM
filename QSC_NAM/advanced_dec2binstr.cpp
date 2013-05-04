#include "functions.h"

char *advanced_dec2binstr(int d, int &len)
{
	if(len <= 11)
		return dec2binstr(d, len);

	char *oldstr = dec2binstr(d, len);
	int zero_num = ceil(log(double(len))/log(2.0));
	int c = 0;//d�Ķ�����ǰ�����ĸ���
	for( ; c < len - 1 && oldstr[c] == 0; c++);

	if(c < 1 + zero_num)
	{
		char *newstr = new char[1+len];
		newstr[0] = '0';//û��ѹ����
		for(int i = 1; i < 1+len; i++)
			newstr[i] = oldstr[i-1];

		len = len + 1;//���³���
		return newstr;
	}
	else
	{
		int new_len = 1+zero_num+len-c;
		char *newstr = new char[new_len];
		newstr[0] = '1';//ѹ����
		char *zero_num_str = dec2binstr(c, zero_num);
		int newstr_index = 1;
		for(int i = 0; i < zero_num; i++)
			newstr[newstr_index++] = zero_num_str[i];
		for(int i = c; i < len; i++)
			newstr[newstr_index++] = oldstr[i];

		len = new_len; //���³���
		return newstr;
	}
}
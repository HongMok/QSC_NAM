#include "functions.h"

int advanced_binstr2dec(vector<char> &Q, int start_i, int &len)
{
	if(len <= 11)
		return binstr2dec(Q, start_i, len);

	if(Q[start_i] == '0')//û��0ѹ��
	{
		len = len + 1;//����һλ�����ж�
		return binstr2dec(Q, start_i + 1, len - 1);
	}
	else//��0ѹ��
	{
		int zero_num = ceil(log(double(len))/log(2.0));
		int c = binstr2dec(Q, start_i + 1, zero_num);
		int strlen = len - c;
		int d = binstr2dec(Q, start_i + c, strlen);
		len = 1 + zero_num + strlen;//���³���

		return d;
	}
}
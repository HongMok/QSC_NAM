#include "functions.h"

int advanced_binstr2dec(vector<char> &Q, int start_i, int &len)
{
	if(len <= 11)
		return binstr2dec(Q, start_i, len);

	if(Q[start_i] == '0')//没有0压缩
	{
		len = len + 1;//增加一位类型判断
		return binstr2dec(Q, start_i + 1, len - 1);
	}
	else//有0压缩
	{
		int zero_num = ceil(log(double(len))/log(2.0));
		int c = binstr2dec(Q, start_i + 1, zero_num);
		int strlen = len - c;
		int d = binstr2dec(Q, start_i + c, strlen);
		len = 1 + zero_num + strlen;//更新长度

		return d;
	}
}
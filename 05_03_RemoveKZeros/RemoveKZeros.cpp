#include <iostream>
#include <string>
using namespace std;

string RemoveKZeros(const string& str, int k)
{
	string res;
	int zeroLen = 0;
	for (int i = 0; i != str.length(); ++i)
	{
		if (str[i] == '0')
		{
			++zeroLen;
		}
		else
		{
			if (zeroLen != k) //长度不为k
				res += string(zeroLen, '0');
			res += str[i];
			zeroLen = 0;
		}

	}
	if (zeroLen != k) //长度不为k
		res += string(zeroLen, '0');

	return res;
}


int main()
{
	string test1 = "0A0B0C00D0";
	cout << RemoveKZeros(test1, 1) << endl;

	string test2 = "00A00B0C00D0";
	cout << RemoveKZeros(test2, 2) << endl;

	string test3 = "000A00B000C0D00";
	cout << RemoveKZeros(test3,3) << endl;

	string test4 = "0000A0000B00C000D0000";
	cout << RemoveKZeros(test4, 4) << endl;

	string test5 = "00000000";
	cout << RemoveKZeros(test5, 5) << endl;
	system("pause");
	return 0;
}


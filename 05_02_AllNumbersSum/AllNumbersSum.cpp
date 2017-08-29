#include <iostream>
using namespace std;


int AllNumbersSum(const string&str)
{
	int res = 0;
	int pre = 0;
	bool positive = true;
	for (int i = 0; i != str.length(); ++i)
	{
		if (str[i] == '.')
			continue;
		else if (str[i] == '-')
		{
			if (i >= 1 && str[i - 1] == '-') positive = !positive;
			else positive = false;
		}
		else if (str[i] <= '9'&&str[i] >= '0')
		{
			pre = (pre * 10 + str[i] - '0');
		}
		else //其他字符
		{
			res += positive ? pre : -pre;
			pre = 0;
			positive = true;
		}

	}

	res += positive ? pre : -pre;//遍历完了还要再结算一次

	return res;
}


int main()
{
	//string str = "ABC12D345";
	//string str = "ABC12.345D12";
	//string str = "ABC12.345D-12";
	//string str = "ABC12.345D--12";

	//string str = "ABC12.345D-.-12";

	string str = "1K-10.0ABC50.0D-T--1..00F200G!!100H---300";

	cout << AllNumbersSum(str) << endl;

	system("pause");
	return 0;
}


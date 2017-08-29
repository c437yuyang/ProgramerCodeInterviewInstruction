#include <iostream>
#include <string>
using namespace std;

bool isValid(const string&str) {
	if (str[0] != '-' && (str[0] < '0' || str[0] > '9')) {
		return false;
	}
	if (str[0] == '-' && (str.length() == 1 || str[1] == '0')) {
		return false;
	}
	if (str[0] == '0' && str.length() > 1) {
		return false;
	}
	for (int i = 1; i < str.length(); i++) {
		if (str[i] < '0' || str[i] > '9') {
			return false;
		}
	}
	return true;
}

#pragma region 有错，中间num可能直接溢出了
//int ConvertStringToInteger(const string&str)
//{
//	bool positive = str[0] != '-' ? true:false;
//	int num = str[0] == '-' ? 0 : str[0] - '0';
//	for (int i=1;i!=str.length();++i)
//		num = num * 10 + str[i] - '0';
//	if (num > INT_MAX || num < -INT_MAX - 1) return 0;
//	return positive ? num : -num;
//}  
#pragma endregion

#pragma region 左程云的版本

int ConvertStringToInteger(const string&str)
{
	bool positive = str[0] != '-' ? true : false;
	int num = str[0] == '-' ? 0 : '0' - str[0]; //全部转化成负数来统计，负数的范围更大
	int minq = (-INT_MAX-1) / 10; //最小的商
	int minr = (-INT_MAX-1) % 10; //最小的余数
	for (int i = 1; i != str.length(); ++i) 
	{
		int cur = '0' - str[i];

		if (num < minq || num == minq&&cur < minr) return 0;
		num = num * 10 + cur;
	}
	if (num > INT_MAX || num < -INT_MAX - 1) return 0; //最后再检查一次，其实没有必要
	if (positive && num == -INT_MAX - 1) return 0;
	return positive ? -num : num;
}

#pragma endregion




int main()
{
	//int i = 2147483649; //i值溢出
	//int i1 = 2147483649 + 1;//i1值溢出
	//int i2 = 2147483649 - 2; //i2值是没问题的，说明中间变量如果大于int_max是没有影响的，只要最终结果能够小于等于int_max即可
	//cout << 2147483649 << endl; //直接输出肯定是正常的
	//cout << (2147483649 > 2147483647) << endl; //直接输出肯定是正常的

	string test1 = "2147483647"; // max in java
	cout << ConvertStringToInteger(test1) << endl;

	string test2 = "-2147483648"; // min in java
	cout << ConvertStringToInteger(test2) << endl;

	string test3 = "2147483648"; // overflow
	cout << ConvertStringToInteger(test3) << endl;

	string test4 = "-2147483649"; // overflow
	cout << ConvertStringToInteger(test4) << endl;

	string test5 = "-123";
	cout << ConvertStringToInteger(test5) << endl;

	system("pause");
	return 0;
}


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

#pragma region �д��м�num����ֱ�������
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

#pragma region ����Ƶİ汾

int ConvertStringToInteger(const string&str)
{
	bool positive = str[0] != '-' ? true : false;
	int num = str[0] == '-' ? 0 : '0' - str[0]; //ȫ��ת���ɸ�����ͳ�ƣ������ķ�Χ����
	int minq = (-INT_MAX-1) / 10; //��С����
	int minr = (-INT_MAX-1) % 10; //��С������
	for (int i = 1; i != str.length(); ++i) 
	{
		int cur = '0' - str[i];

		if (num < minq || num == minq&&cur < minr) return 0;
		num = num * 10 + cur;
	}
	if (num > INT_MAX || num < -INT_MAX - 1) return 0; //����ټ��һ�Σ���ʵû�б�Ҫ
	if (positive && num == -INT_MAX - 1) return 0;
	return positive ? -num : num;
}

#pragma endregion




int main()
{
	//int i = 2147483649; //iֵ���
	//int i1 = 2147483649 + 1;//i1ֵ���
	//int i2 = 2147483649 - 2; //i2ֵ��û����ģ�˵���м�����������int_max��û��Ӱ��ģ�ֻҪ���ս���ܹ�С�ڵ���int_max����
	//cout << 2147483649 << endl; //ֱ������϶���������
	//cout << (2147483649 > 2147483647) << endl; //ֱ������϶���������

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


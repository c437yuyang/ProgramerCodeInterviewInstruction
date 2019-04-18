#include <string>
#include <iostream>
using namespace std;

bool isRotationString(const string&str1,const string &str2) 
{
	if (str1.length() != str2.length()) return false;
	string tmp = str2 + str2;
	return tmp.find(str1) != -1; //find里面其实是调用了kmp算法
}

//我自己的做法，复杂度稍微高点
bool isRotationString1(const string&str1, const string &str2)
{
	
	if (str1.length() != str2.length()) return false;

	int idx = str1.find(str2[0]); //找到第一个
	if (idx == -1) return false;

	int same = 0;
	int i = 0;
	while (same < str1.length()) 
	{
		if (str1[(idx + i)%str1.length()] != str2[i]) break;
		++i;
		++same;
	}

	return same == str1.length();
}

int main()
{
	string str1 = "yunzuocheng";
	//string str2 = "zuochengyun";
	string str2 = "zuochengyua";

	cout << isRotationString(str1, str2) << endl;
	cout << isRotationString1(str1, str2) << endl;


	string str3 = "aaaas";
	cout << str3 << endl;

	system("pause");
	return 0;
}


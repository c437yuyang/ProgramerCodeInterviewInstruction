#include <string>
#include <iostream>
using namespace std;

bool isRotationString(const string&str1,const string &str2) 
{
	if (str1.length() != str2.length()) return false;
	string tmp = str2 + str2;
	return tmp.find(str1) != -1; //find里面其实是调用了kmp算法
}


int main()
{
	string str1 = "yunzuocheng";
	string str2 = "zuochengyun";

	cout << isRotationString(str1, str2) << endl;

	system("pause");
	return 0;
}


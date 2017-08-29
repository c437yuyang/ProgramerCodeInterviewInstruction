
#include <iostream>
#include <string>
using namespace std;

bool isDeformation(const string &str1, const string &str2) 
{
	if (str1.length() != str2.length()) return false;

	char hist[256] = {0};
	for (auto it = str1.begin();it!=str1.end();++it)
	{
		++hist[*it];
	}

	for (auto it = str2.begin(); it != str2.end(); ++it)
	{
		if (--hist[*it] < 0) return false;
	}

	return true;
}


int main()
{

	string s1 = "abc";
	string s2 = "bca";

	cout << isDeformation(s1, s2) << endl;

	system("pause");
	return 0;
}


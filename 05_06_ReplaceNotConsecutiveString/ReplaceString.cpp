#include <string>
#include <vector>
#include <iostream>
using namespace std;

//这个版本是直接只替换第一次出现的，后面连续出现的不管，不是书上的题意
string replaceString(const string&str, const string&from, const string &to)
{
	//思路:找到所有出现指定from的位置，判断是否是连续，进行替换
	string res;
	vector<int> posVec;
	int pos = str.find(from, 0);
	if (pos == -1)
		return str;

	while (pos != -1)
	{
		posVec.push_back(pos);
		pos = str.find(from, pos + 1);
	}

	//把那些不需要的删除掉
	int pre = posVec[0];
	for (auto it = posVec.begin(); it != posVec.end();)
	{
		if (*it - pre == from.length())
		{
			pre = *it;
			it = posVec.erase(it);
		}
		else
		{
			pre = *it;
			++it;
		}
	}
	int j = 0;
	for (int i = 0; i != str.length();)
	{
		if (j < posVec.size() && i == posVec[j])
		{
			++j;
			res += to;
			i += from.length();
		}
		else
		{
			res += str[i];
			++i;
		}
	}

	return res;
}

//这个版本才是书上的题意，后面的直接消失，没有看左程云的写法，自己写的
string replaceString1(const string&str, const string&from, const string &to)
{
	//思路:找到所有出现指定exp的位置，判断是否是连续，进行替换
	string res;
	vector<int> posVec;
	int pos = str.find(from, 0);
	if (pos == -1)
		return str;

	while (pos != -1)
	{
		posVec.push_back(pos);
		pos = str.find(from, pos + 1);
	}

	int j = 0;
	for (int i = 0; i != str.length();)
	{
		if (j < posVec.size() && i == posVec[j])
		{
			if (j > 0 && posVec[j] - posVec[j - 1] == from.length()) 
			{
				i += from.length();
				++j;
				continue;
			}
			++j;
			res += to;
			i += from.length();
		}
		else
		{
			res += str[i];
			++i;
		}
	}

	return res;
}


int main()
{
	string str = "abc1abcabc1234abcabcabc5678";
	string from = "abc";
	string to = "XXXXX";
	cout << replaceString(str, from, to) << endl;
	cout << replaceString1(str, from, to) << endl;

	str = "abc";
	from = "123";
	to = "X";
	cout << replaceString(str, from, to) << endl;
	cout << replaceString1(str, from, to) << endl;

	system("pause");
	return 0;
}
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//第一个版本，能正常求解
string ConvertStringToCount(const std::string &str)
{
	int num = 1;
	char preChar = str[0];
	bool bFirst = true;
	string res;
	for (int i = 1; i != str.length(); ++i)
	{
		if (str[i] == preChar)
		{
			++num;
			preChar = str[i];
		}
		else
		{
			if (!bFirst)
				res += "_";

			res += string(1, preChar) + "_" + to_string(num);
			bFirst = false;



			preChar = str[i];
			num = 1;
		}
	}

	res += "_" + string(1, preChar) + "_" + to_string(num);
	return res;
}


//第二个版本，代码做优化,去掉preChar
//去掉bFirst变量
string ConvertStringToCount1(const std::string &str)
{
	if (str.empty()) return string("");
	int num = 1;
	string res;
	for (int i = 1; i != str.length(); ++i)
	{
		if (str[i] == str[i - 1])
			++num;
		else
		{
			res += string(1, str[i - 1]) + "_" + to_string(num) + "_";
			num = 1;
		}
	}

	res += string(1, str.back()) + "_" + to_string(num); //最后一个不加_就行了
	return res;
}

//补充问题，给定统计字符串，求给定index位置上原始字符

//这个版本是错的，没考虑到个数可能大于10，即_后面跟的不止1位的情况
//char getCharAt(std::string &cstr, int index) 
//{
//	
//	int count = 0;
//	for (int i=2;i<cstr.length();i+=4) //以4为步进，遍历cstr
//	{
//		count += cstr[i] - '0';
//		if (index <count) 
//		{
//			return cstr[i - 2];
//		}
//	}
//
//	return '\0';
//
//}

char getCharAt(std::string &cstr, int index)
{
	//字符串形如:a_1_b_100_c_2
	//解释为:a_1  b_100 c_2中间由_连接
	int count = 0;
	char cur;
	bool isNum = false;
	int tempNum = 0;
	for (int i = 0; i != cstr.length(); ++i)
	{
		if (cstr[i] != '_' && !isNum)//a,b,c这种字符
		{
			cur = cstr[i];
			continue; //可以去掉，但是写上更清晰其实
		}

		if (cstr[i] == '_' && !isNum) //a_1 中的_
		{
			isNum = true;
			continue;
		}

		if (cstr[i] == '_' && isNum) //中间衔接的_,所以这种东西一般都是退出当前阶段的时候进行结算
		{
			//进行结算
			count += tempNum;
			tempNum = 0;

			if (index < count)
				return cur;

			isNum = false;
			continue;
		}

		if (isNum) //数字阶段
			tempNum = tempNum * 10 + (cstr[i] - '0');
	}
	//最后还得结算一次
	count += tempNum;
	return index < count ? cur : '\0';
}


int main()
{
	//string str = "aaabbbbbbbbbbbbbbbbbbbbadddffc";
	string str = "aaabbbbbbbbbbbbbbbbbbbbadddffc";

	cout << ConvertStringToCount(str) << endl;
	cout << ConvertStringToCount1(str) << endl;

	cout << getCharAt(ConvertStringToCount1(str), 0) << endl;

	cout << getCharAt(ConvertStringToCount1(str), 9) << endl;
	cout << getCharAt(ConvertStringToCount1(str), 23) << endl;
	//cout << getCharAt(ConvertStringToCount1(str), 26) << endl;

	for (int i=0;i!=str.length();++i)
	{
		cout << getCharAt(ConvertStringToCount1(str), i);
	}

	system("pause");
	return 0;
}
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//��һ���汾�����������
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


//�ڶ����汾���������Ż�,ȥ��preChar
//ȥ��bFirst����
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

	res += string(1, str.back()) + "_" + to_string(num); //���һ������_������
	return res;
}

//�������⣬����ͳ���ַ����������indexλ����ԭʼ�ַ�

//����汾�Ǵ�ģ�û���ǵ��������ܴ���10����_������Ĳ�ֹ1λ�����
//char getCharAt(std::string &cstr, int index) 
//{
//	
//	int count = 0;
//	for (int i=2;i<cstr.length();i+=4) //��4Ϊ����������cstr
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
	//�ַ�������:a_1_b_100_c_2
	//����Ϊ:a_1  b_100 c_2�м���_����
	int count = 0;
	char cur;
	bool isNum = false;
	int tempNum = 0;
	for (int i = 0; i != cstr.length(); ++i)
	{
		if (cstr[i] != '_' && !isNum)//a,b,c�����ַ�
		{
			cur = cstr[i];
			continue; //����ȥ��������д�ϸ�������ʵ
		}

		if (cstr[i] == '_' && !isNum) //a_1 �е�_
		{
			isNum = true;
			continue;
		}

		if (cstr[i] == '_' && isNum) //�м��νӵ�_,�������ֶ���һ�㶼���˳���ǰ�׶ε�ʱ����н���
		{
			//���н���
			count += tempNum;
			tempNum = 0;

			if (index < count)
				return cur;

			isNum = false;
			continue;
		}

		if (isNum) //���ֽ׶�
			tempNum = tempNum * 10 + (cstr[i] - '0');
	}
	//��󻹵ý���һ��
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
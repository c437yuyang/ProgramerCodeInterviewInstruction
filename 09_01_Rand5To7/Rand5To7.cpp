// 29_01_Rand5ToRand7.cpp : 定义控制台应用程序的入口点。
//

//从一个给定的等概率的rand1to5，不使用其他的随机源产生一个rand1to7

#include <random>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;


#pragma region 原始题目
int rand1to5()
{
	static std::default_random_engine e;
	return (e() % 5) + 1;
}

//对于1-5的随机数，等于三就继续，小于3就返回0，大于3返回1
int binGetor()
{
	int i = 0;
	while ((i = rand1to5()) == 3);
	if (i < 3) i = 0;
	else if (i > 3) i = 1;
	return i;
}

int rand1to7()
{
	//1-7转化成0-6加1,0-6需要三位二进制
	int ret = 7; //使得进入循环
	while (ret > 6) //大于6了就继续重复循环，直到小于等于6
	{
		ret = 0;
		for (int i = 0; i != 3; ++i)
		{
			ret += binGetor()*pow(2, i);
		}
	}
	//得到了0-6的随机数，返回+1
	return ret + 1;
}
#pragma endregion


#pragma region 补充题目
//因为随机产生0-1的函数的概率是p,所以产生01和10的概率都是p(1-p)

//等概率返回0-1的小数
double rand0to1(int digit = 3) //digit代表小数点位数
{
	static std::default_random_engine e;
	const int coef = pow(10, digit);
	return e() % coef / double(coef);
}

//以概率p返回0
int rand01p(double p = 0.83)
{
	return rand0to1() < p ? 0 : 1;
}

//然后和刚才基本一样，转换成2进制来做,若是生成01，就返回0，若是生成10就返回1
int binGetor1()
{
	int num1, num2;
	num1 = rand01p();
	num2 = rand01p();
	while ((num1 && num2) || (!num1 && !num2))
	{
		num1 = rand01p();
		num2 = rand01p();
	}
	if (num1)
		return 1;
	if (num2)
		return 0;
	std::cout << "error" << endl;
	return -1;
}

//随机产生1-M的随机数
int rand1toM(int M)
{
	int digit = (int)ceil(log2(double(M)));
	int res = M; //先产生0->M-1的随机数
	while (res > M - 1)
	{
		res = 0;
		for (int i = 0; i != digit; ++i)
			res += binGetor1()*pow(2, i);
	}
	return res + 1;
}

#pragma endregion


int main()
{
#pragma region 测试rand1to5是否是等概率的
	//int hist[6] = { 0 };
	//const int num = 100000;
	//for (int i = 0; i != num; ++i)
	//{
	//	++hist[rand1to5()];
	//}

	//double histprob[6];
	//for (int i = 0; i != 6; ++i)
	//{
	//	histprob[i] = hist[i] / double(num);
	//}

	//copy(begin(histprob), end(histprob), ostream_iterator<double>(cout, " ")); //可以看到基本是等概率的  
#pragma endregion


#pragma region 测试rand1to7是否是等概率的
	//const int val = 7;
	//int hist[val + 1] = { 0 };
	//const int num = 100000;
	//for (int i = 0; i != num; ++i)
	//{
	//	++hist[rand1to7()];
	//}

	//double histprob[val + 1];
	//for (int i = 0; i != val + 1; ++i)
	//{
	//	histprob[i] = hist[i] / double(num);
	//}

	//copy(begin(histprob), end(histprob), ostream_iterator<double>(cout, " ")); //可以看到基本是等概率的  
#pragma endregion
	cout << endl;


#pragma region 测试rand01p是否等概率
	//int hist[2] = { 0 };
	//const int num = 100000;
	//for (int i = 0; i != num; ++i)
	//{
	//	++hist[rand01p()];
	//}

	//double histprob[2];
	//for (int i = 0; i != 2; ++i)
	//{
	//	histprob[i] = hist[i] / double(num);
	//}

	//copy(begin(histprob), end(histprob), ostream_iterator<double>(cout, " ")); //可以看到基本是准确的(digit只用了3)


#pragma endregion


#pragma region 测试rand1toM
	const int nTestTime = 100000;
	const int M = 20;
	map<int, int> hist;
	for (int i=0;i!=nTestTime;++i)
		++hist[rand1toM(20)];
	for (auto it = hist.begin(); it != hist.end(); ++it)
		cout << it->first << ":" << it->second / (double)nTestTime << endl; 
	//检验基本正确
#pragma endregion




	return 0;
}


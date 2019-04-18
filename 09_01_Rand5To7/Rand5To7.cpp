// 29_01_Rand5ToRand7.cpp : �������̨Ӧ�ó������ڵ㡣
//

//��һ�������ĵȸ��ʵ�rand1to5����ʹ�����������Դ����һ��rand1to7

#include <random>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;


#pragma region ԭʼ��Ŀ
int rand1to5()
{
	static std::default_random_engine e;
	return (e() % 5) + 1;
}

//����1-5����������������ͼ�����С��3�ͷ���0������3����1
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
	//1-7ת����0-6��1,0-6��Ҫ��λ������
	int ret = 7; //ʹ�ý���ѭ��
	while (ret > 6) //����6�˾ͼ����ظ�ѭ����ֱ��С�ڵ���6
	{
		ret = 0;
		for (int i = 0; i != 3; ++i)
		{
			ret += binGetor()*pow(2, i);
		}
	}
	//�õ���0-6�������������+1
	return ret + 1;
}
#pragma endregion


#pragma region ������Ŀ
//��Ϊ�������0-1�ĺ����ĸ�����p,���Բ���01��10�ĸ��ʶ���p(1-p)

//�ȸ��ʷ���0-1��С��
double rand0to1(int digit = 3) //digit����С����λ��
{
	static std::default_random_engine e;
	const int coef = pow(10, digit);
	return e() % coef / double(coef);
}

//�Ը���p����0
int rand01p(double p = 0.83)
{
	return rand0to1() < p ? 0 : 1;
}

//Ȼ��͸ղŻ���һ����ת����2��������,��������01���ͷ���0����������10�ͷ���1
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

//�������1-M�������
int rand1toM(int M)
{
	int digit = (int)ceil(log2(double(M)));
	int res = M; //�Ȳ���0->M-1�������
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
#pragma region ����rand1to5�Ƿ��ǵȸ��ʵ�
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

	//copy(begin(histprob), end(histprob), ostream_iterator<double>(cout, " ")); //���Կ��������ǵȸ��ʵ�  
#pragma endregion


#pragma region ����rand1to7�Ƿ��ǵȸ��ʵ�
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

	//copy(begin(histprob), end(histprob), ostream_iterator<double>(cout, " ")); //���Կ��������ǵȸ��ʵ�  
#pragma endregion
	cout << endl;


#pragma region ����rand01p�Ƿ�ȸ���
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

	//copy(begin(histprob), end(histprob), ostream_iterator<double>(cout, " ")); //���Կ���������׼ȷ��(digitֻ����3)


#pragma endregion


#pragma region ����rand1toM
	const int nTestTime = 100000;
	const int M = 20;
	map<int, int> hist;
	for (int i=0;i!=nTestTime;++i)
		++hist[rand1toM(20)];
	for (auto it = hist.begin(); it != hist.end(); ++it)
		cout << it->first << ":" << it->second / (double)nTestTime << endl; 
	//���������ȷ
#pragma endregion




	return 0;
}


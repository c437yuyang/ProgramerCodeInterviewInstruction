#include <iostream>
using namespace std;

//�ⷨ1:��1X2X..XN���ж��ٸ�����5
////O(Nlog5(N))
int zeroNum1(int N)
{
	if (N < 5) return 0;
	int num_of_5 = 1;
	for (int i = 10; i <= N; i += 5) //��10��ʼ��������ֱ��,����ÿ�ο϶��Ǽ�5
	{
		int cur = i;
		while (cur % 5 == 0) //ֻ���ܵ�ǰ���������5�ܳ�����������п��ܺ��и����5������
		{
			++num_of_5;
			cur /= 5; //��ǰ���ܳ������ͳ���5����
		}
	}
	return num_of_5;
}

//�ⷨ2:�����,������Z = N/5+N/(5^2) + ...
int zeroNum2(int N) //O(log5(N))
{
	int res = 0;
	while (N != 0)
	{
		N /= 5;
		res += N;
	}

	return res;
}

//�������⣬ģ���ŵ�һ���ⷨ����
int rightOne1(int num)
{
	int res = 0; //2�����ӵ�����

	for (int i = 1; i <= num; ++i)
	{
		while (i % 2 == 0)
		{
			++res;
			i /= 2;
		}
	}
	return res;
}
//ģ�µ�һ���ĵڶ��ֽⷨ����
int rightOne2(int num)
{
	int res = 0; //2�����ӵ�����
	while (num != 0)
	{
		num >>= 1;
		res += num;
	}
	return res;
}

//�ⷨ2û����

int main()
{
	int num = 1000000000;
	//cout << zeroNum1(num) << endl;
	//cout << zeroNum2(num) << endl;

	//num = 50;
	//cout << zeroNum1(num) << endl;
	//cout << zeroNum2(num) << endl;

	//cout << rightOne1(num) << endl;
	cout << rightOne2(num) << endl;

	system("pause");
	return 0;
}
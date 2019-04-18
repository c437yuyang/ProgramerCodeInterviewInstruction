#include <iostream>
using namespace std;

//解法1:找1X2X..XN中有多少个因子5
////O(Nlog5(N))
int zeroNum1(int N)
{
	if (N < 5) return 0;
	int num_of_5 = 1;
	for (int i = 10; i <= N; i += 5) //从10开始遍历可以直接,而且每次肯定是加5
	{
		int cur = i;
		while (cur % 5 == 0) //只可能当前数本身除以5能除尽，后面才有可能含有更多的5的因子
		{
			++num_of_5;
			cur /= 5; //当前数能除尽，就除以5再找
		}
	}
	return num_of_5;
}

//解法2:分组解,最后就是Z = N/5+N/(5^2) + ...
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

//进阶问题，模仿着第一个解法做的
int rightOne1(int num)
{
	int res = 0; //2的因子的数量

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
//模仿第一个的第二种解法做的
int rightOne2(int num)
{
	int res = 0; //2的因子的数量
	while (num != 0)
	{
		num >>= 1;
		res += num;
	}
	return res;
}

//解法2没看了

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
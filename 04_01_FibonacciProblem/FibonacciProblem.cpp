#include <iostream>
using namespace std;



int FibonacciWithRecursive(int n)
{
	if (n == 0) return 0;
	if (n == 1 || n == 2) return 1;
	else return FibonacciWithRecursive(n - 1) + FibonacciWithRecursive(n - 2);
}

int FibonacciNoRecursive(int n) //O(N)
{
	if (n == 0) return 0;
	if (n == 1 || n == 2) return 1;
	int pre1 = 1, pre2 = 1;
	int res = 0;
	for (int i = 3; i <= n; ++i)
	{
		res = pre1 + pre2;
		pre1 = pre2;
		pre2 = res;
	}
	return res;
}

int main()
{
	cout << FibonacciWithRecursive(22) << endl;
	cout << FibonacciNoRecursive(22) << endl;
	system("pause");
	return 0;
}


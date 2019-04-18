#include <iostream>
using namespace std;



//如果n==0,代表除尽了，那么此时最大公约数就是m
//如果不等于0，则m = nq + r
//定理表明:m和n的gcd等于n和r的gcd
int gcd(int m, int n) 
{
	return n == 0 ? m : gcd(n, m%n);
}


int main()
{

	system("pause");
	return 0;
}
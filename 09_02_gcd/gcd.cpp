#include <iostream>
using namespace std;



//���n==0,��������ˣ���ô��ʱ���Լ������m
//���������0����m = nq + r
//�������:m��n��gcd����n��r��gcd
int gcd(int m, int n) 
{
	return n == 0 ? m : gcd(n, m%n);
}


int main()
{

	system("pause");
	return 0;
}
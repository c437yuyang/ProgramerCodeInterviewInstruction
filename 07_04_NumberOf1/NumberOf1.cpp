#include <iostream>
using namespace std;


int count1(int num)
{
	int cnt = 0;
	while (num != 0)
	{
		cnt += num & 1;
		num = ((unsigned int)num) >> 1;
	}
	return cnt;
}

int count2(int num)
{
	int cnt = 0; 
	while (num != 0)
	{
		++cnt;
		num &= (num - 1); //移出掉最右边的1
	}
	return cnt;
}


 int count3(int n) {
	int res = 0;
	while (n != 0) {
		n -= n & (~n + 1); //移出掉最右边的1
		res++;
	}
	return res;
}

int main()

{

	cout << count1(7) << endl;
	cout << count1(0x555) << endl;

	cout << count2(7) << endl;
	cout << count2(0x555) << endl;

	system("pause");
	return 0;
}


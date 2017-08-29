#include <iostream>
using namespace std;


void SwapWithoutTmp(int &a, int &b) 
{
	a = a^b;
	b = a^b;
	a = a^b;
}


int main()
{
	int a = 3, b = 4;
	SwapWithoutTmp(a, b);

	cout << a << " " << b << endl;

	system("pause");
	return 0;
}


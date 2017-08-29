
#include "stdafx.h"
#include <iostream>
using namespace std;


#pragma region ���Լ��İ汾
int add(int a, int b)
{
	int addRes = a^b;//�����ǽ�λ�Ľ��
	int onlyCarryRes = (a&b) << 1;
	while (onlyCarryRes != 0)
	{
		int tmp1 = addRes, tmp2 = onlyCarryRes;
		addRes = tmp1 ^ tmp2;
		onlyCarryRes = (tmp1 & tmp2) << 1;
	}
	return addRes;

}

int neg(int a) {
	return add(~a, 1);
}

int sub(int a, int b)
{
	return add(a, neg(b));
}

int mult(int a, int b)
{
	int res = 0;

	while (b != 0)
	{
		res += b & (1) ? a : 0; //ȡb����һλ
		a <<= 1;
		b = ((unsigned int)b) >> 1; //C++���޷�������λҪ��ת�����޷�����������������߲�0�����Ƿ���λ
	}
	return res;
}

#pragma endregion


#pragma region ����Ƶİ汾
int add1(int a, int b) {
	int sum = a;
	while (b != 0) {
		sum = a ^ b;
		b = (a & b) << 1;
		a = sum;
	}
	return sum;
}
#pragma endregion



int main()
{


	cout << add(3, 4) << endl;
	cout << add(3, 1) << endl;
	cout << add(3, 5) << endl;
	cout << add(3, 10) << endl;
	cout << sub(3, 10) << endl;
	cout << sub(3, 1) << endl;
	cout << sub(3, 7) << endl;
	cout << mult(3, 7) << endl;
	cout << mult(-3, 7) << endl;
	cout << mult(3, -7) << endl;

	system("pause");
	return 0;
}


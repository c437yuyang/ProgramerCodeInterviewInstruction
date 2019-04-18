#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //ʹ���ɵ��ڴ�dump�����ڴ�����ľ������Ϊֹ
#include <stdlib.h> 
#include <crtdbg.h>
#define CheckMemoryLeak _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG )| _CRTDBG_LEAK_CHECK_DF)
#endif 

#include <iostream>
#include <boost/progress.hpp>
using namespace std;


#pragma region 쳲��������е����ַ���
//����1:O(2^N)
int FibonacciWithRecursive(int n)
{
	if (n == 0) return 0;
	if (n == 1 || n == 2) return 1;
	else return FibonacciWithRecursive(n - 1) + FibonacciWithRecursive(n - 2);
}

//����2:O(N)
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


//����д���������⣬����multiMatrix(m1,m2,m1) m1Ϊ3*2,m2Ϊ2*3,������Ϊ3*3�����ǳ����˻�����m1���棬�������·����ڴ�Ź�
void muliMatrix(int*m1, int r1, int c1, int* m2, int r2, int c2, int *res) {//Ŀǰ����˵ֻ�з����������ȷ��
	if (c1 != r2 || res == NULL) return;
	int *m1_tmp = new int[r1*c1]; //����in-place����
	int *m2_tmp = new int[r2*c2];

	memcpy(m1_tmp, m1, r1*c1 * sizeof(int));
	memcpy(m2_tmp, m2, r2*c2 * sizeof(int));
	memset(res, 0, sizeof(int)*r1*c2); //�����ȿ����ߣ�in-place����ȷ

	for (int i = 0; i < r1; i++) {
		for (int k = 0; k < r2; k++) {
			for (int j = 0; j < c2; j++) {
				res[i*c2 + j] += m1_tmp[i*c1 + k] * m2_tmp[k*c2 + j];
			}
		}
	}
	delete[] m1_tmp;
	delete[] m2_tmp;
}
//�ɵ��������з����ڴ�
void matrixPower(int* m, int n, int p, int *res) { //ֻ���Ƿ���ֻ�з��������η�
	if (res == NULL) return;
	// �Ȱ�res��Ϊ��λ��������������е�1��
	for (int i = 0; i < n; i++) { //������Ϊ�Ƿ�����Է��󣬲����Ǿ�����ʽ�仯
		res[i*n + i] = 1;
	}
	int *tmp = m;
	for (; p != 0; p >>= 1) {
		if ((p & 1) != 0) {
			muliMatrix(res, n, n, tmp, n, n, res); //res = res*tmp
		}
		muliMatrix(tmp, n, n, tmp, n, n, tmp); //tmp = tmp*tmp
	}
}

//����3:O(logN)
int FibonacciUseStateEquation(int n) {
	if (n < 1) {
		return 0;
	}
	if (n == 1 || n == 2) {
		return 1;
	}
	int base[] = { 1,1,1,0 };
	int res[4] = { 0 };
	matrixPower(base, 2, n - 2, res);
	return res[0 * 2 + 0] + res[1 * 2 + 0];
}
#pragma endregion


//��������2:

//����1:
int cowProblemRecursive(int N) 
{
	if (N < 1) return 0;
	if (N == 1 || N == 2 || N == 3) return N;
	else
		return cowProblemRecursive(N - 1) + cowProblemRecursive(N - 3);
}

int cowProblemNoRecursive(int n) 
{
	if (n < 1) return 0;
	if (n == 1 || n== 2 || n == 3) return n;

	int C_3 = 1; //����ǰ
	int C_2 = 2; //����ǰ
	int C_1 = 3; //һ��ǰ
	int res = 0;

	//��һ��������Էǳ��򵥵ؽ�����⣬���ǿռ临�Ӷ�O(N)��
	for (int i=4;i<=n;++i)
	{
		res = C_1 + C_3; //��������Ļ�����ʵ���Ǳ���֮��Ĵ���
		int tmp = C_1;//�����һ������
		C_1 = res;
		C_3 = C_2;
		C_2 = tmp;
	}

	return res;
}


void printMatrix(int *p, int m, int n)
{
	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != n; ++j)
		{
			cout << p[i*n + j] << " ";
		}
		cout << endl;
	}
}

int main()
{
#ifdef _DEBUG
	CheckMemoryLeak;
#endif
	cout << FibonacciWithRecursive(22) << endl;
	cout << FibonacciNoRecursive(22) << endl;
	cout << FibonacciUseStateEquation(22) << endl;


	for (int i=4;i!=10;++i)
	{
		cout << cowProblemRecursive(i) << endl;
		cout << cowProblemNoRecursive(i) << endl;
	}


	int time = 20000;
	int n = 400;
	{
		boost::progress_timer t1;

		for (int i=0;i!=time;++i)
		{
			FibonacciWithRecursive(n);
		}

	}

	{
		boost::progress_timer t1;

		for (int i = 0; i != time; ++i)
		{
			FibonacciNoRecursive(n);
		}

	}


	system("pause");
	return 0;
}


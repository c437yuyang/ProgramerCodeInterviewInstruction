#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //使生成的内存dump包含内存块分配的具体代码为止
#include <stdlib.h> 
#include <crtdbg.h>
#define CheckMemoryLeak _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG )| _CRTDBG_LEAK_CHECK_DF)
#endif 

#include <iostream>
#include <boost/progress.hpp>
using namespace std;


#pragma region 斐波那契数列的三种方法
//方法1:O(2^N)
int FibonacciWithRecursive(int n)
{
	if (n == 0) return 0;
	if (n == 1 || n == 2) return 1;
	else return FibonacciWithRecursive(n - 1) + FibonacciWithRecursive(n - 2);
}

//方法2:O(N)
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


//这样写还是有问题，比如multiMatrix(m1,m2,m1) m1为3*2,m2为2*3,乘完了为3*3，但是乘完了还是在m1里面，必须重新分配内存才够
void muliMatrix(int*m1, int r1, int c1, int* m2, int r2, int c2, int *res) {//目前可以说只有方阵相乘是正确的
	if (c1 != r2 || res == NULL) return;
	int *m1_tmp = new int[r1*c1]; //兼容in-place处理
	int *m2_tmp = new int[r2*c2];

	memcpy(m1_tmp, m1, r1*c1 * sizeof(int));
	memcpy(m2_tmp, m2, r2*c2 * sizeof(int));
	memset(res, 0, sizeof(int)*r1*c2); //必须先拷贝走，in-place才正确

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
//由调用者自行分配内存
void matrixPower(int* m, int n, int p, int *res) { //只考虑方阵，只有方阵才能算次方
	if (res == NULL) return;
	// 先把res设为单位矩阵，相等于整数中的1。
	for (int i = 0; i < n; i++) { //这里因为是方阵乘以方阵，不考虑矩阵形式变化
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

//方法3:O(logN)
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


//附加问题2:

//方法1:
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

	int C_3 = 1; //三年前
	int C_2 = 2; //两年前
	int C_1 = 3; //一年前
	int res = 0;

	//用一个数组可以非常简单地解决问题，但是空间复杂度O(N)了
	for (int i=4;i<=n;++i)
	{
		res = C_1 + C_3; //不用数组的话，其实就是变量之间的传递
		int tmp = C_1;//三年的一次往后
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


#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //使生成的内存dump包含内存块分配的具体代码为止
#include <stdlib.h> 
#include <crtdbg.h>
#define CheckMemoryLeak _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG )| _CRTDBG_LEAK_CHECK_DF)
#endif 

#include <iostream>
#include <deque>
using namespace std;

void SlidingWindowMaxArray(int arr[], int n, int w, int maxArr[])
{
	deque<int> qmax;
	int idx = 0;
	for (int i = 0; i != n; ++i)
	{
		while (!qmax.empty() && arr[i] >= arr[qmax.back()])
		{
			qmax.pop_back();
		}
		qmax.push_back(i);
		
		if (qmax.front() == i - w)
		{
			qmax.pop_front();
		}

		if (i >= w - 1) //w为3时，从i=2开始，满了一个窗口，开始更新
		{
			maxArr[idx++] = arr[qmax.front()];
		}
	}
}


int main()
{
#ifdef _DEBUG
	CheckMemoryLeak;
#endif

	const int n = 8;
	const int w = 3;
	const int n1 = n - w + 1;

	int arr[n] = { 4,3,5,4,3,3,6,7 };
	int res[n1];

	SlidingWindowMaxArray(arr, n, w, res);

	system("pause");
	return 0;
}
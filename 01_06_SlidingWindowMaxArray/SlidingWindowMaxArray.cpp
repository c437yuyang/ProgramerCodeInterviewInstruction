#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //ʹ���ɵ��ڴ�dump�����ڴ�����ľ������Ϊֹ
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

		if (i >= w - 1) //wΪ3ʱ����i=2��ʼ������һ�����ڣ���ʼ����
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
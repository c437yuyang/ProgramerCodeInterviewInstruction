#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //使生成的内存dump包含内存块分配的具体代码为止
#include <stdlib.h> 
#include <crtdbg.h>
#define CheckMemoryLeak _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG )| _CRTDBG_LEAK_CHECK_DF)
#endif 

#include <iostream>
#include <algorithm>
using namespace std;

#pragma region 常规的暴力做法
//找到左边和右边第一个小于arr[pos]的位置(left,right分别是最后一个大于等于的位置)
void findFirstLeftAndRightLT(int arr[], int n, int pos, int &left, int &right)
{
	if (pos == 0)
		left = 0;
	else
	{
		for (left = pos - 1; left >= 0 && arr[left] >= arr[pos]; --left);
		left += 1;
	}
	if (pos == n - 1)
		right = n - 1;
	else
	{
		for (right = pos + 1; right <= n - 1 && arr[right] >= arr[pos]; ++right);
		right -= 1;
	}



}
int maxRecFromBottom(int height[], int n)
{
	int max = -INT_MAX;

	for (int i = 0; i != n; ++i)
	{
		int left, right;
		findFirstLeftAndRightLT(height, n, i, left, right);

		int cur = (right - left + 1) * height[i];
		max = std::max(cur, max);
	}
	return max;
}
int MaximalRectangle(int arr[], int m, int n)
{

	int *height = new int[n]();
	int max = -INT_MAX;
	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != n; ++j)
		{
			height[j] = arr[i*n + j] == 0 ? 0 : height[j] + 1;
		}

		int cur = maxRecFromBottom(height, n);
		max = std::max(max, cur);
	}
	return max;
}
#pragma endregion




int main()
{
#ifdef _DEBUG
	CheckMemoryLeak;
#endif


	int arr[3 * 4] = { 1,0,1,1,
					1,1,1,1,
					1,1,1,0 };

	cout << MaximalRectangle(arr, 3, 4) << endl;
	system("pause");
	return 0;
}
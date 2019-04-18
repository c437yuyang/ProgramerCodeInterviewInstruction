#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //使生成的内存dump包含内存块分配的具体代码为止
#include <stdlib.h> 
#include <crtdbg.h>
#define CheckMemoryLeak _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG )| _CRTDBG_LEAK_CHECK_DF)
#endif 

#include <iostream>
#include <algorithm>
#include <stack>
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
//找到左右能扩的最远值后，对这一排的这些每个位置都计算最大矩形
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
//求对于每一排结尾的最大矩形
int MaximalRectangle(int arr[], int m, int n)
{

	int *height = new int[n]();
	int max = -INT_MAX;
	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != n; ++j)
			height[j] = arr[i*n + j] == 0 ? 0 : height[j] + 1;
		int cur = maxRecFromBottom(height, n);
		max = std::max(max, cur);
	}
	return max;
}
#pragma endregion


#pragma region 用单调栈的做法
int maxRecFromBottom1(int height[], int n)
{
	int max = -INT_MAX;
	stack<int> s;
	//找左边和右边第一个小于此数的单调栈，小于等于栈顶都弹出(非严格单调栈，但最终结果正确)
	for (int i = 0; i != n; ++i)
	{
		if (s.empty() || height[s.top()] < height[i])
			s.push(i);
		else
		{
			while (!s.empty() && height[s.top()] >= height[i])
			{
				int tmp = s.top();
				s.pop();
				//弹出一次计算一次
				if (s.size() == 0)
					max = std::max((i - 1 - 0 + 1)*height[tmp], max);
				else
					max = std::max((i - 1 - s.top() - 1 + 1) *height[tmp], max);
			}
			s.push(i);
		}

	}

	//结算栈顶还有的
	while (!s.empty())
	{
		if (s.size() == 1) //全局最小值
			max = std::max((n - 1 - 0 + 1)*height[s.top()], max);
		else
			max = std::max((n - 1 - s.top() - 1 + 1)*height[s.top()], max);
		s.pop();
	}
	return max;
}
int MaximalRectangle1(int arr[], int m, int n)
{

	int *height = new int[n]();
	int max = -INT_MAX;
	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != n; ++j)
			height[j] = arr[i*n + j] == 0 ? 0 : height[j] + 1;
		int cur = maxRecFromBottom1(height, n);
		max = std::max(max, cur);
	}
	return max;
}
#pragma endregion

#pragma region 左程云的版本,代码稍微简化了一点，单调栈部分栈顶为空的判断部分
int maxRecFromBottom2(int height[], int n)
{
	int max = -INT_MAX;
	stack<int> s;
	//找左边和右边第一个小于此数的单调栈，小于等于栈顶都弹出(非严格单调栈，但最终结果正确)
	for (int i = 0; i != n; ++i)
	{
		while (!s.empty() && height[s.top()] >= height[i])
		{
			//这一块可以简单点
			int j = s.top();
			s.pop();
			int k = s.empty() ? -1 : s.top();
			max = std::max((i - k - 1)*height[j], max); //(i-1) - (k+1) + 1
		}
		s.push(i);
	}

	//结算栈顶还有的
	while (!s.empty())
	{
		int j = s.top();
		s.pop();
		int k = s.empty() ? -1 : s.top();
		max = std::max((n - k - 1)*height[j], max); //(n-1)-(k+1)+1
	}
	return max;
}
int MaximalRectangle2(int arr[], int m, int n)
{

	int *height = new int[n]();
	int max = -INT_MAX;
	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != n; ++j)
			height[j] = arr[i*n + j] == 0 ? 0 : height[j] + 1;
		int cur = maxRecFromBottom2(height, n);
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
	cout << MaximalRectangle1(arr, 3, 4) << endl;
	cout << MaximalRectangle2(arr, 3, 4) << endl;


	int arr1[5 * 4] = { 1,0,1,1,
						1,1,1,1,
						1,1,1,0,
						1,1,0,1,
						1,1,1,1 };

	cout << MaximalRectangle(arr1, 5, 4) << endl;
	cout << MaximalRectangle1(arr1, 5, 4) << endl;
	cout << MaximalRectangle2(arr1, 5, 4) << endl;



	system("pause");
	return 0;
}
#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //ʹ���ɵ��ڴ�dump�����ڴ�����ľ������Ϊֹ
#include <stdlib.h> 
#include <crtdbg.h>
#define CheckMemoryLeak _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG )| _CRTDBG_LEAK_CHECK_DF)
#endif 

#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

#pragma region ����ı�������
//�ҵ���ߺ��ұߵ�һ��С��arr[pos]��λ��(left,right�ֱ������һ�����ڵ��ڵ�λ��)
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
//�ҵ�������������Զֵ�󣬶���һ�ŵ���Щÿ��λ�ö�����������
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
//�����ÿһ�Ž�β��������
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


#pragma region �õ���ջ������
int maxRecFromBottom1(int height[], int n)
{
	int max = -INT_MAX;
	stack<int> s;
	//����ߺ��ұߵ�һ��С�ڴ����ĵ���ջ��С�ڵ���ջ��������(���ϸ񵥵�ջ�������ս����ȷ)
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
				//����һ�μ���һ��
				if (s.size() == 0)
					max = std::max((i - 1 - 0 + 1)*height[tmp], max);
				else
					max = std::max((i - 1 - s.top() - 1 + 1) *height[tmp], max);
			}
			s.push(i);
		}

	}

	//����ջ�����е�
	while (!s.empty())
	{
		if (s.size() == 1) //ȫ����Сֵ
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

#pragma region ����Ƶİ汾,������΢����һ�㣬����ջ����ջ��Ϊ�յ��жϲ���
int maxRecFromBottom2(int height[], int n)
{
	int max = -INT_MAX;
	stack<int> s;
	//����ߺ��ұߵ�һ��С�ڴ����ĵ���ջ��С�ڵ���ջ��������(���ϸ񵥵�ջ�������ս����ȷ)
	for (int i = 0; i != n; ++i)
	{
		while (!s.empty() && height[s.top()] >= height[i])
		{
			//��һ����Լ򵥵�
			int j = s.top();
			s.pop();
			int k = s.empty() ? -1 : s.top();
			max = std::max((i - k - 1)*height[j], max); //(i-1) - (k+1) + 1
		}
		s.push(i);
	}

	//����ջ�����е�
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
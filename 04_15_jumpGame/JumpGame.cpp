#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

const int maxInt = 65536;

int process(int *arr, int n, int i);
int jumpGame(int *arr, int n)
{
	return process(arr, n, 0);
}


//意义:从i位置到最右的数组上，跳到右边界最少需要的步数
int process(int *arr, int n, int i)
{
	if (i > n - 1) return -maxInt; //不可行
	if (i == n - 1) //到了最右边前面一个，下一次只能选择跳一步
		return 0;

	int min = maxInt;
	for (int j = 1; j <= arr[i]; ++j)
	{
		int tmp = process(arr, n, i + j);
		if (tmp >= 0)
			min = std::min(tmp + 1, min);
	}
	if (min < 0 || min > maxInt)
		return -1;
	return min;



}

//记忆回溯法
int process1(int *arr, int n, int i, vector<int> &dp);
int jumpGame1(int *arr, int n)
{
	vector<int> dp(n, -1);
	dp[n - 1] = 0;
	dp[n - 2] = 1;
	return process1(arr, n, 0, dp);
}


//意义:从i位置到最右的数组上，跳到右边界最少需要的步数
int process1(int *arr, int n, int i, vector<int> &dp)
{
	if (dp[i] != -1)
	{
		return dp[i];
	}

	if (i > n - 1) return -maxInt; //不可行
	if (i == n - 1) //到了最右边前面一个，下一次只能选择跳一步
		return 0;

	int min = maxInt;
	for (int j = 1; j <= arr[i]; ++j)
	{
		int tmp = process(arr, n, i + j);
		if (tmp >= 0)
			min = std::min(tmp + 1, min);
	}
	if (min < 0 || min > maxInt)
		return -1;

	dp[i] = min;
	return dp[i];
}


#pragma region 版本3，动态规划版本

int jumpGame2(int *arr, int n)
{
	vector<int> dp(n, -1);
	dp[n - 1] = 0;
	dp[n - 2] = 1;
	for (int i = n - 3; i >= 0; --i)
	{
		int min = maxInt;
		for (int j = 1; j <= arr[i]; ++j)
			if (i + j <= n - 1)
				min = std::min(dp[i + j] + 1, min);
		dp[i] = min;
	}

	return dp[0];
}

#pragma endregion



int main()
{
	int arr[] = { 3,2,3,1,1,4 };
	//int arr[] = { 3,1,1,1 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << jumpGame(arr, n) << endl;
	cout << jumpGame1(arr, n) << endl;
	cout << jumpGame2(arr, n) << endl;


	int arr1[] = { 3,1,1,1 };
	n = sizeof(arr1) / sizeof(arr1[0]);

	cout << jumpGame(arr1, n) << endl;
	cout << jumpGame1(arr1, n) << endl;
	cout << jumpGame2(arr1, n) << endl;



	system("pause");
	return 0;
}


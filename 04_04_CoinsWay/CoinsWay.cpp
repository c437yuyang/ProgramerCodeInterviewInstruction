#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <boost\progress.hpp>
#include <boost\timer.hpp>
#include <array.h>
#include <unordered_map>
#include <map>
using namespace std;
using namespace yxp_utility;
const int maxInt = 65536;

#pragma region 暴力递归版本
int process1(int *arr, int i, int j, int aim);
int coinsWay1(int *arr, int n, int aim)
{
	if (aim == 0) return 1;

	int res = process1(arr, 0, n - 1, aim);
	return  res < 0 ? 0 : res;

}

//函数意义:从i-n-1位置上的数里面选，要完成这个的方法数
int process1(int *arr, int i, int j, int aim)
{
	if (aim == 0) return 1;

	if (i == j)
	{
		if (aim % arr[i]) return INT_MIN;
		else return 1;
	}

	int res = 0;
	int k = aim / arr[i];
	for (int l = 0; l <= k; ++l)
	{
		int tmp = process1(arr, i + 1, j, aim - l*arr[i]);
		res += tmp < 0 ? 0 : tmp;
	}

	return res;

}

#pragma endregion


#pragma region 自顶向下备忘录版本

int process2(int *arr, int i, int j, int aim, vector<vector<int>> &dp);
int coinsWay2(int *arr, int n, int aim)
{
	if (aim == 0) return 1;
	vector<vector<int>> dp(n);
	for (int i = 0; i != n; ++i)
		dp[i].resize(aim + 1);
	for (int i = 0; i != n; ++i)
		for (int j = 0; j != aim + 1; ++j)
			dp[i][j] = INT_MIN;


	int res = process2(arr, 0, n - 1, aim, dp);
	return  res < 0 ? 0 : res;

}

//函数意义:从i-n-1位置上的数里面选，要完成这个的方法数
int process2(int *arr, int i, int j, int aim, vector<vector<int>> &dp)
{

	if (dp[i][aim] != INT_MIN)
		return dp[i][aim];

	if (aim == 0) return 1;

	if (i == j)
	{
		if (aim % arr[i]) return INT_MIN;
		else return 1;
	}

	int res = 0;
	int k = aim / arr[i];
	for (int l = 0; l <= k; ++l)
	{
		int tmp = process2(arr, i + 1, j, aim - l*arr[i], dp);
		res += tmp < 0 ? 0 : tmp;
		dp[i][aim] = res;
	}

	return res;

}



#pragma endregion

#pragma region 用哈希表做备忘录的回溯法
struct Node
{
	int aim;
	int i;
	Node(int i, int aim) :i(i), aim(aim) {}
};

struct NodeCompare
{
	bool operator()(const Node&left, const Node&other)const
	{
		return other.aim == left.aim&&other.i == left.i;
	}
};

struct HashFunc
{
	std::size_t operator()(const Node &key) const
	{
		using std::size_t;
		using std::hash;

		return hash<int>()(key.aim)
			^ (hash<int>()(key.i) << 1);
	}
};
typedef unordered_map<Node, int, HashFunc, NodeCompare> NodeMap;
//typedef map<Node,int,NodeCompare> NodeMap;
bool findNode(NodeMap& dp, Node& key)
{
	return dp.find(key) != dp.end();
}


int process2_1(int *arr, int i, int j, int aim, NodeMap &dp);
int coinsWay2_1(int *arr, int n, int aim)
{
	if (aim == 0) return 1;
	//vector<vector<int>> dp(n);
	//for (int i = 0; i != n; ++i)
	//	dp[i].resize(aim + 1);
	NodeMap dp;
	for (int i = 0; i != n; ++i)
		for (int j = 0; j != aim + 1; ++j)
			//dp[i][j] = INT_MIN;
			dp[Node(i, j)] = INT_MIN;


	int res = process2_1(arr, 0, n - 1, aim, dp);
	return  res < 0 ? 0 : res;

}



//函数意义:从i-n-1位置上的数里面选，要完成这个的方法数
int process2_1(int *arr, int i, int j, int aim, NodeMap  &dp)
{
	Node curNode(i, aim);
	if (findNode(dp, curNode)
		&& dp[curNode] != INT_MIN)
		return dp[curNode];

	int res = INT_MIN;
	if (aim == 0)
	{
		res = 1;
		dp[curNode] = res;
		return res;
	}
	if (i == j)
	{
		if (aim % arr[i])
			res = INT_MIN;
		else
			res = 1;
		dp[curNode] = res;
		return res;
	}

	res = 0;
	int k = aim / arr[i];
	for (int l = 0; l <= k; ++l)
	{
		int tmp = process2_1(arr, i + 1, j, aim - l*arr[i], dp);
		res += tmp < 0 ? 0 : tmp;
		dp[curNode] = res;
	}

	return res;

}

#pragma endregion


#pragma region 动态规划版本,空间O(aim*n)
int coinsWay3(int *arr, int n, int aim)
{
	if (aim == 0) return 1;
	//vector<vector<int>> dp(n);
	_2dArray<int> dp(n, aim + 1);
	//for (int i = 0; i != n; ++i)
	//	dp[i].resize(aim + 1);
	//for (int i = 0; i != n; ++i)
	//	for (int j = 0; j != aim + 1; ++j)
	//		dp[i][j] = 0;

	for (int i = 0; i != n; ++i) //第一列全部1
		dp[i][0] = 1;

	for (int j = 1; j <= aim; ++j)
	{
		if (j%arr[n - 1] == 0)
			dp[n - 1][j] = 1;
	}

	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = 1; j <= aim; ++j)
		{
			int k = j / arr[i]; //错误在这里，写成了aim/arr[i],从递归转换过来的时候一定要注意，哪些是在变的，哪些是没变的
			int res = 0;
			for (int l = 0; l <= k; ++l)
			{
				int tmp = dp[i + 1][j - l*arr[i]]; //这里是j-xxx不是aim-了!!!
				res += tmp == 0 ? 0 : tmp;
			}
			dp[i][j] = res;
		}
	}


	return dp[0][aim];

}
#pragma endregion

//优化空间复杂度
int coinsWay4(int *arr, int n, int aim)
{
	if (aim == 0) return 1;
	_1dArray<int> dp(aim + 1);
	_1dArray<int> pre(aim + 1);
	dp[0] = 1;
	for (int j = 1; j <= aim; ++j)
	{
		if (j%arr[n - 1] == 0)
			dp[j] = 1;
	}

	for (int i = n - 2; i >= 0; --i)
	{
		pre = dp;
		for (int j = 1; j <= aim; ++j)
		{
			int k = j / arr[i]; //错误在这里，写成了aim/arr[i],从递归转换过来的时候一定要注意，哪些是在变的，哪些是没变的
			int res = 0;
			for (int l = 0; l <= k; ++l)
			{
				//int tmp = pre[j - l*arr[i]];
				//res += tmp == 0 ? 0 : tmp;
				res += pre[j - l*arr[i]];
			}
			dp[j] = res;
		}
	}


	return dp[aim];

}


int main()
{
	int arr[] = { 5,10,25,1 };
	int n = 4;
	cout << coinsWay2(arr, n, 0) << endl;
	cout << coinsWay2(arr, n, 15) << endl;
	cout << coinsWay2(arr, n, 2) << endl;
	cout << coinsWay2_1(arr, n, 2) << endl;

	cout << coinsWay3(arr, n, 0) << endl;
	cout << coinsWay3(arr, n, 15) << endl;
	cout << coinsWay3(arr, n, 2) << endl;

	cout << coinsWay3(arr, n, 2000) << endl;
	cout << coinsWay1(arr, n, 2000) << endl;
	cout << coinsWay2(arr, n, 2000) << endl;
	cout << coinsWay2_1(arr, n, 2000) << endl;
	cout << coinsWay4(arr, n, 2000) << endl;

#pragma region 性能测试,VS别测了，估计是对递归做了优化，比自己写的还快

#pragma endregion


	//debug下，最快的是动态规划矩阵版，其次是空间优化，其次是递归，最后是带备忘录的递归
	//release下，最快的是递归!!!,其次是动态规划矩阵版，然后是带备忘录的递归，最后是空间优化的动态规划

	int nTestTime = 200;
	int aim = 2000;
	clock_t start;
	start = clock();
	for (int i = 0; i != nTestTime; ++i)
		coinsWay1(arr, n, aim);
	cout << clock() - start << endl;

	start = clock();
	for (int i = 0; i != nTestTime; ++i)
		coinsWay2(arr, n, aim);
	cout << clock() - start << endl;

	start = clock();
	for (int i = 0; i != nTestTime; ++i)
		coinsWay2_1(arr, n, aim);
	cout << clock() - start << endl;

	start = clock();
	for (int i = 0; i != nTestTime; ++i)
		coinsWay3(arr, n, aim);
	cout << clock() - start << endl;

	start = clock();
	for (int i = 0; i != nTestTime; ++i)
		coinsWay4(arr, n, aim);
	cout << clock() - start << endl;

	system("pause");
	return 0;
}


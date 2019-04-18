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

#pragma region �����ݹ�汾
int process1(int *arr, int i, int j, int aim);
int coinsWay1(int *arr, int n, int aim)
{
	if (aim == 0) return 1;

	int res = process1(arr, 0, n - 1, aim);
	return  res < 0 ? 0 : res;

}

//��������:��i-n-1λ���ϵ�������ѡ��Ҫ�������ķ�����
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


#pragma region �Զ����±���¼�汾

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

//��������:��i-n-1λ���ϵ�������ѡ��Ҫ�������ķ�����
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

#pragma region �ù�ϣ��������¼�Ļ��ݷ�
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



//��������:��i-n-1λ���ϵ�������ѡ��Ҫ�������ķ�����
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


#pragma region ��̬�滮�汾,�ռ�O(aim*n)
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

	for (int i = 0; i != n; ++i) //��һ��ȫ��1
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
			int k = j / arr[i]; //���������д����aim/arr[i],�ӵݹ�ת��������ʱ��һ��Ҫע�⣬��Щ���ڱ�ģ���Щ��û���
			int res = 0;
			for (int l = 0; l <= k; ++l)
			{
				int tmp = dp[i + 1][j - l*arr[i]]; //������j-xxx����aim-��!!!
				res += tmp == 0 ? 0 : tmp;
			}
			dp[i][j] = res;
		}
	}


	return dp[0][aim];

}
#pragma endregion

//�Ż��ռ临�Ӷ�
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
			int k = j / arr[i]; //���������д����aim/arr[i],�ӵݹ�ת��������ʱ��һ��Ҫע�⣬��Щ���ڱ�ģ���Щ��û���
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

#pragma region ���ܲ���,VS����ˣ������ǶԵݹ������Ż������Լ�д�Ļ���

#pragma endregion


	//debug�£������Ƕ�̬�滮����棬����ǿռ��Ż�������ǵݹ飬����Ǵ�����¼�ĵݹ�
	//release�£������ǵݹ�!!!,����Ƕ�̬�滮����棬Ȼ���Ǵ�����¼�ĵݹ飬����ǿռ��Ż��Ķ�̬�滮

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


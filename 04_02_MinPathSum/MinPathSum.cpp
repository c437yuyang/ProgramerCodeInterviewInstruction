#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

#pragma region 递归版本，两种意义的求解
//函数意义:在i,j位置，走完这个矩阵的最小路径
int minPathSum(int *mat, int i, int j, int m, int n)
{
	int res = mat[i*n + j];
	if (i == m - 1 && j == n - 1)
		return res;

	if (i == m - 1) //到了最后一行了,只能向右走
		return res + minPathSum(mat, i, j + 1, m, n);

	if (j == n - 1) //到了最后一列了,只能向下走
		return res + minPathSum(mat, i + 1, j, m, n);

	return res + std::min(minPathSum(mat, i, j + 1, m, n), minPathSum(mat, i + 1, j, m, n));
}


//回溯版本
int minPathSum_Back(int *mat, int i, int j, int m, int n, vector<vector<int>>&dp)
{
	int res = mat[i*n + j];
	if (i == m - 1 && j == n - 1)
		return res;

	int res1 = -1, res2 = -1;
	if (i == m - 1) //到了最后一行了,只能向右走
	{
		if (dp[i][j + 1] != -1)
		{
			res1 = dp[i][j + 1];
			return  res + res1;
		}
		return res + minPathSum_Back(mat, i, j + 1, m, n, dp);
	}

	if (j == n - 1) //到了最后一列了,只能向下走
	{
		if (dp[i + 1][j] != -1)
		{
			res2 = dp[i + 1][j];
			return  res + res2;
		}
		return res + minPathSum_Back(mat, i + 1, j, m, n, dp);
	}

	if (res1 == -1)
		res1 = minPathSum_Back(mat, i, j + 1, m, n, dp);
	if (res2 == -1)
		res2 = minPathSum_Back(mat, i + 1, j, m, n, dp);

	dp[i][j] = res + std::min(res1, res2);
	return dp[i][j];
}

//函数意义:走到i,j位置的最小路径和
int minPathSum_1(int *mat, int i, int j, int m, int n)
{
	int res = mat[i*n + j];
	if (i == 0 && j == 0)
		return res;

	if (i == 0)
		return res + minPathSum_1(mat, i, j - 1, m, n);

	if (j == 0)
		return res + minPathSum_1(mat, i - 1, j, m, n);

	return res + std::min(minPathSum_1(mat, i - 1, j, m, n), minPathSum_1(mat, i, j - 1, m, n));

}

#pragma endregion

#pragma region 动态规划版本
int minPathSum1(int *mat, int i, int j, int m, int n)
{
	vector<vector<int>> dp(m);
	for_each(dp.begin(), dp.end(), [n](vector<int>&tmp) { tmp.resize(n); });

	dp[m - 1][n - 1] = mat[m*n - 1];

	for (int i = m - 2; i >= 0; --i)
		dp[i][n - 1] = dp[i + 1][n - 1] + mat[i*n + n - 1];

	for (int j = n - 2; j >= 0; --j)
		dp[m - 1][j] = dp[m - 1][j + 1] + mat[(m - 1)*n + j];

	for (int i = m - 2; i >= 0; --i)
		for (int j = n - 2; j >= 0; --j)
			dp[i][j] = mat[i*n + j] + std::min(dp[i][j + 1], dp[i + 1][j]);
	return dp[0][0];
}

//降低空间复杂度为O(1),貌似不行，至少是O(N+M)?,用两个条
//用两个条的版本
int minPathSum2(int *mat, int i, int j, int m, int n)
{
	vector<vector<int>> dp(m);
	for_each(dp.begin(), dp.end(), [](vector<int>&tmp) { tmp.resize(2); }); //两列

	dp[m - 1][1] = mat[m*n - 1]; //右下角
	//dp[m-1][0] = dp[]

	for (int i = m - 2; i >= 0; --i) //先计算最后一列
		dp[i][1] = dp[i + 1][1] + mat[i*n + n - 1];

	//后面每一列依次算
	for (int j = n - 2; j >= 0; --j)
	{
		dp[m - 1][0] = dp[m - 1][1] + mat[(m - 1)*n + j]; //最后一个位置
		for (int i = m - 2; i >= 0; --i)
		{
			dp[i][0] = mat[i*n + j] + std::min(dp[i + 1][0], dp[i][1]);
		}
		//计算完成后把两列位置交换
		for (int i = 0; i < m; ++i)
		{
			dp[i][1] = dp[i][0];
		}
	}
	return dp[0][1];

}

#pragma endregion


int main()
{

	int mat[] = { 1, 3, 5, 9 ,
				8, 1, 3, 4 ,
				5, 0, 6, 1 ,
				8, 8, 4, 0 };

	vector<vector<int>> dp(4);
	for_each(dp.begin(), dp.end(), [](vector<int> &v) { v.resize(4, -1); });

	printMatrix(mat, 4, 4);
	cout << minPathSum(mat, 0, 0, 4, 4) << endl;
	cout << minPathSum1(mat, 0, 0, 4, 4) << endl;
	cout << minPathSum2(mat, 0, 0, 4, 4) << endl;
	cout << minPathSum_Back(mat, 0, 0, 4, 4, dp) << endl;
	cout << minPathSum_1(mat, 3, 3, 4, 4) << endl; //函数意义不同的动态规划


	int mat1[] = { 8, 6, 7, 9,
					0 ,4 ,3 ,9,
					4 ,9 ,3 ,3 };
	printMatrix(mat1, 3, 4);
	cout << minPathSum(mat1, 0, 0, 3, 4) << endl;
	cout << minPathSum1(mat1, 0, 0, 3, 4) << endl;
	cout << minPathSum2(mat1, 0, 0, 3, 4) << endl;
	cout << minPathSum_1(mat1, 2, 3, 3, 4) << endl;
	dp.clear();
	dp.resize(3, vector<int>(4, -1));

	cout << minPathSum_Back(mat1, 0, 0, 3, 4, dp) << endl;



	system("pause");
	return 0;
}


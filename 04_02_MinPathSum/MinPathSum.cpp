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

#pragma region �ݹ�汾��������������
//��������:��i,jλ�ã���������������С·��
int minPathSum(int *mat, int i, int j, int m, int n)
{
	int res = mat[i*n + j];
	if (i == m - 1 && j == n - 1)
		return res;

	if (i == m - 1) //�������һ����,ֻ��������
		return res + minPathSum(mat, i, j + 1, m, n);

	if (j == n - 1) //�������һ����,ֻ��������
		return res + minPathSum(mat, i + 1, j, m, n);

	return res + std::min(minPathSum(mat, i, j + 1, m, n), minPathSum(mat, i + 1, j, m, n));
}


//���ݰ汾
int minPathSum_Back(int *mat, int i, int j, int m, int n, vector<vector<int>>&dp)
{
	int res = mat[i*n + j];
	if (i == m - 1 && j == n - 1)
		return res;

	int res1 = -1, res2 = -1;
	if (i == m - 1) //�������һ����,ֻ��������
	{
		if (dp[i][j + 1] != -1)
		{
			res1 = dp[i][j + 1];
			return  res + res1;
		}
		return res + minPathSum_Back(mat, i, j + 1, m, n, dp);
	}

	if (j == n - 1) //�������һ����,ֻ��������
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

//��������:�ߵ�i,jλ�õ���С·����
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

#pragma region ��̬�滮�汾
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

//���Ϳռ临�Ӷ�ΪO(1),ò�Ʋ��У�������O(N+M)?,��������
//���������İ汾
int minPathSum2(int *mat, int i, int j, int m, int n)
{
	vector<vector<int>> dp(m);
	for_each(dp.begin(), dp.end(), [](vector<int>&tmp) { tmp.resize(2); }); //����

	dp[m - 1][1] = mat[m*n - 1]; //���½�
	//dp[m-1][0] = dp[]

	for (int i = m - 2; i >= 0; --i) //�ȼ������һ��
		dp[i][1] = dp[i + 1][1] + mat[i*n + n - 1];

	//����ÿһ��������
	for (int j = n - 2; j >= 0; --j)
	{
		dp[m - 1][0] = dp[m - 1][1] + mat[(m - 1)*n + j]; //���һ��λ��
		for (int i = m - 2; i >= 0; --i)
		{
			dp[i][0] = mat[i*n + j] + std::min(dp[i + 1][0], dp[i][1]);
		}
		//������ɺ������λ�ý���
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
	cout << minPathSum_1(mat, 3, 3, 4, 4) << endl; //�������岻ͬ�Ķ�̬�滮


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


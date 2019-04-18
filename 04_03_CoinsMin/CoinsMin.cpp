#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
const int maxInt = 65536;
//�������壬��arr[i->j]���Ҵճ�aim����С������
//���ϰ汾������:ʹ��[0->i]�Ļ��Ҵճ�aim����С��������Ҳ����solve2��Ӧ��
int CoinsMin1(int *arr, int i, int j, int aim);
int solve1(int *arr, int n, int aim)
{
	int res = CoinsMin1(arr, 0, n - 1, aim);
	return  res >= maxInt ? -1 : res;
}

int CoinsMin1(int *arr, int i, int j, int aim)
{
	if (aim == 0) return 0;
	if (i == j) //��ʵ�����ұ߽�,n-1
	{
		if (aim%arr[i] != 0)
		{
			return maxInt;

		}
		else return aim / arr[i];
	}

	int k = aim / arr[i];
	int res = maxInt;
	for (int c = 0; c <= k; ++c)
	{
		res = std::min(res, c + CoinsMin1(arr, i + 1, j, aim - c*arr[i]));
	}

	return /*res >= 65536 ? -1 :*/ res; //��ò�Ҫ����-1����һ��solve����ȥ���ã�����-1Ҳ������������Ϊ���ﷵ�ص�����Ŀ��-1�͸�������


}


//��������:ʹ��[0->i]�Ļ��Ҵճ�aim������Ҫ����С��������ʱ��O(aim*n),�ռ���ͬ
int solve2(int *arr, int n, int aim)
{
	vector<vector<int>> dp(n);
	for_each(dp.begin(), dp.end(), [aim](vector<int>&tmp) {tmp.assign(aim + 1, 0); }); //��һ���Զ�Ϊ0��

	for (int j = 1; j <= aim; ++j) //ֻ��ʹ��arr[0]�������
	{
		if (j%arr[0] != 0) dp[0][j] = maxInt;
		else  dp[0][j] = j / arr[0];
		//������һ��������Ƶİ汾��û��ô����
		//dp[0][j] = maxInt;
		//if (j - arr[0] >= 0 && dp[0][j - arr[0]] != maxInt) {
		//	dp[0][j] = dp[0][j - arr[0]] + 1;
		//}

	}

	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j <= aim; ++j)
		{
			if (j - arr[i] < 0)
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = std::min(dp[i - 1][j], dp[i][j - arr[i]] + 1);
		}
	}
	return dp[n - 1][aim];
}

//�Ż�Ϊ���и���ʱ��O(aim*n),�ռ�O(aim)
int solve3(int *arr, int n, int aim)
{

	vector<int> dp(aim + 1);
	dp[0] = 0;//��һ���ȸ�ֵ
	for (int j = 1; j <= aim; ++j) //ֻ��ʹ��arr[0]�������
	{
		if (j%arr[0] != 0) dp[j] = maxInt;
		else  dp[j] = j / arr[0];
	}

	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j <= aim; ++j)
		{
			if (j - arr[i] < 0) //��ʱ����һ�е�ֵ��������Ҳ����
				continue;
			//dp[j] = dp[j]; 
			else
				dp[j] = std::min(dp[j], dp[j - arr[i]] + 1);
		}
	}
	return dp[aim];
}


//������
int CoinsMin_1(int *arr, int i, int j, int aim);
int solve_1(int *arr, int n, int aim)
{
	int res = CoinsMin_1(arr, 0, n - 1, aim);
	return  res >= maxInt ? -1 : res;
}

int CoinsMin_1(int *arr, int i, int j, int aim)
{
	if (aim == 0)
		return 0;
	if (accumulate(arr + i, arr + j + 1, 0) < aim)
		return maxInt;
	if (arr[i] == aim)
		return 1;
	if (arr[i] > aim)
		return CoinsMin_1(arr, i + 1, j, aim);

	//������ǰ������������
	//if (i == j)
	//{
	//	if (aim == arr[i])
	//		return 1;
	//	else //С�ڻ���ڶ������Ҳ���
	//		return 65536;
	//}


	int res = std::min(
		CoinsMin_1(arr, i + 1, j, aim),
		1 + CoinsMin_1(arr, i + 1, j, aim - arr[i]));

	return /*res >= 65536 ? -1 :*/ res; //���ﲻ��ȥ����-1�������


}

int main()
{


	int arr[] = { 5,2,3 };

	cout << solve1(arr, 3, 20) << endl;
	cout << solve1(arr, 3, 0) << endl;
	cout << solve1(arr, 3, 1) << endl;

	int arr1[] = { 100, 20, 5, 10, 2, 50, 1 };
	//int aim1 = 501;
	int aim1 = 17901;
	//cout << solve1(arr1, 7, aim1) << endl; //���ִ��ˣ�solve1�����ܲ�����
	cout << solve2(arr1, 7, aim1) << endl;
	cout << solve3(arr1, 7, aim1) << endl;

	//int arr2[] = { 10, 100, 2, 5, 5, 5, 10, 1, 1, 1, 2, 100 };
	//int aim2 = 223;
	//cout << solve_1(arr2, 12, aim2) << endl;

	int arr2[] = { 5,2,5,3,10 };
	int aim2 = 11;
	cout << solve_1(arr2, 5, aim2) << endl;

	//int arr2[] = { 5,2,5 };
	//int aim2 = 7;
	//cout << CoinsMin_1(arr2, 0, 2, aim2) << endl;



	system("pause");
	return 0;
}


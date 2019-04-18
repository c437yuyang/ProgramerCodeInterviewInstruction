#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <set>
using namespace std;


#pragma region 我的版本，简单实现，没看左程云的版本,错的，题意都理解错了
int longestSequence(int *arr, int n)
{
	set<int> dict(arr, arr + n);

	int max = INT_MIN;
	int len = 1;
	int pre = *(dict.begin());
	auto it = dict.begin();
	++it;
	for (; it != dict.end(); ++it)
	{
		if (*it - pre == 1)
		{
			len++;
			max = std::max(max, len);
		}
		else
		{
			len = 1;
			max = std::max(max, len);
		}
		pre = *it;
	}


	return max;
}

#pragma endregion


int main()
{
	//int arr[] = { 3,2,3,1,1,4 };
	//int arr[] = { 3,1,1,1 };
	int arr[] = { 100,4,1,3,2,200,5,6,7,1000 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << longestSequence(arr, n) << endl;



	system("pause");
	return 0;
}


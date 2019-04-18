#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;


//����1:������ֱ��ͼ������
bool IsAllUnique(char arr[], int n)
{
	unordered_map<char, int> map;
	for (int i = 0; i != n; ++i)
	{
		if (map.find(arr[i]) == map.end()) {
			map[arr[i]] = 1;
		}
		else return false;
	}
	return true;
}

//�ռ临�Ӷ�ΪO(1),ʱ�临�ӶȾ����͵�����
//������Ȼ�����һ�飬���ÿ���ַ��Ƿ��ǰһ���ַ�һ����һ����false��
//���ö�������������ռ�O(1)��ʱ��O(N)


//�汾1:ʹ��stl�ĶѲ���
bool IsAllUnique1(char arr[], int n)
{
	make_heap(arr, arr + n);

	sort_heap(arr, arr + n);

	for (int i = 1; i != n; ++i)
	{
		if (arr[i] == arr[i - 1]) {
			return false;
		}
	}
	return true;
}

//�汾2��ʹ���Լ�д��heap����

//heapify
void heapify(char arr[], int n, int i)
{
	int left = i * 2 + 1;
	int right = i * 2 + 2;
	int largest = i;
	while (left < n)
	{
		if (arr[left] > arr[i])
			largest = left;
		if (right < n && arr[right] > arr[largest])
			largest = right;
		if (largest != i) 
		{
			std::swap(arr[i], arr[largest]);
			i = largest;
			left = i * 2 + 1;
			right = i * 2 + 2;
		}
		else
		{
			break;
		}
	}

}


bool IsAllUnique2(char arr[], int n)
{
	//ִ��heapinsert,Ҳ����buildheap
	for (int i = 0; i != n; ++i)
	{
		while (i != 0)
		{
			int parent = (i - 1) / 2;
			if (arr[parent] < arr[i])
				std::swap(arr[parent], arr[i]);
			else
				break;
			i = parent;
		}
	}

	//ִ��heap_sort
	for (int i = n - 1; i != 0; --i)
	{
		std::swap(arr[i], arr[0]);
		--n;
		heapify(arr, n, 0);
	}

	for (int i = 1; i != n; ++i)
	{
		if (arr[i] == arr[i - 1]) {
			return false;
		}
	}
	return true;
}



int main()
{

	char chas[] = { '1', '2', '3', 'a', 'b', 'c', 'd', '4', '5', '6' };

	cout << IsAllUnique(chas, sizeof(chas) / sizeof(chas[0])) << endl;
	cout << IsAllUnique1(chas, sizeof(chas) / sizeof(chas[0])) << endl;
	cout << IsAllUnique2(chas, sizeof(chas) / sizeof(chas[0])) << endl;

	system("pause");
	return 0;
}
#include <iostream>
#include <memory>
#include <stack>
#include <list>
#include <assert.h>
using namespace std;
using std::shared_ptr;

template<class T>
struct BinaryTreeNode
{
	typedef  shared_ptr<BinaryTreeNode<T>> pBTN;
	T elem;
	pBTN left;
	pBTN right;

	BinaryTreeNode(const T&elem, const pBTN& left, const pBTN& right) :
		elem(elem), left(left), right(right) {}

	BinaryTreeNode(const T&elem) :
		elem(elem), left(NULL), right(NULL) {}

};

typedef  shared_ptr<BinaryTreeNode<int>> ipBTN;
typedef  BinaryTreeNode<int> iBTN;


//记录当前值以及左右第一个比它大的值
struct Item
{
	int elem;

	int left;
	int right;
	Item(int e, int l, int r) :elem(e), right(r), left(l) {}
};

#pragma region 自己的版本
void build_tree(list<Item> &list, ipBTN head);
//说了不考虑重复值
ipBTN getMaxTree(int *arr, int n)
{

	stack<int> s;
	list<Item> list;
	for (int i = 0; i != n; ++i)
	{
		if (s.empty() || arr[s.top()] >= arr[i])
			s.push(i);
		else
		{
			while (!s.empty() && arr[s.top()] < arr[i])
			{
				int tmp = s.top();
				s.pop();
				if (s.empty()) //只剩这一个数
					list.push_back(Item(arr[tmp], -1, arr[i]));
				else //还有其他数
					list.push_back(Item(arr[tmp], arr[s.top()], arr[i]));
			}
			s.push(i);
		}
	}


	while (!s.empty())
	{
		if (s.size() == 1)
		{
			list.push_back(Item(arr[s.top()], -1, -1));
			s.pop();
		}

		else
		{
			int tmp = s.top();
			s.pop();
			list.push_back(Item(arr[tmp], arr[s.top()], -1));
		}
	}

	//遍历之前的list，形成maxTree
	assert(list.back().right == -1 && list.back().left == -1);
	ipBTN head = make_shared<iBTN>(list.back().elem);
	auto itEnd = list.end();
	list.erase(--itEnd); //删除掉最后一个元素


	build_tree(list, head);

	return head;

}

void build_tree(list<Item> &list, ipBTN head)
{
	for (auto it = list.begin(); it != list.end();) //这里list.end()是变化的，所以不能取固定值
	{
		if (it->left == head->elem && (it->left < it->right || it->right == -1)) {
			head->left = make_shared<iBTN>(it->elem);
			it = list.erase(it);
			build_tree(list, head->left);
		}

		else if (it->right == head->elem && (it->right < it->left || it->left == -1)) {
			head->right = make_shared<iBTN>(it->elem);
			it = list.erase(it);
			build_tree(list, head->right);
		}
		else
		{
			++it;
		}
	}
}

#pragma endregion


#pragma region 参考左程云，优化单调栈写法
void build_tree1(list<Item> &list, ipBTN head);
//说了不考虑重复值
ipBTN getMaxTree1(int *arr, int n)
{
	stack<int> s;
	list<Item> list;
	for (int i = 0; i != n; ++i)
	{
		while (!s.empty() && arr[s.top()] < arr[i])
		{
			int tmp = s.top();
			s.pop();
			int left = s.empty() ? -1 : arr[s.top()];
			list.push_back(Item(arr[tmp], left, arr[i]));
		}
		s.push(i);
	}
	while (!s.empty())
	{
		int tmp = s.top();
		s.pop();
		int left = s.empty() ? -1 : arr[s.top()];
		list.push_back(Item(arr[tmp],left, -1));
	}

	//遍历之前的list，形成maxTree
	assert(list.back().right == -1 && list.back().left == -1);
	ipBTN head = make_shared<iBTN>(list.back().elem);
	auto itEnd = list.end();
	list.erase(--itEnd); //删除掉最后一个元素

	build_tree1(list, head);

	return head;

}

void build_tree1(list<Item> &list, ipBTN head)
{
	for (auto it = list.begin(); it != list.end();) //这里list.end()是变化的，所以不能取固定值
	{
		if (it->left == head->elem && (it->left < it->right || it->right == -1)) {
			head->left = make_shared<iBTN>(it->elem);
			it = list.erase(it);
			build_tree(list, head->left);
		}

		else if (it->right == head->elem && (it->right < it->left || it->left == -1)) {
			head->right = make_shared<iBTN>(it->elem);
			it = list.erase(it);
			build_tree(list, head->right);
		}
		else
		{
			++it;
		}
	}
}

#pragma endregion


int main()
{
	int arr[] = { 3,4,5,1,2 };
	const int n = 5;

	ipBTN head = getMaxTree(arr, n);
	ipBTN head1 = getMaxTree1(arr, n);

	system("pause");
	return 0;
}
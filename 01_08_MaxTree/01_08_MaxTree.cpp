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


//��¼��ǰֵ�Լ����ҵ�һ���������ֵ
struct Item
{
	int elem;

	int left;
	int right;
	Item(int e, int l, int r) :elem(e), right(r), left(l) {}
};

#pragma region �Լ��İ汾
void build_tree(list<Item> &list, ipBTN head);
//˵�˲������ظ�ֵ
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
				if (s.empty()) //ֻʣ��һ����
					list.push_back(Item(arr[tmp], -1, arr[i]));
				else //����������
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

	//����֮ǰ��list���γ�maxTree
	assert(list.back().right == -1 && list.back().left == -1);
	ipBTN head = make_shared<iBTN>(list.back().elem);
	auto itEnd = list.end();
	list.erase(--itEnd); //ɾ�������һ��Ԫ��


	build_tree(list, head);

	return head;

}

void build_tree(list<Item> &list, ipBTN head)
{
	for (auto it = list.begin(); it != list.end();) //����list.end()�Ǳ仯�ģ����Բ���ȡ�̶�ֵ
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


#pragma region �ο�����ƣ��Ż�����ջд��
void build_tree1(list<Item> &list, ipBTN head);
//˵�˲������ظ�ֵ
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

	//����֮ǰ��list���γ�maxTree
	assert(list.back().right == -1 && list.back().left == -1);
	ipBTN head = make_shared<iBTN>(list.back().elem);
	auto itEnd = list.end();
	list.erase(--itEnd); //ɾ�������һ��Ԫ��

	build_tree1(list, head);

	return head;

}

void build_tree1(list<Item> &list, ipBTN head)
{
	for (auto it = list.begin(); it != list.end();) //����list.end()�Ǳ仯�ģ����Բ���ȡ�̶�ֵ
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
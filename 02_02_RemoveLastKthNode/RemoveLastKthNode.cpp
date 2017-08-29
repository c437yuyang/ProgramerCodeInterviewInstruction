#include <iostream>
using namespace std;


class ChainNode
{
public:

	ChainNode(int val) :elem(val), next(NULL) {}
	int elem;
	ChainNode* next;
};

void printLinkedList(ChainNode *head)
{
	while (head != NULL)
	{
		cout << head->elem << " ";
		head = head->next;
	}
	cout << endl;
}


class DoubleChainNode
{
public:

	DoubleChainNode(int val) :elem(val), next(NULL), last(NULL) {}
	int elem;
	DoubleChainNode* next;
	DoubleChainNode* last;
};
void printLinkedList(DoubleChainNode *head)
{
	while (head != NULL)
	{
		cout << head->elem << " ";
		head = head->next;
	}
	cout << endl;
}

void printLinkedListReverse(DoubleChainNode *head)
{
	while (head->next != NULL) //�ҵ�����head->next ==null�ģ��������һ��
	{
		//cout << head->elem << " ";
		head = head->next;
	}
	while (head != NULL) 
	{
		cout << head->elem << " ";
		head = head->last;
	}

	cout << endl;
}

#pragma region �Լ��ķ���
void printQueue(ChainNode**w, int k)
{
	cout << "����: ";
	for (int i = 0; i != k; ++i)
	{
		if (w[i] != NULL) cout << w[i]->elem << " ";
		else cout << "NULL ";
	}
	cout << endl;
}

void processQueue(ChainNode**w, int k, ChainNode *p) //��k��ָ�������
{
	int i = 0;
	for (int i = 0; i != k - 1; ++i)
	{
		w[i] = w[i + 1];
	}
	w[k - 1] = p;
}

//ɾ�������ص�����k���ڵ�
ChainNode * removeLastKthNode(ChainNode *&head, int k)
{
	ChainNode**w = new ChainNode*[k + 1];
	for (int i = 0; i != k + 1; ++i)
		w[i] = NULL;

	ChainNode *c = head;

	while (c != NULL)
	{
		processQueue(w, k + 1, c);
		printQueue(w, k + 1);
		c = c->next;
	}

	if (k == 1) {
		w[0]->next = w[1]->next;
		return w[1];

	}
	//����w������ĵڶ��������ǵ�����k���ڵ㣬��һ�����ǵ�����k���ڵ����һ���ڵ�
	if (w[0] == NULL && w[1] != NULL) //head���ǵ�����k���ڵ�
	{
		head = w[1]->next;//��head���¸�ֵ
		return w[1];//���ص�һ���ڵ�
	}
	else if (w[0] == NULL &&w[1] == NULL)  //û�ҵ�������k���ڵ㣬��������
	{
		return NULL;
	}
	else if (w[0] != NULL &&w[1] != NULL)
	{
		w[0]->next = w[1]->next;
		return w[1];
	}
	else
	{
		cout << "error " << endl;
		return NULL;
	}

}
#pragma endregion

#pragma region ����Ƶİ汾

ChainNode* removeLastKthNode1(ChainNode *&head, int lastKth)
{
	int k = lastKth;
	ChainNode *cur = head;
	while (cur != NULL)
	{
		cur = cur->next;
		--k;
	}
	if (k > 0) return NULL;//�����ڵ�����k��
	if (k == 0) 
	{
		ChainNode *tmp = head;
		head = head->next;
		return tmp;
	} 
	if (k < 0)
	{
		cur = head;
		while (++k < 0) //һֱ�ҵ�k=0�Ľڵ�
			cur = cur->next;
		ChainNode *tmp = cur->next;
		cur->next = cur->next->next;//k=0�Ľ�����Ҫɾ���Ľ�����һ�����
		return tmp;
	}

}
#pragma endregion


#pragma region ˫����
DoubleChainNode* removeLastKthNode1(DoubleChainNode *&head, int lastKth)
{
	int k = lastKth;
	DoubleChainNode *cur = head;
	while (cur != NULL)
	{
		cur = cur->next;
		--k;
	}
	if (k > 0) return NULL;//�����ڵ�����k��
	if (k == 0)
	{
		DoubleChainNode *tmp = head;
		head = head->next;
		head->last = NULL;
		return tmp;
	}
	if (k < 0)
	{
		cur = head;
		while (++k < 0) //һֱ�ҵ�k=0�Ľڵ�
			cur = cur->next;
		DoubleChainNode *tmp = cur->next;
		cur->next = cur->next->next;//k=0�Ľ�����Ҫɾ���Ľ�����һ�����
		if(cur->next!=NULL)
			cur->next->last = cur;
		return tmp;
	}
}

#pragma endregion

int main()
{
	ChainNode *c2 = new ChainNode(1);
	c2->next = new ChainNode(2);
	c2->next->next = new ChainNode(5);
	c2->next->next->next = new ChainNode(7);
	c2->next->next->next->next = new ChainNode(8);

	printLinkedList(c2);
	//ChainNode *lastKNode = removeLastKthNode(c2, 1);
	//ChainNode *lastKNode = removeLastKthNode(c2, 2);
	//ChainNode *lastKNode = removeLastKthNode(c2, 3);

	//ChainNode *lastKNode = removeLastKthNode1(c2, 1);
	ChainNode *lastKNode = removeLastKthNode1(c2, 2);

	printLinkedList(c2);


	//˫��������
	DoubleChainNode *head2 = new DoubleChainNode(1);
	head2->next = new DoubleChainNode(2);
	head2->next->last = head2;
	head2->next->next = new DoubleChainNode(3);
	head2->next->next->last = head2->next;
	head2->next->next->next = new DoubleChainNode(4);
	head2->next->next->next->last = head2->next->next;
	head2->next->next->next->next = new DoubleChainNode(5);
	head2->next->next->next->next->last = head2->next->next->next;

	printLinkedList(head2);
	printLinkedListReverse(head2);

	//removeLastKthNode1(head2, 1);
	removeLastKthNode1(head2, 2);
	printLinkedList(head2);
	printLinkedListReverse(head2);


	system("pause");
	return 0;
}


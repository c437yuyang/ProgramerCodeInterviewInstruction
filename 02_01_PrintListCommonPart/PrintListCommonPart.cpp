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

void printListCommonPart(ChainNode *c1, ChainNode *c2)
{
	ChainNode *head1, *head2;

	head1 = c1, head2 = c2;

	while (head1 != NULL && head2 != NULL)
	{
		if (head1->elem == head2->elem)
		{
			cout << head1->elem << " ";
			head1 = head1->next;
			head2 = head2->next;
		}
			
		else if (head1->elem < head2->elem) head1 = head1->next;
		else
			head2 = head2->next;
	}
}




int main()
{

	ChainNode *c1 = new ChainNode(2);
	c1->next = new ChainNode(3);
	c1->next->next = new ChainNode(5);
	c1->next->next->next = new ChainNode(6);
	c1->next->next->next->next = new ChainNode(8);

	ChainNode *c2 = new ChainNode(1);
	c2->next = new ChainNode(2);
	c2->next->next = new ChainNode(5);
	c2->next->next->next = new ChainNode(7);
	c2->next->next->next->next = new ChainNode(8);

	printLinkedList(c1);
	printLinkedList(c2);
	printListCommonPart(c1, c2);

	system("pause");
	return 0;
}


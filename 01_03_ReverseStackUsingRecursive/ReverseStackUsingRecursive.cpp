#include <iostream>
#include <stack>
using namespace std;

int getAndRemoveLastElement(stack<int>& s)
{
	int res = s.top();
	s.pop();
	if (s.empty())
		return res;
	int last = getAndRemoveLastElement(s); //�ܹ�ȡ�÷���ֵ�����ֻ�е�ջ���һ��Ԫ�ص�ʱ��
	s.push(res);
	return last; //һֱ�����ֵ���ػ�ȥ
}

void reverseStack(stack<int> &s)
{
	if (s.empty())
		return;

	int last = getAndRemoveLastElement(s);
	reverseStack(s);
	s.push(last);
}

int main()
{

	stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	reverseStack(s);

	cout << s.top() << endl; s.pop();
	cout << s.top() << endl;

	system("pause");
	return 0;
}
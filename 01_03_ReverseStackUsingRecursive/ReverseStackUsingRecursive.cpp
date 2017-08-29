#include <iostream>
#include <stack>
using namespace std;

int getAndRemoveLastElement(stack<int>& s)
{
	int res = s.top();
	s.pop();
	if (s.empty())
		return res;
	int last = getAndRemoveLastElement(s); //能够取得返回值的情况只有当栈最后一个元素的时候
	s.push(res);
	return last; //一直把这个值返回回去
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
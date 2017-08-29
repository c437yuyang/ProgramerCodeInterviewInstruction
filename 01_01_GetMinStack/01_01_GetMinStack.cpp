#include <iostream>
#include <stack>
using namespace std;


class MinStack {

public:
	void push(int val);
	int top();
	void pop();
	int minval() { return stackMin.top(); }

private:
	stack<int> stackData;
	stack<int> stackMin;
};

void MinStack::push(int val)
{
	if (stackMin.empty())
		stackMin.push(val);
	else if (val <= stackMin.top()) 
	{
		stackMin.push(val);
	}
	stackData.push(val);
}

int MinStack::top()
{
	return stackData.top();
}

void MinStack::pop()
{
	if (stackData.top() == stackMin.top())
		stackMin.pop();
	stackData.pop();
}



int main()
{



	system("pause");
	return 0;
}
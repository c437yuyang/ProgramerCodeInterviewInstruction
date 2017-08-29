#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //ʹ���ɵ��ڴ�dump�����ڴ�����ľ������Ϊֹ
#include <stdlib.h> 
#include <crtdbg.h>
#define CheckMemoryLeak _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG )| _CRTDBG_LEAK_CHECK_DF)
#endif 

#include <iostream>
#include <stack>
using namespace std;

#pragma region ���Լ��İ汾
void StackSortStack(stack<int>& s)
{
	stack<int> help;
	while (!s.empty())
	{
		int tmp = s.top();
		s.pop();
		if (help.empty()) {
			help.push(tmp);
		}
		else
		{
			if (help.top() >= tmp) help.push(tmp);
			else
			{
				int cnt = 0;
				while (!help.empty())
				{
					s.push(help.top());
					help.pop();
					++cnt;
				}
				help.push(tmp);
				while (cnt > 0)
				{
					help.push(s.top());
					s.pop();
					--cnt;
				}
			}
		}
	}

	while (!help.empty())
	{
		s.push(help.top());
		help.pop();
	}

}
#pragma endregion


#pragma region ����Ƶİ汾
void StackSortStack1(stack<int>& s)
{
	stack<int> help;
	while (!s.empty())
	{
		int tmp = s.top();
		s.pop();
		
		while (!help.empty() && tmp > help.top())
		{
			s.push(help.top()); //����push��������ʵ��������ԭ��֮����s����Ҫ����pop
			help.pop();
		}
		help.push(tmp);
	}

	while (!help.empty())
	{
		s.push(help.top());
		help.pop();
	}

}
#pragma endregion

void printStack(stack<int> s)
{
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}


int main()
{
#ifdef _DEBUG
	CheckMemoryLeak;
#endif

	stack<int> s;
	s.push(5);
	s.push(4);
	s.push(3);
	s.push(2);
	s.push(1);

	printStack(s);
	StackSortStack1(s);
	printStack(s);
	system("pause");
	return 0;
}


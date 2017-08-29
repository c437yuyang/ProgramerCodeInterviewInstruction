#ifdef _DEBUG
//for memory leak check
#define _CRTDBG_MAP_ALLOC //使生成的内存dump包含内存块分配的具体代码为止
#include <stdlib.h> 
#include <crtdbg.h>
#define CheckMemoryLeak _CrtSetDbgFlag( _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG )| _CRTDBG_LEAK_CHECK_DF)
#endif 

#include <iostream>
#include <deque>
#include <string>
#include <queue>
using namespace std;

class Pet {
public:
	virtual ~Pet() = 0 {}; //防止产生该类对象
	string getType() const
	{
		return this->type;
	}
protected:
	string type;
	static int id;
};

class Dog :public Pet {
public:
	Dog() 
	{ 
		char buf[256];
		_itoa_s(id++, buf, 10);
		type = string("Dog") + buf;
	}
};

class Cat :public Pet {
public:
	Cat() 
	{
		char buf[256];
		_itoa_s(id++, buf, 10);
		type = string("Cat") + buf;
	}
};

class DogCatQueueItem {
public:
	DogCatQueueItem(Pet *p, int count) :p(p), count(count) {}
	string getType() { return p->getType(); }
	int getCount() { return count; }
	Pet* getPet() { return p; }
private:
	Pet* p;
	int count;
};


class DogCatQueue
{
public:
	int getCount() { return count; }

	void add(Pet *p)
	{
		if (p->getType().substr(0,3).compare("Cat") == 0)
			catQueue.push(new DogCatQueueItem(p, count++));
		if (p->getType().substr(0,3).compare("Dog") == 0)
			dogQueue.push(new DogCatQueueItem(p, count++));
		else return;
	}

	Pet *pollAll()
	{
		Pet *p;
		if (!catQueue.empty() && !dogQueue.empty()) 
		{
			if (catQueue.front()->getCount() < dogQueue.front()->getCount())
			{
				p = catQueue.front()->getPet();
				delete catQueue.front();
				catQueue.pop();
			}

			else if (catQueue.front()->getCount() > dogQueue.front()->getCount())
			{
				p = dogQueue.front()->getPet();
				delete dogQueue.front();
				dogQueue.pop();
			}
			else p = NULL;
		}
		else if (catQueue.empty() && !dogQueue.empty()) 
		{
			p = dogQueue.front()->getPet();
			delete dogQueue.front();
			dogQueue.pop();
		}
		else if (!catQueue.empty() && dogQueue.empty()) 
		{
			p = catQueue.front()->getPet();
			delete catQueue.front();
			catQueue.pop();
		}
		else
		{
			p = NULL;
		}

		return p;
	}

	Cat* pollCat()
	{
		Cat *cat = dynamic_cast<Cat*>(catQueue.front()->getPet());
		delete catQueue.front();
		catQueue.pop();
		return cat;
	}
	Dog* pollDog()
	{

		Dog *dog = dynamic_cast<Dog*>(dogQueue.front()->getPet());
		delete dogQueue.front();
		dogQueue.pop();
		return dog;
	}

	bool isEmpty() { return catQueue.empty() && dogQueue.empty(); }
	bool isCatEmpty() { return catQueue.empty(); }
	bool isDogEmpty() { return dogQueue.empty(); }

private:
	queue<DogCatQueueItem*> catQueue;
	queue<DogCatQueueItem*> dogQueue;
	int count;
};

int Pet::id = 0;
int main()
{
#ifdef _DEBUG
	CheckMemoryLeak;
#endif
	DogCatQueue *test = new DogCatQueue();

	Pet *dog1 = new Dog();
	Pet *cat1 = new Cat();
	Pet *dog2 = new Dog();
	Pet *cat2 = new Cat();
	Pet *dog3 = new Dog();
	Pet *cat3 = new Cat();

	test->add(dog1);
	test->add(cat1);
	test->add(dog2);
	test->add(cat2);
	test->add(dog3);
	test->add(cat3);



	while (!test->isDogEmpty()) {
		cout << test->pollDog()->getType() << endl;
	}
	while (!test->isEmpty()) {
		cout << test->pollCat()->getType() << endl;
	}

	test->add(dog1);
	test->add(cat1);
	test->add(dog2);
	test->add(cat2);
	test->add(dog3);
	test->add(cat3);

	while (!test->isEmpty())
	{
		cout << test->pollAll()->getType() << endl;
	}


	delete cat1;
	delete cat2;
	delete cat3;
	delete dog1;
	delete dog2;
	delete dog3;
	delete test;

	system("pause");
	return 0;
}


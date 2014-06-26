//Laboratory Work 1: Programming C++ 
//Author : Chetrusca Maxim
//Last time modifyed : 9.10.2011
#include <iostream>

using namespace std;

class queue
{
	int n;//number of elements
	int *p;//pointer to memory for the queue;
	int maxN; //Maximal amount of elements allowed in queue


public:

	
//Default constructor :
	queue()
	{
		cout << " implicit constructor ";
		n=0;
		p=NULL;
		maxN=0;
	}

	//Copy constructor :
	queue(const queue &q) //q- constant referince to an object of queue class
	{
		cout << " copy constructor ";
		maxN=q.maxN;
		n=q.n; 
		p=new int[maxN]; 
		for (int i=0; i<n; ++i)
		{
			p[i]=q.p[i];
		}
	}

	//General constructor; n - maximal number of elements allowed in queue
	queue(int n)
	{
		cout << " general constructor ";
		maxN=n;
		this->n=0;
		p=new int[n];
	}

	//Destructor :
~queue()
{
	cout << " destructor ";
	delete[]p;
	p=NULL;
}

//Checks if the queue is full :
	int isFull()
	{
		return n==maxN;
	}
	//Checks if the queue is empty :
	int isEmpty()
	{
		return n==0;
	}


	//Pushes one element into queue:
	int add(int newElement)
	{
		if (isFull()) return 0; //Cannot add anymore;
		else 
		{
			p[n++]=newElement;
		}
		return 1;
	}

	//Pops one element from queue;
	int get()
	{
		if (isEmpty()) return 0;
		else 
		{
			int value=p[0];
			n--;
			for (int i=0; i<n; ++i) p[i]=p[i+1];
			return value;
		}
	}

};


int main ()
{
	queue q1;
	queue q2(10);
	q2.add(111);
	q2.add(222);
	queue q3(q2);

	while (!q3.isEmpty())
	{
		cout << q3.get() << endl; 
	}


	// system("PAUSE");
	return 0;
}

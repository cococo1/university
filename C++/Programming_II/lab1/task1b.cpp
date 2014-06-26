//Laboratory Work 1 : C++
//Author : Chetrusca Maxim
//Last editted : 09.10.2011
#include <iostream>
using namespace std;



class vector
{

private:

	int *p;//pointer to memory for array;
	int n;//number of elements in array; 

public:

	//Default constructor :
	vector()
	{
		p=NULL;
		n=0;
	}

	//Function for initializing of the vector:
	void initVector(int *newVector,int newN)
	{
		n=newN; 
		if (p) delete[]p; 
		p=new int[n];
		for (int i=0; i<n; ++i)
		{
			p[i]=newVector[i];
		}
	}

	void deleteVector()
	{
		if (p) delete []p;
		p=NULL;
	}

	void setN(int newN)
	{
		p=(int*)realloc(p,sizeof(int)*newN);
		for (n; n<newN; n++) p[n]=0;
	}

	int getElement(int index)
	{
		return p[index];
	}
	
	void setElement(int index,int value)
	{
		p[index]=value;
	}

	//returns the product of all negative elements from vector
	int getNegativeProduct()
	{
		int product=1;
		for (int i=0; i<n; ++i)
		{
			if (p[i]<0) product*=p[i];
		}
		return product;
	}

};


int main ()
{
	vector a,b,c;

	cout << "Give data about first vector:" << endl;
	cout << "How many elements does it have?"<< endl;
	int n,a1[100];
	cin >> n;
	for (int i=0; i<n; ++i)
	{
		cout << "Give next element:" << endl;
		cin >> a1[i];
	}
	a.initVector(a1,n);

	cout << "Give data about second vector:" << endl;
	
	for (int i=0; i<n; ++i)
	{
		cout << "Give next element:" << endl;
		cin >> a1[i];
	}
	b.initVector(a1,n);

	c.setN(n);
	cout << "Product of vectors is:"<<endl;
	for (int i=0; i<n; ++i)
	{
		c.setElement(i,a.getElement(i)*b.getElement(i));
		cout << c.getElement(i) << " ";
	}

	// system("PAUSE");
	return 0;
}

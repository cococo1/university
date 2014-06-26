#include <iostream>

using namespace std;

template <typename T>
T* pairChange( T* a, int n)
{
	T *newA=new T[n];

	int i;
	for (i=0; i<n-1; i=i+2)
	{
		newA[i]=a[i]+a[i+1];
		newA[i+1]=a[i]-a[i+1];
	}
	if (n%2) newA[i]=a[i];
	return newA;
}

int main()
{
	int a1[]={1,2,3,4,5};
	int *a2=pairChange(a1,5);
	for (int i=0; i<5; i++)
	{
		cout <<a2[i]<<" ";
	}
	cout << endl;

	double b1[]={2.2,-2.1,3,4.0,5.2};
	double *b2=pairChange(b1,5);
	for (int i=0; i<5; i++)
	{
		cout <<b2[i]<<" ";
	}
	cout <<endl;

	char c1[]={'a','b','c','d','e'};
	char *c2=pairChange(c1,5);
	for (int i=0; i<5; i++)
	{
		cout <<c2[i]<<" ";
	}
	cout << endl;


	return 0;
}

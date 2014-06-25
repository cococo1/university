#include <iostream>

using namespace std;


long int calls1,calls2,calls3;


long long int fib1(int n)
{
calls1++;


if (n<2)  return n;
	else return (fib1(n-1)+fib1(n-2));
}

long double fib2(int n)
{
	calls2=n;
	int i=1;
	int j=0;
	for (int k=0; k<n; k++)
	{
		j=i+j;
		i=j-i;
	}
	return j;
}

long double fib3(int n)
{
	int i=1;
	int j=0;
	int k=0;
	int h=1;
	int t;

	while (n>0)
	{
		calls3++;
		if (n%2) 
		{
			t=j*h;
			j=i*h+j*k+t;
			i=i*k+t;
		}
		t=h*h;
		h=2*k*h+t;
		k=k*k+t;
		n=n/2;

	}
	return j;	
}

int main()
{
	calls1=calls2=calls3=0;

	int n;
	cout << "Give n:" << endl;
	cin >> n;
	fib1(n);
	fib2(n);
	fib3(n);
	cout << "Fibonacci " << n<<"'s term is : "<< fib1(n)<< " ; calls: " << calls1 << endl;
	cout << "Fibonacci " << n<<"'s term is : "<< fib2(n)<< " ; calls: " << calls2 << endl;
	cout << "Fibonacci " << n<<"'s term is : "<< fib3(n)<< " ; calls: " << calls3 << endl;


// system("PAUSE");
	return 0;
}

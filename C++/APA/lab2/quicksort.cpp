#include <iostream>

using namespace std;

long long int iterations=0;
long long int comparisons=0;
long long int functionCalls=0;

void qSort(int *a, int initialLeft, int initialRight)
{
	functionCalls++;
	int lower, upper;
	int pivotValue=a[(initialLeft+initialRight)/2];
	lower=initialLeft;
	upper=initialRight;

	comparisons++;
	while (lower<upper)
	{
		comparisons++;
		iterations++;
		while (a[lower]<pivotValue) { lower++; comparisons++; iterations++;}
		while (a[upper]>pivotValue) { upper--; comparisons++; iterations++;}
		comparisons++;
		if (lower<=upper)
		{int t=a[lower];
		a[lower]=a[upper];
		a[upper]=t;
		lower++;
		upper--;
		}
	}
	comparisons++;
	comparisons++;
	if (lower<initialRight) qSort(a,lower,initialRight);
	if (upper>initialLeft) qSort(a,initialLeft,upper);

}

int main()
{	
	int n;
	cout << "Give n:"<<endl;
	cin >> n;

	int *a=new int[n];

	for (int i=0; i<n; i++)
	{
		a[i]=i;//rand()%100000;
	}
	cout << endl;


	qSort(a,0,n-1);
	cout << " Iterations: "<<iterations<<" comparisons: "<<comparisons<< " function calls: "<<functionCalls <<endl;

	
	return 0;
}

#include <iostream>

using namespace std;

class matrix
{
	int **p;
	int n;

public:
	matrix()
	{
		p=NULL;
		n=0;
	}
	matrix(const matrix &copy)
	{
		n=copy.n;
		p=new int*[n];
		for (int i=0; i<n; ++i)
		{
			p[i]=new int[n];
			for (int j=0; j<n; ++j)
			{
				p[i][j]=copy.p[i][j];
			}
		}
	}

		matrix( int n1)
	{
		n=n1;
		p=new int*[n];
		for (int i=0; i<n; ++i)
		{
			p[i]=new int[n];
			for (int j=0; j<n; ++j)
			{
				p[i][j]=0;
			}
		}
	}

		matrix(const matrix &m1, const matrix &m2, const matrix &m3, const matrix &m4)
		{
			n=m1.n*2;
			p=new int*[n];
			for (int i=0; i<n; ++i)
			{
				p[i]=new int[n];
				for (int j=0; j<n; ++j)
				{
					if (i<n/2 && j<n/2) p[i][j]=m1.p[i][j];
					if (i<n/2 && j>=n/2) p[i][j]=m2.p[i][j-n/2];
					if (i>=n/2 && j<n/2) p[i][j]=m3.p[i-n/2][j];
					if (i>=n/2 && j>=n/2) p[i][j]=m4.p[i-n/2][j-n/2];
				}
			}
		}

	matrix( int **ptr, int n1)
	{
		n=n1;
		p=new int*[n];
		for (int i=0; i<n; ++i)
		{
			p[i]=new int[n];
			for (int j=0; j<n; ++j)
			{
				p[i][j]=ptr[i][j];
			}
		}
	}

	~matrix()
	{
		if (p) 
			{
				for (int i=0; i<n; ++i)
				{
						delete []p[i];
				}
				delete []p;
		}
	}

	bool isMultipleOf2(int n)
	{
		cout << "n="<<n <<endl;
		while (n>2)
		{
			n=n/2;
		}
		return (n==2);
	}

		void showMatrix()
	{
		if (!p) 
		{
			cout << "Error 1: No memory allocated for p. Pointer is NULL"<<endl;
			return ;
		}
		for (int i=0; i<n; ++i)
		{
			for (int j=0; j<n; ++j)
			{
				cout << "  " << p[i][j];
			}
			cout << endl;
		}
	}

		matrix& one(matrix &m)
		{
			matrix result(m.n/2);
			for (int i=0; i<result.n; i++)
			{
				for (int j=0; j<result.n; j++)
				{
					result.p[i][j]=m.p[i][j];
				}
			}
			return *new matrix(result);
		}

		matrix& two(matrix &m)
		{
			matrix result(m.n/2);
			for (int i=0; i<result.n; i++)
			{
				for (int j=0; j<result.n; j++)
				{
					result.p[i][j]=m.p[i][j+n/2];
				}
			}
			return *new matrix(result);
		}

		matrix& three(matrix &m)
		{
			matrix result(m.n/2);
			for (int i=0; i<result.n; i++)
			{
				for (int j=0; j<result.n; j++)
				{
					result.p[i][j]=m.p[i+n/2][j];
				}
			}
			return *new matrix(result);
		}

		matrix& four(matrix &m)
		{
			matrix result(m.n/2);
			for (int i=0; i<result.n; i++)
			{
				for (int j=0; j<result.n; j++)
				{
					result.p[i][j]=m.p[i+n/2][j+n/2];
				}
			}
			return *new matrix(result);
		}
	

		matrix& operator-(matrix &anotherMatrix)
		{
			matrix result(n);
			for (int i=0; i<n; ++i)
			{
				for (int j=0; j<n; ++j)
				{
					result.p[i][j]=p[i][j]-anotherMatrix.p[i][j];
				}
			}
			return *new matrix(result);
		}

				matrix& operator+(matrix &anotherMatrix)
		{
			matrix result(n);
			for (int i=0; i<n; ++i)
			{
				for (int j=0; j<n; ++j)
				{
					result.p[i][j]=p[i][j]+anotherMatrix.p[i][j];
				}
			}
			return *new matrix(result);
		}

	matrix& operator*(matrix &otherMatrix)
	{
		if (otherMatrix.n==n)
		{
			if (n==2)
			{		

					int a=p[0][0];
					int b=p[0][1];
					int c=p[1][0];
					int d=p[1][1];
					int e=otherMatrix.p[0][0];
					int f=otherMatrix.p[1][0];
					int g=otherMatrix.p[0][1];
					int h=otherMatrix.p[1][1];
				
					int ag=a*g;
					int ah=a*h;
					int bh=b*h;
					int ce=c*e;
					int de=d*e;
					int df=d*f;
					int ae=a*e;
					int dh=d*h;
					int bf=b*f;
					int cg=c*g;
					int p1=ag-ah;
					int p2=ah+bh;
					int p3=ce+de;
					int p4=df-de;
					int p5=ae+ah+de+dh;
					int p6=bf+bh-df-dh;
					int p7=ae+ag-ce-cg;

					int r=p5+p4-p2+p6;
					int s=p1+p2;
					int t=p3+p4;
					int u=p5+p1-p3-p7;

					matrix result(2);
					result.p[0][0]=r;
					result.p[0][1]=s;
					result.p[1][0]=t;
					result.p[1][1]=u;



					return *new matrix(result);	
			}
			else
				{
					cout << "Matrixes are not of length 2" <<endl;
					if (otherMatrix.isMultipleOf2(otherMatrix.n))
					{

						matrix a(one(*this));
						matrix b(two(*this));
						matrix c(three(*this));
						matrix d(four(*this));
						matrix e(one(otherMatrix));
						matrix f(three(otherMatrix));
						matrix g(two(otherMatrix));
						matrix h(four(otherMatrix));

						matrix p1(matrix(a*g-a*h));
						matrix p2(matrix(a*h+b*h));
						matrix p3(matrix(c*e+d*e));
						matrix p4(matrix(d*f-d*e));
						matrix p5=(matrix(a*e+a*h+d*e+d*h));
						matrix p6=(matrix(b*f+b*h-d*f-d*h));
						matrix p7=(matrix(a*e+a*g-c*e-c*g));

						matrix r=p5+p4-p2+p6;
						matrix s=p1+p2;
						matrix t=p3+p4;
						matrix u=p5+p1-p3-p7;


						return *new matrix(r,s,t,u);
					}
					else
					{
						cout << "We need matrixes multiples of 2;"<<endl;
						return *new matrix();
					}
			}
		}
		else 
		{
			cout << "We need matrixes of equal length;"<<endl;
			return *new matrix();
		}
	}
	
};



int main()
{	
	int n=0;
	cout << "Give n:"<<endl;
	cin >>n;

	cout << "GIVE FIRST MATRIX:"<<endl;
	int **a1=new int*[n];
	for (int i=0; i<n; i++)
	{
		a1[i]=new int[n];
		for (int j=0; j<n; j++)
		{
			cout << "give next term:"<< endl;
			cin >>a1[i][j];
		}
	}

		cout << "GIVE SECOND MATRIX:"<<endl;
		int **a2=new int*[n];
	for (int i=0; i<n; i++)
	{
		a2[i]=new int[n];
		for (int j=0; j<n; j++)
		{
			cout << "give next term:"<< endl;
			cin >>a2[i][j];
		}
	}

	matrix m1(a1,n);
	m1.showMatrix();
	cout << endl;
		matrix m2(a2,n);
		m2.showMatrix();
cout << "THE PRODUCT IS :"<<endl;
		(m1*m2).showMatrix();

	return 0;
}

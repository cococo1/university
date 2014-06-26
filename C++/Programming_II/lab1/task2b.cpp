//Laboratory Work 1: Programming C++ 
//Author : Chetrusca Maxim
//Last time modifyed : 9.10.2011

#include "iostream"
using namespace std;

class matrix
{
	int **p; //Pointer to pointer to int, indicates the adress of memory for our matrix (2-D array)
	int n,m,error;// n - number of rows, m- number of columns, error- code for error.

public:

	//Default constructor:
	matrix()
	{
		p=NULL;
		n=0;
		m=0;
		error=0;
	}

	//General constructor for quadratic matrix :
	matrix(int n) //n - simple variable of int type, indicates the number of rows and columns; 
	{
		p=new int*[n];
		for (int i=0; i<n; ++i) 
		{
			p[i]=new int[n];
			for (int j=0; j<n; ++j)
			{
				p[i][j]=0;
			}
		}
		this->n=n;
		m=n;
		error=0;
	}

	//Setter for n and m:
	void setnm(int n, int m)// the same meaning as instances from class ;
{
	if (p) delete []p;
	p=new int*[n];
	for (int i=0; i<n; ++i)
	{
		p[i]=new int[m];
		for (int j=0; j<m; ++j)
		{
			p[i][j]=0;
		}
	}
	this->n=n;
	this->m=m;
	error=0;
}

	//General constructor for non-quadratic matrix: 
	matrix(int n, int m)// the same meaning as instances from class ;
	{
		//setnm(n,m);
		p=new int*[n];
		for (int i=0; i<n; ++i)
		{
			p[i]=new int[m];
			for (int j=0; j<m; ++j)
		{
			p[i][j]=0;
		}
		}
		this->n=n;
		this->m=m;
		error=0;
	}


	//Copy constructor:
	matrix(const matrix &newMatrix)//newMatrix- a constant referince to an object of this class ;
	{
		p=new int*[newMatrix.n];
		for (int i=0; i<newMatrix.n; ++i) 
			{
				p[i]=new int[newMatrix.m];
				for (int j=0; j<newMatrix.m; j++)
				{
					p[i][j]=newMatrix.p[i][j];
				}
		}
		m=newMatrix.m;
		n=newMatrix.n;
		error=0;
	}

	//Destructor :
~matrix()
{
	delete []p;
}


int getN()
{
	return n;
}

int getError()
{
	return error;
}

int getM()
{
	return m;
}


int** getP()
{
	return p;
}

//Gets the element [i][j] :
	int get(int i, int j)
	{
		if (!p)
		{ 
			error=1;
			cout << "Error 1: No memory allocated for p. Pointer is NULL"<<endl;
			return 0; 
		}		
		if (i>=n || j>=m)
		{
			error=2;
			cout << "Error 2: Matrix bounds exceeded."<<endl;
			return 0;
		}
		if (i<0 || j<0)
		{
			error=3;
			cout << "Error 3: Negative value to indexes not allowed."<<endl;
			return 0; 
		}
		return p[i][j];
	}

	//Sets to the element [i][j] the coresponding value :
	int set(int i,int j,int value)
	{
		if (!p)
		{ 
			error=1;
			cout << "Error 1: No memory allocated for p. Pointer is NULL"<<endl;
			return 0; 
		}		
		if (i>=n || j>=m)
		{
			error=2;
			cout << "Error 2: Matrix bounds exceeded."<<endl;
			return 0;
		}
		if (i<0 || j<0)
		{
			error=3;
			cout << "Error 3: Negative value to indexes not allowed."<<endl;
			return 0; 
		}
		p[i][j]=value;
		return 1;
	}

	//Prints on the screen the error description :
	void errorDescription()
	{
		if (error==0) cout << "No errors."<<endl;
		else if (error==1) cout << "Error 1: No memory allocated for p. Pointer is NULL"<<endl;
		else if (error==2) cout << "Error 2: Matrix bounds exceeded."<<endl;
		else if (error==3) cout << "Error 3: Negative value to indexes not allowed."<<endl;
	}

	//Multiplies the matrix with the constant :
	matrix multC(int c)
	{
		if (!p) 
		{
			error=1;
			cout << "Error 1: No memory allocated for p. Pointer is NULL"<<endl;
			return *this;
		}
		for (int i=0; i<n; ++i)
		{
			for (int j=0; j<m; ++j)
			{
				p[i][j]*=c;
			}
		}
		return *this;
	}

	//Prints the matrix on the screen :
	void showMatrix()
	{
		if (!p) 
		{
			error=1;
			cout << "Error 1: No memory allocated for p. Pointer is NULL"<<endl;
			return ;
		}
		for (int i=0; i<n; ++i)
		{
			for (int j=0; j<m; ++j)
			{
				cout << " " << p[i][j];
			}
			cout << endl;
		}
	}
};


//Adds two matrixes and returns the pointer to resultant matrix :
matrix* addMatrixes(matrix a, matrix b)
{
	matrix *result=new matrix(a.getN());
	if (!a.getP() || !b.getP()) return NULL;
	for (int i=0; i<a.getN(); i++)
	{
		for (int j=0; j<a.getM(); j++)
		{
			result->set(i,j,a.get(i,j)+b.get(i,j));
			if (a.getError() || b.getError()) return NULL;
		}
	}
	return result;
}

//Subtracts two matrixes and returns the pointer to resultant matrix :
matrix* subtractMatrixes(matrix a, matrix b)
{
	matrix *result=new matrix(a.getN());
	if (!a.getP() || !b.getP()) return NULL;
	for (int i=0; i<a.getN(); i++)
	{
		for (int j=0; j<a.getM(); j++)
		{
			result->set(i,j,a.get(i,j)-b.get(i,j));
			if (a.getError() || b.getError()) return NULL;
		}
	}
	return result;
}

//Multiplies two matrixes and returns the pointer to resultant matrix :
matrix* multMatrixes(matrix a, matrix b)
{
	matrix *result=new matrix(a.getN());
	if (!a.getP() || !b.getP()) return NULL;
	for (int i=0; i<a.getN(); i++)
	{
		for (int j=0; j<a.getN(); j++)
		{
			int value=0;
			for (int l=0; l<a.getN(); l++)
			{
				value=value+a.get(i,l)*b.get(l,i);
			}
			result->set(i,j,value);
			if (a.getError() || b.getError()) return NULL;
		}
	}
	return result;
}


int main ()
{
	matrix a; 
	matrix b(4);
	matrix c(3,4);
	matrix d(b);
	matrix *result=NULL;




	a.showMatrix();


	for (int i=0; i<c.getN(); i++)
		c.set(i,1,92);
	c.showMatrix();


	b.set(0,0,1);
	d.set(0,1,2);
	d.multC(2);
	d.showMatrix();
	result=multMatrixes(b,c);
	if (result)
	{
		result->showMatrix();
		delete result;
	}

	result=subtractMatrixes(d,b);
	if (result)
	{
		result->showMatrix();
		delete result;
	}



	// system("PAUSE");
	return 0;
}

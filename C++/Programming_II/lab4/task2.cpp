#include <iostream>

using namespace std;



template <class T>
class Matrix
{
	int n,m;
	T **p;
public:
	Matrix()
	{

		cout << "Matrix()"<<endl;
		p=NULL;
		n=0;
		m=0;
	}

	Matrix(int n, int m)
	{
		cout <<"Matrix(int n, int m)"<<endl;
		this->n=n;
		this->m=m;
		p=new T*[n];
		for (int i=0; i<n; ++i)
		{
			p[i]=new T[m];
			for (int j=0; j<m; j++)
			{
				p[i][j]=0;
			}
		}
	}

	Matrix(const Matrix<T>& copy)
	{
		cout << "Matrix(const Matrix& copy)"<<endl;
		n=copy.n;
		m=copy.m;
				//cout << n<<" "<<m<<endl;
		p=new T*[n];
		for (int i=0; i<n; ++i)
		{
			p[i]=new T[m];
			for (int j=0; j<m; ++j)
			{
				p[i][j]=copy.p[i][j];
			}
		}
	}

	Matrix(const T** copy,int n,int m)
	{
		cout << "Matrix(const T** copy,int n,int m)"<<endl;
		this->n=n;
		this->m=m;
		p=new T*[n];
		for (int i=0; i<n; ++i)
		{
			p[i]=new T[m];
			for (int j=0; j<m; ++j)
			{
				p[i][j]=copy[i][j];
			}
		}
	}

	~Matrix()
	{
		cout << "~Matrix()"<<endl;
		if (p)
		{
			for (int i=0; i<n; ++i)
			{
				delete []p[i];
			}
			delete []p;
		}
	}

	int getRows(){return n;}
	int getCols(){return m;}

	T* operator[](int i)
	{
		cout <<"T* operator[](int i)"<<endl;
		// if (i>=0 && i<n && p)
		 return p[i];
	}

	Matrix<T>& operator+(Matrix<T>& m1)
	{
		cout <<"Matrix& operator+(Matrix& m)"<<endl;
		if (m1.n!=n && m1.m!=m) 
		{
			cout << "Matrices have different size."; 
			return *this;
		}

		Matrix<T> *c=new Matrix(*this);

		for(int i=0; i<n; ++i)
		{
			for (int j=0; j<m; ++j)
			{
				c->p[i][j]+=m1.p[i][j];
			}
		}
		return *c;
	}

	Matrix<T>& operator*(Matrix<T>& m1)
	{
		cout <<"Matrix& operator*(Matrix& m)"<<endl;
		if (n!=m1.m)
		{
			cout << "Nr. of rows is different from nr. of columns"; 
			return *this;
		}

		Matrix<T> *c=new Matrix(n,m1.m);

		for (int i=0; i<n; ++i)
		{
			for (int j=0; j<m1.m; ++j)
			{
				for (int l=0; l<m; ++l)
				{
					c->p[i][j]=c->p[i][j]+(p[j][l]*m1.p[l][j]);
				}
			}
		}
		return *c;
	}

	Matrix<T>& operator=(Matrix<T>& m1)
	{
		if (this!=&m1)
		{

			if (p)
			{
				for (int i=0; i<n; ++i)
				{
					delete []p[i];
				}
				delete []p;
			}

			n=m1.n;
			m=m1.m;
			p=new T*[n];
			for (int i=0; i<n; ++i)
			{
				p[i]=new T[m];
				for (int j=0; j<m; ++j)
				{
					p[i][j]=m1.p[i][j];
				}
			}

		}
		return *this;
	}
	friend ostream& operator<< (ostream& stream,const Matrix& m)
    {
        for(int i=0; i<m.n; i++)
        {
            for(int j=0; j<m.m; j++)
            {
                stream<<" "<<m.p[i][j];
            }
            stream<<endl;
        }
        return stream;
    }
	friend istream& operator>> (istream& stream, Matrix& m1)
    {
        cout << "Give n and m:"<<endl;
        int n,m;
        stream>>n;
        stream>>m;
        
        if (m1.p)
        {
            for (int i=0; i<m1.n; i++)
            {
                delete m1.p[i];
            }
            delete []m1.p;
        }
        
        m1.n=n;
        m1.m=m;
        
        m1.p=new T*[n];
        cout << "Give the elements:"<<endl;
        for (int i=0; i<n; ++i)
        {
            m1.p[i]=new T[m];
            for (int j=0; j<m; j++)
            {
                stream>>m1.p[i][j];
            }
        }
        return stream;

    }
    
};






int main()
{
	Matrix<int> m(2,2);
	cin>>m;
	cout<<m <<endl;

	Matrix<int>  k;
	k=m+m;
	cout <<k<<endl;

	Matrix<int> h;
	cin >>h;
	cout<<h<<endl;
	cout<<m*h<<endl;

	cout << m[1][1] <<endl;

	Matrix<double> d;
	cin>>d;
	cout<<d<<endl;
	
	return 0;
}

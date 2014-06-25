#include <iostream>

using namespace std;
int iterations=0;

void dijkstra(int** graph,int n)
{
	for (int i=0; i<n; i++)
	{
		bool *a=new bool[n];
		for(int i1=0; i1<n; i1++)
		{
			a[i1]=true;
		}
		int min=1000000,jmin=0;
		for(int i3=0; i3<n; i3++)
		{
			min=1000000,jmin=0;
			for(int i2=0; i2<n; i2++)
			{
				iterations++;
				if (a[i2] && (graph[i][i2]<min) && (i2!=i))
				{
					min=graph[i][i2];
					jmin=i2;
				}
			}
			//int k;
			a[jmin]=false;
			//cout<<"min="<<min<<" v="<<jmin<<endl;
			//cin>>k;

			for(int j=0; j<n; j++)
			{
				if (graph[i][j]>(min+graph[jmin][j])) 
				{
					graph[i][j]=min+graph[jmin][j];
				}
			//	cout<<"D[i][j]="<<graph[i][j]<<" ";
			//	cin>>k;
			}
		}
		delete(a);
	}
}

void floyd(int** graph,int n)
{
	for(int k=0; k<n; k++)
	{
		for(int i=0; i<n; i++)
		{
			if (i!=k)
			{
				for(int j=0; j<n; j++)
				{
					if (j!=k)
					{
						iterations++;
						if (graph[i][j]>(graph[i][k]+graph[k][j]))
							graph[i][j]=(graph[i][k]+graph[k][j]);
					}
				}
			}
		}
	}
}

int main()
{
	int n,edges=0;
	cout<< "Give the number of nodes:"<<endl;
	cin>>n;
	int **graph=new int*[n];
	for (int i=0; i<n; i++)
	{
		graph[i]=new int[n];
		for (int j=0; j<n; ++j)
		{

			if (j==i) 
			{
				graph[i][j]=0;
			}
			else 
			{
				int p=rand()%100;
				if (p<20)
					{
						graph[i][j]=rand()%10;
						edges++;
				}
				else graph[i][j]=1000000;

				/*cout<<i+1<<"->"<<j+1<<" :"<<endl;
				cin>>graph[i][j];*/
			}
		}
	}/*
		for (int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout<<" "<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	dijkstra(graph,n);
	//floyd(graph,n);
/*
	cout<<endl<<endl;

	for (int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout<<" "<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
	*/
	cout<<" edges:"<<edges<<" Iterations:"<<iterations;

	return 0;
}

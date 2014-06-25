#include <iostream>
#include <set>
using namespace std;

long long iterations;

class Arc
{
public:
	double value;
	int edge1,edge2;
};

Arc* sortedSetOfArcs(double** g, int n,int *nrOfArcs)
{
	Arc *setOfArcs=new Arc[n*n];
	int l=0;
	for(int i=0; i<n; ++i)
	{
		for (int j=0; j<n;++j)
		{
			if (g[i][j]!=0)
			{
				setOfArcs[l].edge1=i;
				setOfArcs[l].edge2=j;
				setOfArcs[l].value=g[i][j];
				l++;
			}
		}
	}
	*nrOfArcs=l;
	Arc* sortedArcs=new Arc[l];
	for(int i=0; i<l; ++i)
	{
		sortedArcs[i]=setOfArcs[i];
	//	cout <<sortedArcs[i].value<<" ";
	}
	//cout<<endl;
	delete []setOfArcs;

	for (int i=0; i<l-1; ++i)
	{
		for (int j=0; j<l-1; ++j)
		{
			if (sortedArcs[j].value>sortedArcs[j+1].value)
			{
				Arc a=sortedArcs[j];
				sortedArcs[j]=sortedArcs[j+1];
				sortedArcs[j+1]=a;
			}
		}
	}
	return sortedArcs;
}

double** kruscall(double** g, int n)
{
	int nrOfArcs;
	Arc *sortedArcs=sortedSetOfArcs(g,n,&nrOfArcs);
	/*for(int i=0; i<nrOfArcs; i++)
	{
		//cout<<"The arc:"<<sortedArcs[i].edge1<<"-"<<sortedArcs[i].edge2<<":"<<sortedArcs[i].value<<endl;
	}*/
	double **solution=new double*[n];
	for(int i=0; i<n; ++i)
	{
		solution[i]=new double[n];
		for(int j=0; j<n; ++j)
		{
			solution[i][j]=0;
		}
	}

	//int **setOfEdges=new int*[n];
	set<int> *edges=new set<int>[n];
	for (int i=0; i<n; ++i)
	{
		iterations++;
		set<int> aSet;
		aSet.insert(i);
		edges[i]=aSet;
	}

	Arc *solutionArcs=new Arc[n-1];
	int l=0;
	for(int i=0; i<nrOfArcs; i++)
	{
		Arc anArc=sortedArcs[i];
		for(int j=0; j<n; j++)
		{
			iterations++;
			if(!edges[j].empty())
			{
				bool one=(edges[j].find(anArc.edge1)!=edges[j].end());
				bool two=(edges[j].find(anArc.edge2)!=edges[j].end());
				if ((one && !two) || (!one && two)) 
				{

					set<int>::iterator it;

						solutionArcs[l]=anArc;
						l++;
						if (one) 
						{
							set<int> aSet;
							for(int e=0;e<n; e++)
							{
								if (edges[e].find(anArc.edge2)!=edges[e].end())
								{
									aSet=edges[e];
									edges[e].clear();
									break;
								}
							}
							for(it=aSet.begin(); it!=aSet.end();++it)
								{
								edges[j].insert(*it);
								}
						}
						else 
						{
							set<int> aSet;
							for(int e=0;e<n; e++)
							{
								if (edges[e].find(anArc.edge1)!=edges[e].end())
								{
									aSet=edges[e];
									edges[e].clear();
									break;
								}
							}
							for(it=aSet.begin(); it!=aSet.end();++it)
								{
								edges[j].insert(*it);
								}
						}
						break;
				}
			}
		}
				
	}
	//cout<<l<<endl;
	for(int i=0; i<l; i++)
	{
		solution[solutionArcs[i].edge1][solutionArcs[i].edge2]=solutionArcs[i].value;
	}

	

	return solution;
}

double **prim(double** g, int n)
{
	int nrOfArcs;
	Arc *sortedArcs=sortedSetOfArcs(g,n,&nrOfArcs);

	double **solution=new double*[n];
	for(int i=0; i<n; ++i)
	{
		solution[i]=new double[n];
		for(int j=0; j<n; ++j)
		{
			solution[i][j]=0;
		}
	}

	set<int> edges;
	edges.insert(0);

	Arc *solutionArcs=new Arc[n-1];
	int l=0;

	while (edges.size()<n)
	{
		double min=100000000;
		int newEdge;
		Arc anArc;
		set<int>::iterator it;
		for(it=edges.begin(); it!=edges.end();++it)
		{
			int edge=*it;

			for (int i=0; i<nrOfArcs; i++)
			{

				if (sortedArcs[i].edge1==edge)
				{	
					iterations++;
					if (edges.find(sortedArcs[i].edge2)==edges.end())
					{
						if (sortedArcs[i].value<min)
						{
							newEdge=sortedArcs[i].edge2;
							anArc=sortedArcs[i];
							min=sortedArcs[i].value;
							break;
						}
					}
				}
				else if (sortedArcs[i].edge2==edge)
				{
					iterations++;
					if (edges.find(sortedArcs[i].edge1)==edges.end())
					{
						if (sortedArcs[i].value<min)
						{
							newEdge=sortedArcs[i].edge1;
							anArc=sortedArcs[i];
							min=sortedArcs[i].value;
							break;
						}
					}
				}
			}
		}
			edges.insert(newEdge);
			solutionArcs[l]=anArc;
			l++;
	}

	for(int i=0; i<l; i++)
	{
		solution[solutionArcs[i].edge1][solutionArcs[i].edge2]=solutionArcs[i].value;
	}
	return solution;
}


int main()
{
	
	double **graph;
	cout<< "Give the number of edges:"<<endl;
	long n,e=0;
	cin>>n;
	cout <<"Give the edges:"<<endl;
	graph=new double*[n];
	for(int i=0; i<n; ++i)
	{
		graph[i]=new double[n];
		for(int j=0; j<n; ++j)
		{
			/*cout<<"G["<<i+1<<"]["<<j+1<<"]=";
			cin>>graph[i][j];*/
			int p=rand()%100;
			if (p<50)
			{
			graph[i][j]=rand()%10;
			e++;
			}
			else graph[i][j]=0;
			//cout<<" "<< graph[i][j];
		}
		//cout<<endl;
	}
	//prim(graph,n); kruscall(graph,n);
	double **spann= prim(graph,n);
	//cout<<endl;
/*	for(int i=0;i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout<<" "<<spann[i][j];
		}
		cout<<endl;
	}*/

	cout<<"Iterations:"<<iterations<< " edges: "<<e;


	return 0;
}

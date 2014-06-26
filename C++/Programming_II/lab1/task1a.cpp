//Laboratory Work 1 : C++
//Author : Chetrusca Maxim
//Last editted : 09.10.2011


#include <iostream>

using namespace std;


class monitor
{
private:
	char *firm;//pointer to char that indicates name of the firm
	double dimension; //dimensions of the monitor
	int nrOfColours;//number o colours
	int xPixels,yPixels;//resolution : width and height


public:

	//Default constructor :
	 monitor()
	{
		firm=NULL;
		dimension=0;
		nrOfColours=0;
		xPixels=0;
		yPixels=0;
	}

	void setNrOfColours(int newNumber)
	{ nrOfColours=newNumber; }
	
	int getNrOfColours()
	{return nrOfColours; }

	void setFirm(char* newFirm)
	{
		if (firm)delete[]firm;
		firm=new char[strlen(newFirm)+1];
		strcpy(firm,newFirm);
	}

	char* getFirm()
	{ return firm;  }

	void setDimension(double newDimension)
	{ dimension=newDimension;}

	double getDimension()
	{ return dimension; }

	void setPixels(int newXPixels,int newYPixels)
	{
		xPixels=newXPixels;
		yPixels=newYPixels;
	}

	int getXPixels() 
	{return xPixels;}

	int getYPixels()
	{ return yPixels; }

	void freeMem()
	{
		if (firm) delete []firm;
		firm=NULL;
	}


};

void input (monitor *a,int n)
{
	for (int i=0; i<n; ++i)
	{
		cout << "Give the data about screen "<< i+1 << endl;
		cout << "Firm:"<< endl;
		char newFirm[100];
		cin >> newFirm;
		a[i].setFirm(newFirm);
		cout << "Dimension:"<<endl;
		int newDimension;
		cin >> newDimension;
		a[i].setDimension(newDimension);
		cout << "Nr. of colours:" << endl;
		int newNrOfColours;
		cin >> newNrOfColours;
		a[i].setNrOfColours(newNrOfColours);
		cout << "Resolution (x,y):" << endl;
		int newX,newY;
		cin >>newX >>newY;
		a[i].setPixels(newX,newY);
	}
}

monitor* searchByDimension(int dimension,monitor *a, int n)
{
	for (int i=0; i<n; ++i)
	{
		if (a[i].getDimension()==dimension) return &a[i];
	}
	return NULL;
}

monitor* searchByFirm(char *wantedFirm,monitor *a, int n)
{
		for (int i=0; i<n; ++i)
	{
		if (!strcmp(a[i].getFirm(),wantedFirm)) return &a[i];
	}
	return NULL;
}


int main()
{
	monitor *a=NULL,*b=NULL;
	cout << "Give the nr. of monitors:"<<endl;
	int n;
	cin >> n;
	a=new monitor[n];
	input(a,n);
	char wanted[100];
	cout << "Give the name of the firm you want to find:" << endl;
	cin >> wanted;

	b=searchByFirm(wanted,a,n);

	if (b) cout << "Monitor was found! The Firm:" << b->getFirm();
	else cout << "Monitor not found."<< endl;


	delete []a;
	// system("PAUSE");
	return 0;
}

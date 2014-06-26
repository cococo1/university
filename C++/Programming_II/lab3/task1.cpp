#include <iostream>

using namespace std;
class airTransport
{

	int lengthOfFly;
public:
	char* name;
	airTransport()
	{
		cout <<"airTransport();"<<endl;
		name=NULL;
		lengthOfFly=0;
	}
	airTransport(const airTransport &copy)
	{
		cout <<"airTransport(const airTransport &copy);"<<endl;
		name=new char[strlen(copy.name)+1];
		strcpy(name,copy.name);
		lengthOfFly=copy.lengthOfFly;
	}
~airTransport()
{
	cout << "~airTransport();"<<endl;
	if (name) delete []name;
}

airTransport& operator=(const airTransport& result)
{
	cout << "airTransport& operator=(const airTransport& result)"<<endl;
	if (this!=&result)
	{
		if (name) delete []name;
		name=new char[strlen(result.name)+1];
		strcpy(name,result.name);
		lengthOfFly=result.lengthOfFly;
	}
	return *this;
}

int getLengthOfFly() { return lengthOfFly;}

void setLengthOfFly(int newLengthOfFly)
{
	lengthOfFly=newLengthOfFly;
}

};

class passengerTransport
{

	int numberOfPassengers;
public:
	char *name;
	passengerTransport()
	{
		cout << "passengerTransport()"<<endl;
		name=NULL;
		numberOfPassengers=0;
	}
	passengerTransport(const passengerTransport &copy)
	{
		cout << "passengerTransport(const passengerTransport &copy)"<<endl;
		name=new char[strlen(copy.name)+1];
		strcpy(name,copy.name);
		numberOfPassengers=copy.numberOfPassengers;
	}
~passengerTransport()
{
	cout << "~passengerTransport()"<<endl;
	if (name) delete []name;
}

passengerTransport& operator=(const passengerTransport& result)
{
	cout << "passengerTransport& operator=(const passengerTransport& result)"<<endl;
	if (this!=&result)
	{
		if (name) delete []name;
		name=new char[strlen(result.name)+1];
		strcpy(name,result.name);
		numberOfPassengers=result.numberOfPassengers;
	}
	return *this;
}

int getNumberOfPassengers() { return numberOfPassengers;}

void setNumbersOfPassengers(int newNumberOfPassengers)
{
	numberOfPassengers=newNumberOfPassengers;
}

};

class Boing747 : public airTransport, public passengerTransport
{

	int comfort;//Number of stars
	int volumeOfFuel;

public:

	Boing747():airTransport(),passengerTransport()
	{
		cout <<"Boing747()"<<endl; 
		comfort=0;
		volumeOfFuel=0;
	}

	Boing747(const Boing747& copy): airTransport(copy), passengerTransport(copy)
	{
		cout << "Boing747(const Boing747& copy)"<<endl;
		comfort=copy.comfort;
		volumeOfFuel=copy.volumeOfFuel;
	}
	
	~Boing747()//:~airTransport(),~passengerTransport()
	{
		cout << "~Boing747()"<<endl;
		//airTransport::~airTransport();
		//passengerTransport::~passengerTransport();
	}

	void setComfort(int newComfort)
	{ 
		if (newComfort>5) comfort=5;
		else if (newComfort<0) comfort=0;
		else comfort=newComfort;
	}

	int getComfort() {return comfort; }

	void setVolumeOfFuel(int newVolumeOfFuel)
	{
		volumeOfFuel=newVolumeOfFuel;
	}

	int getVolumeOfFuel() {return volumeOfFuel;}
};

int main()
{
	Boing747 b;

	b.airTransport::setLengthOfFly(100);
	//b.name="123"; ERROR !!!
	b.passengerTransport::name=new char[10];
	strcpy(b.passengerTransport::name,"Boing 747");
	b.airTransport::name=new char[10];
	strcpy(b.airTransport::name,"plane");
	cout << "The name of air transport is: " <<b.airTransport::name <<endl;
	cout << "The name of passenger transport is:"<<b.passengerTransport::name <<endl;

	airTransport *a=new Boing747(b);
	cout << "This air transport is:"<<a->name<<endl;

	delete a; //Is it a leak ???*/
//	system("PAUSE");
	return 0;
}
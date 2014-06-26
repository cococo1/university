#include <iostream>

using namespace std;


class transport
{
	int speed;
	int yearOfProduction;
public:
	char *name;
	transport()
	{
		cout <<"transport();"<<endl;
		name=NULL;
		speed=0;
		yearOfProduction=0;
	}

	transport(int newSpeed, int newYearOfProduction, char* newName)
	{
		cout<<"transport(int newSpeed, int newYearOfProduction, char* newName)"<<endl;
		speed=newSpeed;
		yearOfProduction=newYearOfProduction;
		name=new char[(strlen(newName)+1)];
		strcpy(name,newName);
	}

	transport(const transport &copy)
	{
		cout <<"transport(const transport &copy);"<<endl;
		name=new char[strlen(copy.name)+1];
		strcpy(name,copy.name);
		speed=copy.speed;
		yearOfProduction=copy.yearOfProduction;
	}
~transport()
{
	cout << "~transport();"<<endl;
	if (name) delete []name;
}

transport& operator=(const transport& result)
{
	cout << "transport& operator=(const transport& result)"<<endl;
	if (this!=&result)
	{
		if (name) delete []name;
		name=new char[strlen(result.name)+1];
		strcpy(name,result.name);
		speed=result.speed;
		yearOfProduction=result.yearOfProduction;
	}
	return *this;
}

friend ostream& operator<<(ostream& stream,transport &t);

int getSpeed() { return speed;}

void setSpeed(int newSpeed)
{
	speed=newSpeed;
}

int getYearOfProduction() { return yearOfProduction; }

void setYearOfProduction(int newYearOfProduction) {yearOfProduction=newYearOfProduction;}
};

ostream& operator<<(ostream& stream,transport &t)
{
	stream<<"Info about a transport: "<<endl;
	stream<<"Name: "<<t.name<<endl;
	stream<<"Speed: "<<t.speed<<endl;
	stream<<"Year: "<<t.yearOfProduction<<endl;
	return stream;
}

class airTransport : public virtual transport
{

	int lengthOfFly;
public:
	airTransport():transport()
	{
		cout <<"airTransport();"<<endl;
		name=NULL;
		lengthOfFly=0;
	}

	airTransport(int newSpeed,int newYearOfProduction,char* newName,int newLengthOfFly):transport(newSpeed,newYearOfProduction,newName)
	{
		cout << "airTransport(int newSpeed,int newYearOfProduction,char* newName,int newLengthOfFly)"<<endl;
		lengthOfFly=newLengthOfFly;
	}

	airTransport(const airTransport &copy):transport(copy)
	{
		cout <<"airTransport(const airTransport &copy);"<<endl;
		name=new char[strlen(copy.name)+1];
		strcpy(name,copy.name);
		lengthOfFly=copy.lengthOfFly;
	}
~airTransport()
{
	cout << "~airTransport();"<<endl;
}

airTransport& operator=(const airTransport& result)
{
	cout << "airTransport& operator=(const airTransport& result)"<<endl;
	if (this!=&result)
	{
		transport::operator=(result);
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

class passengerTransport: public virtual transport
{

	int numberOfPassengers;
public:
	passengerTransport()//:transport()
	{
		cout << "passengerTransport()"<<endl;
		name=NULL;
		numberOfPassengers=0;
	}
	passengerTransport(int newSpeed,int newYearOfProduction, char* newName,int newNumberOfPassengers):transport(newSpeed,newYearOfProduction,newName)
	{
		cout <<"passengerTransport(int newSpeed,int newYearOfProduction, char* newName,int newNumberOfPassengers)"<<endl;
		numberOfPassengers=newNumberOfPassengers;
	}
	passengerTransport(const passengerTransport &copy)//:transport(copy)
	{
		cout << "passengerTransport(const passengerTransport &copy)"<<endl;
		name=new char[strlen(copy.name)+1];
		strcpy(name,copy.name);
		numberOfPassengers=copy.numberOfPassengers;
	}
~passengerTransport()
{
	cout << "~passengerTransport()"<<endl;
}

passengerTransport& operator=(const passengerTransport& result)
{
	cout << "passengerTransport& operator=(const passengerTransport& result)"<<endl;
	if (this!=&result)
	{
		transport::operator=(result);
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

	Boing747():airTransport(),passengerTransport(),transport()
	{
		cout <<"Boing747()"<<endl; 
		comfort=0;
		volumeOfFuel=0;
	}

	Boing747(const Boing747& copy): airTransport(copy), passengerTransport(copy), transport(copy)
	{
		cout << "Boing747(const Boing747& copy)"<<endl;
		comfort=copy.comfort;
		volumeOfFuel=copy.volumeOfFuel;
	}

	Boing747(int speed,int yearOfProduction,char* name,int lengthOfFly,int numberOfPassengers,int comfort,int volumeOfFuel)
		:airTransport(speed,yearOfProduction,name,lengthOfFly), passengerTransport(speed,yearOfProduction,name,numberOfPassengers),
		transport(speed,yearOfProduction,name)
	{
		this->comfort=comfort;
		this->volumeOfFuel=volumeOfFuel;
	}

	
	~Boing747()
	{
		cout << "~Boing747()"<<endl;
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
	/*transport *t1=new airTransport(10,1991,"1",1000);
	transport *t2=new transport(*t1);
	strcpy(t1->name,"one");
	transport *t3=new airTransport(13,333,"3",3003);
	*t2=*t3;
	//cout <<t2->lengthOfFly; ERROR!

	cout << endl << endl;
	passengerTransport a1(1,1,"one",1);
	passengerTransport a2(2,2,"two",2);
	a2=a1;
	

	cout << a2.name<<endl;
	cout << endl << endl;

	Boing747 b(700,2007,"Atlantic Air",2000,500,4,7000);
	cout << b.name<<endl;
	cout << endl << endl;
	Boing747 b2;*/

	transport a[4];
	transport t(300,2000,"transport");
	airTransport a1(700,1999,"plane",400);
	passengerTransport p(430,2007,"train",1000);
	Boing747 b(700,2003,"Boing 1",1800,600,4,4000);

	a[0]=t;
	a[1]=a1;
	a[2]=p;
	a[3]=b;

	for (int i=0; i<4; ++i)
	{
		cout << a[i] <<endl;
	}


	return 0;
}

#include "iostream"

using namespace std;


class Bool
{
//simple private instance of class Bool of int type
// 0 if false, 1 if true by default but true for any non-zero value
	  int value; 

public:
//Default constructor 
//initialize the value with 0.
	Bool()
	{
		value=0;
	}

//Type conversion constructor 
//handle int type, convert it into Bool type
	Bool(int x)
	{
		if (!x) value=0;
		else value=1;
	}
	
//Getter for value:
       int getValue()
       {return value;}
//Overloading of operators :
// logical OR:
	Bool operator+(Bool a )
	{
		return Bool(a.value || value);
	}

//logical AND:
	Bool operator*(Bool a)
	{
		return Bool(a.value && value);
	}
//logical XOR:
	Bool operator^(Bool a)
	{
		return Bool((a.value || value) && (!a.value || !value));
	}
//overloading of operators using friend functions:
//In order to perform such operations : 5+b, or 2*s, etc.
    friend Bool operator+(int, Bool);
    friend Bool operator*(int, Bool);
    friend Bool operator^(int, Bool);
    
    
	friend Bool operator==(Bool ,Bool );
	friend Bool operator!=(Bool , Bool );
};

//Friend functions :
         
Bool operator+(int x ,Bool a )
	{
		return Bool(a+x);
	}
	
Bool operator*(int x, Bool a)
{
     return Bool(a*x);
}
	    
	    
Bool operator^(int x, Bool a)
{
     return Bool(a^x);
}
    
Bool operator==(Bool a,Bool b)
{
     return Bool(a.value==b.value);
}

Bool operator!=(Bool a, Bool b)
{
     return Bool(a.value!=b.value);
}

int main()
{
  Bool a(1),b(a);
  cout << (0^a).getValue() <<endl;
  cout <<" a=" <<a.getValue()  <<" b="<< b.getValue() <<endl; 
  cout << "a OR b ="<<(a+b).getValue() << endl; 
  cout << "a AND b ="<<(a*b).getValue() << endl; 
  cout << "a XOR b ="<<(a^b).getValue() << endl; 
  cout << "a == b ="<<(a==b).getValue() << endl; 
  cout << "a != b ="<<(a!=b).getValue() << endl; 
  // system("PAUSE");
	return 0;}
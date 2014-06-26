#include <iostream>
using namespace std;

class String1
{
// simple private instance of int type
//indicate number of characters in array
//NULL-byte not included
      int n;
//simple private instance of char* type
//represent the pointer to memory dinamically alocated
//for the first element of array of characters
      char *word;
public:
       
       char* getWord() {return word;}
//Returns the length of the string
int length() {return n;}
//Default constructor :
//simply initialize everything with 0
       String1()
       {
             n=0;
             word=NULL;  
       }
//Copy constructor :
//alocates memory for pointer word
//creates a copy of string
       String1 (const String1& copy)
       {
            n=copy.n;
            word=new char[n+1];
            strcpy(word,copy.word);  
       }

//Conversion constructor :
//takes a char* terminated with NULL byte 
       String1(const char* word1)
       {
                    n=strlen(word1);
                    word=new char[n+1];
                    strcpy(word,word1);
       }    
       
//Destructor: we have allocated memory,  so we need to dealocate it
       ~String1()
       {
                if (word) delete []word;
       } 

//Overloading of + operator - concatenation of two strings  
//first we find the length of our new string, 
//next we allocate memory for it 
//and copy first string, and concatenate second one.   
String1 operator+(String1 b)
{
       String1 c;
       c.n=n+b.n;
       c.word=new char[c.n+1];
       strcpy(c.word,word);
       strcat(c.word,b.word);
       return c;
}

//Overloading of = operator :
//we simply return a copy of given string, 
//using copy constructor


String1& operator=(String1 b)
{
        if (this!=&b)
       if (word) delete []word;
       n=b.n;
       word=new char[n];
       strcpy(word,b.word);
       return *this;      
}


//Overloading of += operator :
//We need to change the word of this object,
//and return a copy of this changed object.
//To reallocate memory, and not loose our initial word,
//we create a temporar variable char* finalWord
String1 operator+=(String1 b)
{
       n=n+b.n;
       char *finalWord=new char[n]; 
       strcpy(finalWord,word);
       strcat(finalWord,b.word);  
      if (word) delete []word;
       word=new char[n];
       strcpy(word,finalWord); 
       delete []finalWord;
       return *this;   
}
//Overloading of operator []
//i - index
//returns NULL byte if word is NULL or index exceeds bounds
char operator[](int i)
{
     if (i>=n || i<0) return '\0';
     else return word[i];
}

//Overloaded operators using friend functions:
 
friend bool operator==(String1 , String1 );
friend bool operator!=(String1 , String1 );
friend bool operator<(String1 , String1 );
friend bool operator>(String1 , String1 );
friend ostream& operator<<(ostream&,String1);
friend istream& operator>>(istream&,String1 &);
 

};


 bool operator==(String1 a, String1 b)
{
    if (!strcmp(a.word,b.word)) return true;
    else return false;         
}

 bool operator!=(String1 a, String1 b)
{
    if (strcmp(a.word,b.word)) return true;
    else return false;         
}

bool operator>(String1 a, String1 b)
{
     if (strcmp(a.word,b.word)>0) return true;
     else return false;    
}

bool operator<(String1 a, String1 b)
{
     if (strcmp(a.word,b.word)<0) return true;
     else return false;    
}

ostream& operator<<(ostream &stream,String1 a)
{
         stream<<a.word;
         return stream;
}

istream& operator>>(istream &stream,String1 &a)
{
         if (a.n>0)
         {
                   delete []a.word;
                   a.n=0;
         }
         char *temp=new char[256];
         stream>>temp;
         a.n=strlen(temp);
         a.word=new char[a.n+1];
         strcpy(a.word,temp);
         delete []temp;
         return stream;
}

int main()
{
    String1 a("asd"), b("aaaaa");

    cout << a << " "<< b << endl;
    String1 c(a=b);
    cout << c << endl;
    a+=b;
    cout << a << endl;
    cin >> c;
    cout << c <<endl;
    a="abc";
    b="bcd";
    cout << (a>b)<< (a==b) << (a!=b) << (a<b) << endl; 
    
    // system("PAUSE");
    return 0;
}

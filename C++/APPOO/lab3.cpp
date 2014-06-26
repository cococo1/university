//
//  main.cpp
//  Lab3APPOO
//
//  Created by Maxim Chetrusca on 3/26/13.
//  Copyright (c) 2013 Maxim Chetrusca. All rights reserved.
//
//----------------------------------------------------------------------------------------------------------------------------------------------------
//Include:
#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <vector>
#include <string>

using namespace std;
//----------------------------------------------------------------------------------------------------------------------------------------------------
//Our class:
class Item
{
    double price;
    int code;
    
public:
    Item():price(0),code(0){}
    Item(double price,int code):price(price),code(0){}
    
    double getPrice(){return price;}
    int getCode(){return code;}
    
    friend bool operator<(Item a, Item b);
    friend istream& operator>>(istream& in, Item& item)
    {
        in >> item.price >> item.code;
        return in;
    }
    friend ostream& operator<<(ostream& out, Item& item)
    {
        out << " price:" << item.price << " code:" << item.code;
        return out;
    }
};

bool operator<(Item a,Item b)
{
    return a.price < b.price;
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
//Some typedefs:

typedef pair<string, Item> myPair;
typedef map<string, Item> Dictionary;
typedef list<Item> ListOfItems;
typedef vector<Item> VectorOfItems;

//----------------------------------------------------------------------------------------------------------------------------------------------------
//Functors:

class cheaperThan
{
    double price;
public:
    cheaperThan(double price):price(price){}
    bool operator()(myPair p)
    {
        return  p.second.getPrice() < price;
    }
};

bool comparator(myPair a, myPair b)
{
    return a.second.getPrice() < b.second.getPrice();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
//Predicates:

bool exactly100(Item& item);

bool greaterForItems(Item a,Item b)
{
    return a.getPrice() > b.getPrice();
    }

bool lessForItems(Item a,Item b)
{
    return a.getPrice() < b.getPrice();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//Functions:

void testInput(Dictionary& d)
{
    string keys[5] = {"Coca Cola","Bentley","Pizza","Mars","PC"};
    Item items[5] = { {1.99,111}, {1000000,222}, {19,112},{1.49,113},{700,333}};
    for (int i=0; i<5; i++)
    {
        d[keys[i]] = items[i];
    }
}

void inputDictionary(Dictionary& dictionary)
{
    int n;
    cout << "How many elements do you have?" << endl;
    cin >> n;
    
    Item item;
    string name;
    for (int i=0; i<n; i++)
    {
        cout << "Name of item - price - code:" << endl;
        cin >> name >> item;
        dictionary[name] = item;
    }
}

void outputDictionary(Dictionary& dictionary,bool ascending)
{
    cout << "Here's the dictionary:" << endl;
    if (ascending)
    {
        Dictionary::iterator mapIterator = dictionary.begin(), end = dictionary.end();
        
        for (; mapIterator != end; mapIterator++)
        {
            //pair.first = key; pair.second = value
            cout << "Key: " << mapIterator->first << " Value: " << mapIterator->second << endl;
        }
    }
    else
    {
        Dictionary::reverse_iterator mapIterator = dictionary.rbegin(), end = dictionary.rend();

        for (; mapIterator != end; mapIterator++)
        {
            
            //pair.first = key; pair.second = value
            cout << "Key: " << mapIterator->first << " Value: " << mapIterator->second << endl;
        }

    }

}

void moveDictionaryToListWithCondition(Dictionary& dictionary,ListOfItems& listOfItems)
{
    Dictionary::iterator mapIterator = find_if(dictionary.begin(), dictionary.end(), cheaperThan(100.0f));
    Dictionary::iterator dictionaryEnd = dictionary.end();
    for (; mapIterator != dictionaryEnd; mapIterator = find_if(++mapIterator, dictionaryEnd, cheaperThan(100.0f)))
    {
        //cout << mapIterator->second << endl;
        listOfItems.push_back(mapIterator->second);
    }
}

void outputListOfItems(ListOfItems& listOfItems)
{
    cout << "Here's the list:" << endl;
    list<Item>::iterator listIterator = listOfItems.begin(), end = listOfItems.end();
    for (; listIterator != end; listIterator++)
    {
        cout << *listIterator << " ";
    }
}

void moveDictionaryToVector(Dictionary& dictionary,VectorOfItems& vectorOfItems)
{
    Dictionary::iterator mapIterator = find_if(dictionary.begin(), dictionary.end(), cheaperThan(100.0f));
    Dictionary::iterator dictionaryEnd = dictionary.end();
    for (; mapIterator != dictionaryEnd; mapIterator = find_if(++mapIterator, dictionaryEnd, cheaperThan(100.0f)))
    {
        //cout << mapIterator->second << endl;
        vectorOfItems.push_back(mapIterator->second);
    }
}

void outputVector(VectorOfItems& items)
{
    cout << "Here's the vector:" << endl;
    unsigned long n = items.size();
    //cout << "size computed";
    for (int i = 0; i < n; i++)
    {
        cout << items[i];
    }
}

int countFreeItems(VectorOfItems& items)
{
    unsigned long n = items.size();
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        if (items[i].getPrice() == 0.0f)
        {
            result++;
        }
    }
    return result;
}

bool exactly100(Item& item)
{
    return item.getPrice() == 100.0f;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//Main:
int main(int argc, const char * argv[])
{
    Dictionary dictionary;
    //1.
    //inputDictionary(dictionary);
    testInput(dictionary);
    //2.By default sorted by keys:
    //3.
    outputDictionary(dictionary,false);
    //4.
    Dictionary::iterator it = find_if(dictionary.begin(), dictionary.end(), cheaperThan(20.0f));
    if (it != dictionary.end()) cout << "The first item which is cheaper than 20$ is: " << it->first << " " << it->second << endl;
    else cout << "No items found cheaper than 20$." << endl;
    //5.
    ListOfItems listOfItems;
    moveDictionaryToListWithCondition(dictionary,listOfItems);
    //6.
    outputListOfItems(listOfItems);
    //7.
    listOfItems.sort(lessForItems);
    //8.
    outputDictionary(dictionary,true);
    outputListOfItems(listOfItems);
    //9.
    VectorOfItems itemsFromDictionary;
    moveDictionaryToVector(dictionary,itemsFromDictionary);
    
    VectorOfItems items(2*itemsFromDictionary.size());
    merge(itemsFromDictionary.begin(), itemsFromDictionary.end(), listOfItems.begin(), listOfItems.end(), items.begin());
    //10.
    outputVector(items);
    //11.
    cout << "We have " << countFreeItems(items) << " free items." << endl;
    //12.
    VectorOfItems::iterator vectorIterator = find_if(items.begin(), items.end(), exactly100);
    if (vectorIterator != items.end()) cout << "Item found" << endl;
    else cout << "Item not found." << endl;
    
    
    return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
//End of file.
using System;
using System.Collections.Generic;

namespace Lab3APPOO
{
	class Item
	{
		double price;
		int code;
		public Item(){ price = 0; code = 0;}
    	public Item(double price,int code){this.price = price; this.code = code;}
	
		public double getPrice(){return price;}
    	public int getCode(){return code;}
		public void setPrice(double price){this.price = price;}
		public void setCode(int code){this.code = code;}
	}
	
	class DescendingComparer<T> : IComparer<T> where T : IComparable<T>
	{
	    public int Compare(T x, T y) {
	        return y.CompareTo(x);
	    }
	}
	
	class MainClass
	{
		static void testInput(ref SortedDictionary<string,Item> d)
		{
			string[] keys = new string[5] {"Coca Cola","Bentley","Pizza","Mars","PC"} ;
			Item[] items = new Item[5] { new Item(1.99,111), new Item(1000000,222), new Item(19,112),new Item(1.49,113),new Item(700,333)};
			for (int i=0; i<5; i++)
			{
				d[keys[i]] = items[i];
			}
		}
		static void inputDictionary(ref SortedDictionary<string,Item> dictionary)
		{
		    int n;
		    Console.WriteLine ("How many elements do you have?");
		    n = Console.Read();
		    
		    Item item = new Item();
		    string name;
		    for (int i=0; i<n; i++)
		    {
		        Console.WriteLine ("Name of item - price - code:");
		        name = Console.ReadLine();
				item.setPrice(Console.Read());
				item.setCode(Console.Read());
		        dictionary[name] = item;
		    }
		}
		static void outputDictionary(ref SortedDictionary<string,Item> d,bool ascending)
		{
			Console.WriteLine("Here's the dictionary:");
			if (ascending)
				foreach(KeyValuePair<string,Item> entry in d)
				{
					Console.WriteLine(entry.Key+" price:{0} code:{1}",entry.Value.getPrice(),entry.Value.getCode());
				}
			else
			{
				Console.WriteLine("buidling reverse order");
				SortedDictionary<string,Item> reverse = new SortedDictionary<string, Item>(new DescendingComparer<string>());
				foreach(KeyValuePair<string,Item> entry in reverse)
				{
					Console.WriteLine(entry.Key+" price:{0} code:{1}",entry.Value.getPrice(),entry.Value.getCode());
				}
			}
		}
		static KeyValuePair<String,Item> getFirstItemCheaperThan(ref SortedDictionary<string,Item> d,double price)
		{
			foreach(KeyValuePair<String,Item> entry in d)
			{
				if (entry.Value.getPrice() < price) return entry;
			}
			return new KeyValuePair<String, Item>();
		}
		static void moveDictionaryToList(ref SortedDictionary<string,Item> d, ref List<Item> l)
		{
			foreach(KeyValuePair<String,Item> entry in d) l.Add(entry.Value);
		}
		static void outputList(ref List<Item> l)
		{
			Console.WriteLine("Here's the list:");
			foreach(Item item in l)
			{
				Console.WriteLine("price:{0} code:{1}",item.getPrice(),item.getCode());
			}
		}
		static void sortedDictionaryAndListToQueue(ref SortedDictionary<string,Item> d, ref List<Item> l, ref Queue<Item> q)
		{
			foreach(KeyValuePair<String,Item> entry in d)
			{
				q.Enqueue(entry.Value);
			}
			foreach(Item item in l)
			{
				q.Enqueue(item);
			}
		}
		static void outputQueue(ref Queue<Item> q)
		{
			Item[] items = q.ToArray();
			int n = q.Count;
			for(int i = 0; i < n; i++)
			{
				Console.Write (" price:{0} code:{1} ",items[i].getPrice(),items[i].getCode());
			}
			Console.WriteLine();
		}
		static Item findItemWithPrice(ref Queue<Item> q, double price)
		{
			Item result = new Item();
			Item[] items = q.ToArray();
			int n = q.Count;
			for(int i = 0; i < n; i++)
			{
				if (items[i].getPrice() == price) return items[i];
				//Console.Write (" price:{0} code:{1} ",items[i].getPrice(),items[i].getCode());
			}
			return result;
			
		}
		public static void Main (string[] args)
		{
			//Item a = new Item(4,3);
			List<Item> listOfItems = new List<Item>();
			SortedDictionary<string,Item> dictionaryOfItems = new SortedDictionary<string, Item>();
			Queue<Item> queue = new Queue<Item>();
			//1. Input dictionary:
			//inputDictionary(ref dictionaryOfItems);
			testInput(ref dictionaryOfItems);
			//2.We are using SortedDictionary:
			//3.Ouput:
			outputDictionary(ref dictionaryOfItems,true);
			//4.Find smth. cheaper than 20:
			KeyValuePair<String,Item> pair = getFirstItemCheaperThan(ref dictionaryOfItems,20);
			if (pair.Key.Length > 0) Console.WriteLine("Item found: "+pair.Key+" price:{0} code:{1}",pair.Value.getPrice(),pair.Value.getCode());
			else Console.WriteLine("Item not found.");
			//5. Move dict. to list:
			foreach(KeyValuePair<String,Item> entry in dictionaryOfItems) listOfItems.Add(entry.Value);
			//6. Output the list:
			outputList (ref listOfItems);
			//7. Sort list using lambda expression:
			listOfItems.Sort((a,b)=>a.getPrice().CompareTo(b.getPrice()));
			//8. 0utput:
			outputList (ref listOfItems);
//!!! Error here...
			outputDictionary(ref dictionaryOfItems,false);
			//9. Merge everything in a 3rd container:
			sortedDictionaryAndListToQueue(ref dictionaryOfItems, ref listOfItems, ref queue);
			//10.Output queue:
			outputQueue(ref queue);
			//11. Count elements:
			Console.WriteLine("We have {0} items in queue.",queue.Count);
			//12. Find smth.:
			Item res = findItemWithPrice(ref queue,700.0);
			if (res.getCode() == 0) Console.WriteLine("No item found.");
			else Console.WriteLine("Item with code: {0}, price:{1}",res.getCode(),res.getPrice());
			
			//Console.Write("{0},{1}",34, 2);
			//Console.WriteLine ("Hello World!");
		}
	}
}

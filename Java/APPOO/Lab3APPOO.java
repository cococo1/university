import java.util.*;
import java.util.Map.Entry;
//import java.util.map;


public class Lab3APPOO {

	static void inputDictiona(TreeMap<String, Item> d)
	{
	    int n;
	    Scanner in = new Scanner(System.in);
	    System.out.println ("How many elements do you have?");
	    n = in.nextInt();
	    
	    Item item = new Item();
	    String name;
//	    int i = in.nextInt();
//	    String s = in.next();
	    for (int i=0; i<n; i++)
	    {
	    	System.out.println ("Name of item - price - code:");
	        name = in.next();
			item.setPrice(in.nextDouble());
			item.setCode(in.nextInt());
	        d.put(name, item);
	    }
	}
	static void testInput(TreeMap<String, Item> d)
	{
		String keys[] = {"Coca Cola","Bentley","Pizza","Mars","PC"};
		Item items[] ={ new Item(1.99,111), new Item(1000000,222), new Item(19,112),new Item(1.49,113),new Item(700,333)};
		for (int i=0; i<5; i++)
		{
			d.put(keys[i],items[i]);
		}
	}
	static void outputDictionary(TreeMap<String, Item> d, boolean ascending)
	{
		System.out.println("Here's the dictionary:");
		if (ascending)
			for(Map.Entry<String,Item> entry : d.entrySet())
			{
				System.out.printf("%s price:%f code:%d \n",entry.getKey(),entry.getValue().getPrice(),entry.getValue().getCode());
			}
		else
		{
			
			LinkedList<Map.Entry<String, Item>> list = new LinkedList<Map.Entry<String, Item>>();
			list.addAll(d.entrySet());
			for(int i = list.size()-1; i >= 0; i--)
			{
				System.out.printf("%s price:%f code:%d \n",list.get(i).getKey(),list.get(i).getValue().getPrice(),list.get(i).getValue().getCode());
			}
		}
	}
	static Map.Entry<String,Item> getFirstItemCheaperThan(TreeMap<String, Item> d, double price)
	{
		for(Map.Entry<String,Item> entry : d.entrySet())
		{
			if (entry.getValue().getPrice() < price) return entry;
		}
		return null;
	}
	static void outputLinkedList(LinkedList<Item> l)
	{
		System.out.println("Here's the list:");
		for(Item item : l)
		{
			System.out.printf("Price: %f, Code: %d ", item.getPrice(),item.getCode());
		}
	}
	static void outputVector(ArrayList<Item> v)
	{
		System.out.println("The vector is:");
		for (Item item : v)
		{
			System.out.printf("Price: %f, Code: %d ", item.getPrice(),item.getCode());
		}
	}
	static Item findItemWithPrice(ArrayList<Item> v,double price)
	{
		for (Item item : v)
		{
			if (item.getPrice() == price) return item;
		}
		return new Item();
	}
	
	public static void main(String[] args) {
		TreeMap <String,Item> dictionary = new TreeMap<String, Item>();
		LinkedList<Item> list = new LinkedList<Item>();
		ArrayList<Item> vector = new ArrayList<Item>();
		//1. Input dictionary:
		//inputDictionary(dictionary);
		testInput(dictionary);
		//2. Sort dictionary reverse order (tree map is already sorted):
		//3.Ouput:
		outputDictionary(dictionary,false);
		//4.Find smth. cheaper than 20:
		Map.Entry<String, Item> pair = getFirstItemCheaperThan(dictionary,20);
		if (pair != null) System.out.printf("Item found: %s price: %f code: %d ",pair.getKey(),pair.getValue().getPrice(),pair.getValue().getCode());
		else System.out.println("Item not found.");
		//5. Move dict. to list:
		list.addAll(dictionary.values());
		//6. Output the list:
		outputLinkedList(list);
		//7. Sort list:
		Collections.sort(list, new MyItemComparable());
		//8. Output sorted list and dictionary:
		outputLinkedList(list);
		//Because dictionary is already sorted, 
		outputDictionary(dictionary,true);
		//9. Merge everything in a 3rd container:
		vector.addAll(list);
		vector.addAll(dictionary.values());
		//10.Output vector:
		outputVector(vector);
		//11. Count elements:
		System.out.printf(" \nThere are %d elements in the vector \n",vector.size());
		//12. Find smth.:
		Item res = findItemWithPrice(vector,700);
		if (res.getCode() == 0) System.out.println("Item not found.");
		else System.out.printf("Item found: price: %f , code: %d \n",res.getPrice(),res.getCode());
		//System.out.println("Hello world!");
	}

}

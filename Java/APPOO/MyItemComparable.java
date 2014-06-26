import java.util.Comparator;
 
public class MyItemComparable implements Comparator<Item>{
    public int compare(Item a, Item b) {
    	if (a.getPrice() > b.getPrice()) return 1;
    	else if (a.getPrice() == b.getPrice()) return 0;
    	else return -1;
    }
}

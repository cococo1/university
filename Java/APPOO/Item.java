public class Item {
		double price;
		int code;
		public Item(){ price = 0; code = 0;}
    	public Item(double price,int code){this.price = price; this.code = code;}
	
		public double getPrice(){return price;}
    	public int getCode(){return code;}
		public void setPrice(double price){this.price = price;}
		public void setCode(int code){this.code = code;}

}

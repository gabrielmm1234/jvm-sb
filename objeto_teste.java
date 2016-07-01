class objeto_teste{
	private int a;
	private double c;
	
	public objeto_teste(int a, double c){
		this.a = a;
		this.c = c;
	}
	
	public void set_a(int a){
		this.a = a;
	}
	public void set_c(double c){
		this.c = c;
	}
	public int get_a(){
		return a;
	}
	public double get_c(){
		return c;
	}

		
	public static void main(String argv[]){
		objeto_teste obj1, obj2;
		obj1 = new objeto_teste(3,5.0);
		obj2 = new objeto_teste(-300, -51.54);
		
		System.out.println(obj1.get_a());
		System.out.println(obj1.get_c());
		System.out.println(obj2.get_a());
		System.out.println(obj2.get_c());
		
		obj1.set_a(42);
		obj1.set_c(42.0);
		System.out.println(obj1.get_a());
		System.out.println(obj1.get_c());
	}
}

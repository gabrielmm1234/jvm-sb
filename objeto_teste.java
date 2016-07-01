class objeto{
	private int a;
	private double c;
	
	public objeto(int a, double c){
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
		objeto obj1, obj2;
		obj1 = new objeto(3,5.0);
		obj2 = new objeto(-30000, -51.54);
		
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
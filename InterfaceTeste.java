public class InterfaceTeste implements MinhaPrimeiraInterface {

	@Override
	public void metodo1() {
		// TODO Auto-generated method stub
		System.out.println("Entrei no metodo1");
	}

	@Override
	public void metodo2() {
		// TODO Auto-generated method stub
		System.out.println("Entrei no metodo2");
	}

	@Override
	public void metodo3() {
		// TODO Auto-generated method stub
		System.out.println("Entrei no metodo3");
	}

	public static void main(String[] args) {
		InterfaceTeste fib = new InterfaceTeste();

		fib.metodo3();
		fib.metodo2();
		fib.metodo1();

	}

}
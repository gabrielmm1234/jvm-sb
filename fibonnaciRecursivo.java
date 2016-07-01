public class FibonacciRecursivo {
 
    int fibo(int n) {
        if (n < 2) {
            return n;
        } else {
            return fibo(n - 1) + fibo(n - 2);
        }
    }
 
    public static void main(String[] args) {   
	
	// teste do programa. Imprime os 30 primeiros termos       
	for (int i = 0; i < 30; i++) {
            System.out.println(Fibonacci.fibo(i));
        }
 
    }
 
}
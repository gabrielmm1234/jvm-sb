import java.util.*;  

public class Delta {  
  
    Scanner read = new Scanner(System.in);  
  
    int a, b, c;  
    float delta, x1, x2;  
  
    public Delta() {  
        deltaCalculo();  
    }  
  
    private void deltaCalculo() {  
  
        System.out.println("Digite o valor de A, B e C respectivamente: ");
        a = Integer.parseInt(read.next());  
        b = Integer.parseInt(read.next());  
        c = Integer.parseInt(read.next());  
  
        delta = (b * b) + (-4 * (a * c));  
  
        System.out.println("Delta: " + delta);  
  
        if (delta >= 0) {  
            calculaX();  
        } else {  
            System.out.println("Delta não possui raiz!");
            System.exit(0);  
        }  
  
    }  
  
    private void calculaX() {  
  
        x1 = (float) ((-(b) + Math.sqrt(delta)) / 2 * a);  
        x2 = (float) ((-(b) - Math.sqrt(delta)) / 2 * a);  
  
        System.out.println("x1 = " + x1);  
        System.out.println("x2 = " + x2);  
  
    }  
  
    public static void main(String[] args) {  
        new Delta();  
    }  
  
}  

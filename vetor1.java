/*
 Saida esperada:
100000
1
2
3
4
5
6
7
8
9
2.000000
3.000000
-5.000000
-5
3
6426246
-433242
2.000000
3.000000
-5.000000
-2
4
0
a
0
)
15
1000
-2
 */
class vetor1{
	public int a;
	public static void main(String argv[]){
		int array[] = new int[10];
		float array4[] = {2.0f,3.0f,-5.0f};
		byte array5[] = {-2, 4, 0};
		short array7[] = {15, 1000, -2};
		char array6[] = {'a', '0', ')'};
		double array2[] = {2.0,3.0,-5.0};
		long array3[] = {-5, 3, 6426246, -433242};

		vetor1 vet = new vetor1();
		vet.a = 20;

		vetor1 arrayObjeto[] = new vetor1[10];
		arrayObjeto[0] = vet;
		System.out.println(arrayObjeto[0].a);

		System.out.println(array.length);
		System.out.println(array4.length);
		System.out.println(array5.length);
		System.out.println(array7.length);
		System.out.println(array6.length);
		for (int i = 0; i < 10; i++){
			array[i] = i;
            System.out.println(array[i]);
		}

		for (int i = 0; i < 3; i++){
			System.out.println(array4[i]);
		}
		System.out.println();

		for (int i = 0; i < 3; i++){
			System.out.println(array5[i]);
		}
		System.out.println();

		for (int i = 0; i < 3; i++){
			System.out.println(array6[i]);
		}
		System.out.println();

		for (int i = 0; i < 3; i++){
			System.out.println(array7[i]);
		}
		System.out.println();

		for (int i = 0; i < 3; i++){
			System.out.println(array2[i]);
		}
		System.out.println();

		
		for (int i = 0; i < 4; i++){
			System.out.println(array3[i]);
		}
		System.out.println();
	}
}
	

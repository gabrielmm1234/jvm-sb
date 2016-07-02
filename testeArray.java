class testeArray{
	static public void printint(int[] val){
		int i;	
		for(i=0;i<5; i++){
			System.out.println(val[i]);
		}
	}

	public static void main(String[] args){
		int[] vetint;
		vetint = new int[5];
		vetint[0] = 10;
		int i;
		for(i=0; i<5; i++){
			vetint[i] = 10;
		}

		testeArray.printint(vetint);

		int array[] = new int[10];
		for (i = 0; i < 10; i++){
			array[i] = i;
		}
		array[0] += 100000;
		for (i = 0; i < 10; i++){
			System.out.println(array[i]);
		}
		System.out.println();


	}
}
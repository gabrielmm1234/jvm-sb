public class Switch {

   public static void main(String args[]){

      //char grade = args[0].charAt(0);
      int i = 0;

      switch(i)
      {
         case 0 :
            System.out.println("Excellent!"); 
            break;
         case 1 :
         case 2 :
            System.out.println("Well done");
            break;
         case 3 :
            System.out.println("You passed");
            break;
         case 4 :
            System.out.println("Better try again");
            break;
         default :
            System.out.println("Invalid grade");
      }
   }
}


public class mainforstack{


	public static void main(String args[]){
	
   	    int i=1;
	    Stack mystack = new Stack(10); //stack of size
	     mystack.peek();

	     while(!mystack.isFull()){
	     System.out.println("Pushing : "+i);
	     	mystack.push(i);
		i++;
		}

	     int mynum;

	     while(!mystack.isEmpty()){
	     mystack.peek();
	     mynum = mystack.pop();
	     System.out.println("Mynum is: "+mynum);
	     }



	}

}

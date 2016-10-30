public class Stack{

	int size;
	int array[];
	int top=-1; //starting in basically null position since empty

	public Stack(int size){
	  this.size = size;	
	  array = new int[size];
	}

	public int pop(){
//	 if(top < 0) System.out.println("Stack is empty");
//	 else { //pretending like an element got removed even though its still there, by moving top
		top--;
		return array[top+1];
//	    }
//	  return 0;
	}

	public void push(int num){
		//if(top == size-1) System.out.println("Stack is full"); 

//		else{
		  top++;
		  array[top]=num;
//		}

	}
	
	public void peek(){
	if(top < 0) System.out.println("Stack is empty");
	else System.out.println("Item at top is: "+array[top]);
	 }
	
	public boolean isEmpty(){
	if (top <0) return true;
	else return false;
	}
	
	public boolean isFull(){
	if(top==size-1)return true;
	else return false;
	}
}

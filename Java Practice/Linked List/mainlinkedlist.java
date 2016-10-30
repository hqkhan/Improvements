import java.util.Random;
public class mainlinkedlist{

	public static void main(String []args){
		LinkedList mylist = new LinkedList(); //created new list
		int randy,counter=0;
		
		while(counter<20){
			Random randnum = new Random();
			randy = randnum.nextInt(100);
			Link newnode = new Link(randy); //insert value i in node
			mylist.insert(newnode); //insert last should be in order
			counter++;
		}
			
		mylist.displayList();	
	
	
	}


}

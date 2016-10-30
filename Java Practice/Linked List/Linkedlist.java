public class LinkedList{
	
	Link first; //each list has first node to start off
	
	public LinkedList(){ //constructor
		first = null; //setting to null, inserting will change this
	}
	
	boolean isEmpty(){ //check if list is empty
		if(first == null) return true;
		return false;
	        }

	public void insertBegin(Link newnode){ //insertion in the beginning
		if (first == null) first = newnode; //the first node to insert
		else{
		    newnode.next = first; //point to the previous first
		    first = newnode; //updated new first 
	        }
	}


	public void insertLast(Link newnode){
		if(first == null) first = newnode; //insert this at last is the same as inserting first
		else{
		   Link current = first;
		   while(current.next != null) current = current.next; //move to the last node
		   //can insert now
		   current.next = newnode; //inserting
		   newnode.next = null; 
		
		}
	}

	
	public void displayList(){
		Link current = first; //starting probe from beginning
		System.out.println("Starting to display");
		
		while (current != null){ //until last element
			System.out.println("Value of node is="+current.num);
			current = current.next; //move forward
		}
		
		System.out.println("Finished to display");
	}
	


}

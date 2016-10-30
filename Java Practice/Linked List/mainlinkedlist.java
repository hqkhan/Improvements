public class mainlinkedlist{

	public static void main(String []args){
		LinkedList mylist = new LinkedList(); //created new list
		
		for(int i=0;i<10;i++){
			Link newnode = new Link(i); //insert value i in node
			mylist.insertBegin(newnode); //insert last should be in order
		}
			
		mylist.displayList();	
	
	
	}


}

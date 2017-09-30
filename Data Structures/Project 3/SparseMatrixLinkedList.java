import java.util.Random;

public class SparseMatrixLinkedList implements Matrix
{
private RowNode top;
private int size=0; // size matrix
private int nnz=0; // number of non-zero elements
//////////////////////
// constructors
//////////////////////
// Basic constructor- no element in the list yet
SparseMatrixLinkedList(){top=null;}

// Constructor with Random generator (using nnz random non-zero numbers between 0.01<= x < 1.01
// on any random row,column coordinates)
SparseMatrixLinkedList(int sizeMatrix, int nonZero){ //using dynamic fill-in
///=====> TO COMPLETE <===========///
		
		//random to assign values in random row/col
		Random rand1 = new Random(); 
		double num;
		
		size = sizeMatrix;
		nnz = nonZero;
		
		Random rand = new Random();
		RowNode row = null;
		
		int counter = 0;
		
		ColNode column;
		row = new RowNode(0);
		while( counter < nonZero){
		for (int i = 0; i < size; i++){
			if(counter == nonZero)break;//manage number of nonzero numbers
			
			if( i == 0){
				top = row;
			}
			
			for(int j = 0; j < size; j++){
				
				//With a 50% of probability a random number will be assigned to the cell
				if(rand1.nextDouble()< 0.5){
					
					num = rand.nextDouble() + 0.01;  //increasing range of random generated numbers by 0.01
					column =new ColNode(j,num);
					
					double x = get(i,j);
					if(x == 0){
					set(i,j,num);
					
					counter ++;
					}
				}
			}
			
		}
		}
}
// Constructor from any matrix storage using the interface to SparseMatrixLinkedList storage
// (using dynamic fill-in)

//SparseMatrixLinkedList(int sizeMatrix, int nonZero){ //using dynamic fill-in
//	//random to assign values in random row/col
//	Random rand1 = new Random(); 
//
//	int counter = 0;
//	size = sizeMatrix;
//	nnz = nonZero;
//	top = new RowNode(0);
//	while (counter < nonZero){
//		
//		double num = rand1.nextDouble()+0.01; 
//		int randi = rand1.nextInt(size);
//		int randj = rand1.nextInt(size);
//		double x = get(randi,randj);
//		if(x == 0){
//			set(randi, randj, num);
//			counter++;
//		}
//		
//		
//		
//	}
//}

SparseMatrixLinkedList(Matrix A){
///=====> TO COMPLETE <===========///
			double num;
			
			size = A.getSize();
			nnz = A.getNnz();
			
			ColNode currentColumn = null;
			
			 RowNode row = new RowNode(0);
			
			for (int i = 0; i < size; i++){
				
				if(i==0){
					row.col = currentColumn;
					top = row;
				}
				for(int j = 0; j < size; j++){
					
						num = A.get(i, j);  
						
						if (num != 0.0){ 
							set(i, j, num);
							}
				}
				
				//create next row if there is not any, checking that it is still inside the bounds
				if ( row.next == null && (row.rowindex < size-1)){		
					//(rowBef < size-1)i.e if size is 3 then the last case rowBef is 1 which means that the current(going back to the loop) is now in row 2 (the last row)

					//create new node
					RowNode node = new RowNode(row.rowindex+1);
					row.next = node;// now the row is going to point to node and next current is not going to be null
				}
				row = row.next;
			}
		}

//////////////////////
// Methods
//////////////////////



// get the size of the matrix
public int getSize(){return size;}
// get the number of non-zero elements
public int getNnz(){return nnz;}


// Assign the value x to element i,j- change size matrix and nnz dynamically
public void set(int i, int j, double x){
///=====> TO COMPLETE <===========///
	//you have to dynamically insert into	a sorted ColNode list and sorted RowNode list.
	//top should be created
	
	boolean unassigned = true; 
	
	//Checking only case where a element cannot be set inside the matrix
	if(i>=size || j >= size){
		//need to extend matrix
		if( i > j){
			size = i+1;
		}
		else{//j > = i
			size = j +1;//size is the number of elements; j is the index
		}
		nnz ++; //the matrix was expanded so we can fit the element we want to add. So now the  nnz number is going to increased. We do not increase each time that we set because we assume the number of nnz elements was already given. 
		
	}
	
	//create a column 
	ColNode column = new ColNode(j,x);
	
	//we know the row where the element needs to be linked but need to check where to link it between the columns
	
	//finding row
	RowNode current;
	//top is something
	current = top;//top now 
	
	while(unassigned && current != null){ //current != null--> there is the case when the sparseMatrix is not initialized and we need to create the row
		
		if(current.rowindex == i )
		{
			//find column
			//current.col = top.col;
			ColNode currentCol = current.col; //current.col 
			if( current.col == null){// nothing is inside this row
				current.col = column;
				break;
			}
			
			while(currentCol != null){
				
				if(currentCol.colindex == j){ //we want to replace the exact coordinates
					column.next = currentCol.next;
					current.col = column;
					unassigned = false;
					break;
				}
				else if(currentCol.colindex > j){// when the first element has a greater column index than the one we want to insert
					//column is the object we want to insert
					 column.next = currentCol;
					 current.col = column;
					 
					 
					 unassigned = false;
						break;
				 }
				else if (currentCol.next == null && currentCol.colindex < j ){ //we are at the end of the row and want to insert the next one
						 currentCol.next = column;
						 unassigned = false;
							break;
				}
				else if(currentCol.colindex < j && currentCol.next.colindex > j){
						column.next = currentCol.next ;
						currentCol.next = column;
						unassigned = false;
						break;
				}
				currentCol = currentCol.next;
			}
		}
		
		
		//create next row if there is not any, checking that it is still inside the bounds
		if ( current.next == null && (current.rowindex < size-1)){		
			//(rowBef < size-1)i.e if size is 3 then the last case rowBef is 1 which means that the current(going back to the loop) is now in row 2 (the last row)

			//create new node
			RowNode node = new RowNode(current.rowindex+1);
			current.next = node;// now the row is going to point to node and next current is not going to be null
		}
			
		
		current = current.next;
	}
}


// Get the value of element i,j
public double get(int i, int j){
///=====> TO COMPLETE <===========///
	
	//this method returns the value corresponding to the location i,j but if it is not found, then the method returns 0
	
	RowNode currentNode = top;
	ColNode currentCol;
	while(currentNode != null){
		
		if (currentNode.rowindex == i){
			currentCol = currentNode.col;
			while(currentCol != null){
				
				if(currentCol.colindex == j){
					//found it
					return currentCol.entry;	
				}
				currentCol = currentCol.next;
			}	
		}
		currentNode = currentNode.next;
		
	}
	
	return 0;
}

public void display(){
	RowNode current = top; //start probe at the beginning
	System.out.println();
	System.out.println("Display in linked-list format");
	System.out.println("i");
	while (current!=null) { // until the end of the list
		System.out.print(current.rowindex+" ");
		ColNode jcurrent = current.col;
		while (jcurrent!=null) { // until the end of the list
			
			int var = jcurrent.colindex;
			double var2 = jcurrent.entry;
			Object[] array = {new Integer(var),new Double(var2)};
			System.out.format("==> (j=%d, a=%.4f)",array);
			jcurrent = jcurrent.next;
}
System.out.println();
current = current.next; // move to next Link
}
	System.out.println();
}


// NEW DISPLAY TO CHECK
public void display2(){
	RowNode current = top; //start probe at the beginning
//	System.out.println();
//	System.out.println("Display in linked-list format");
//	System.out.println("i");
	while (current!=null) { // until the end of the list
//		System.out.print(current.rowindex+" ");
		ColNode jcurrent = current.col;
		while (jcurrent!=null) { // until the end of the list
			
			int var = jcurrent.colindex;
			double var2 = jcurrent.entry;
			Object[] array = {new Integer(var),new Double(var2)};
//			System.out.format("==> (j=%d, a=%.4f)",array);
			jcurrent = jcurrent.next;
}
//System.out.println();
current = current.next; // move to next Link
}
//	System.out.println();
}
// get the elements of the diagonal
public double[] getDiagonal(){
///=====> TO COMPLETE <===========///
	double[] array = new double[size];
	RowNode current = top;
	while (current!=null) { // until the end of the list
		
		ColNode jcurrent = current.col;
		while (jcurrent!=null) { // until the end of the list
			
			if( current.rowindex == jcurrent.colindex){//we have found the element in the diagonal 
				
				array[current.rowindex]= jcurrent.entry;//assign the entry value which corresponds to the diagonal to the array that we are going to return
				break;// we can break as soon we found a element of the diagonal in one row because there are no more elements that correspond to the diagonal in that row
			}
			jcurrent = jcurrent.next;
		}
		
		current = current.next;
	
	}
	return array;
}
// Multiply a matrix by a vector (multiply using only the non-zero elements)
public Vector multiply(Vector B){
///=====> TO COMPLETE <===========///
	//The multiply routine should be optimal involving only non-zero elements in the multiplication.
	Vector vector = new Vector(size);
	double num = 0.0;
	RowNode currentRow = top;
	while(currentRow != null){
		
		ColNode jcurrent = currentRow.col;
		while (jcurrent!=null) {
			
			num += jcurrent.entry*B.get(jcurrent.colindex);//if get(i,j) is not found then it returns 0
			jcurrent = jcurrent.next;
		}
	vector.set(currentRow.rowindex, num);
	num = 0.0;
	currentRow = currentRow.next;
	}
	return vector;
}
}
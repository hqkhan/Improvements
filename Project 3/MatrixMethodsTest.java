import java.util.Random;
public class MatrixMethodsTest {
	
	    public static void main(String args[])
	    {
	    	
	    int[] array1= {20,100,1000,10000};
	    
	    for(int i =0; i < array1.length;i++){
	    	long startTime, endTime;
	    	
	    	int n = array1[i];
			Matrix A1=new DenseMatrix(n,n*n);
			int size = A1.getSize();
			int j = size-1;

			// Define a vector
			Random rand = new Random();
			Vector b=new Vector(A1.getSize(),rand);
		       
			Vector f;
			// multiplication
			startTime = System.currentTimeMillis(); // capture time
			
			f=A1.multiply(b); // F=A*B
			A1.set(j,j,1);//inserting 1 in the worst case
			A1.get(j,j);
			A1.getDiagonal();
			A1.display2(); //display2() is the same display() method but it is not printing anything 
			
			endTime = System.currentTimeMillis(); // capture time
			System.out.println("All methods in dense matrix of size ("+A1.getSize()+") are done in "+(endTime-startTime)+"ms");
		     

			
		    }
	    	
	    
	    for(int i =0; i < array1.length;i++){	 
	    	
	    	long startTime, endTime;
	    	
	    	int n = array1[i];
			Matrix A2=new SparseMatrixLinkedList(n,n*n);	

			int size = A2.getSize();
			int j = size-1;

			// Define a vector
			Random rand = new Random();
			Vector b=new Vector(A2.getSize(),rand);
		       
			
			// multiplication
			startTime = System.currentTimeMillis(); // capture time
			Vector f=A2.multiply(b); // F=A*B
			A2.set(j,j,1);//inserting 1 in the worst case
			A2.get(j,j);
			A2.getDiagonal();
			A2.display2(); //display2() is the same display() method but it is not printing anything
			
			
			endTime = System.currentTimeMillis(); // capture time
			System.out.println("All methods in sparse matrix of size ("+A2.getSize()+") are done in "+(endTime-startTime)+"ms");
	    	
			
	   
	    }
	    
	    System.out.println("program is done");
	    }
	}





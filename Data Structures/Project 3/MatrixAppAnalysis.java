	import java.util.Random;
import java.util.Random;
public class MatrixAppAnalysis {

	
	    public static void main(String args[])
	    {
	    	
	    int[] array1= {20,100,1000,10000};
	    int[] array2= {20,100,1000,10000,20000};
	    
	    for(int i =0; i < array1.length;i++){
	    	long startTime, endTime;
	    	
	    	int n = array1[i];
			Matrix A1=new DenseMatrix(n,20*n);

			// Define a vector
			Random rand = new Random();
			Vector b=new Vector(A1.getSize(),rand);
		       
			Vector f;
			// multiplication
			startTime = System.currentTimeMillis(); // capture time
			f=A1.multiply(b); // F=A*B
			endTime = System.currentTimeMillis(); // capture time
			System.out.println("Matrix-Vector Multiplication using dense matrix of size ("+A1.getSize()+") done in "+(endTime-startTime)+"ms");
		     

			
		    }
	    	
	    
	    for(int i =0; i < array2.length;i++){	    
			long startTime, endTime;
			
			int n = array2[i];
			Matrix A2=new SparseMatrixLinkedList(n,20*n);	
	
			// Define a vector
			Random rand = new Random();
			Vector b=new Vector(n,rand);
		       
			Vector f;
	
			// multiplication
		        startTime = System.currentTimeMillis(); // capture time
			f=A2.multiply(b); // F=A*B
			endTime = System.currentTimeMillis(); // capture time
			System.out.println("Matrix-Vector Multiplication using sparse matrix of size ("+A2.getSize()+") done in "+(endTime-startTime)+"ms");
	    
	    }
	    
	    
	    }
	}



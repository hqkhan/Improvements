
public class DeterCheck {
	
	
		public static void main(String args[])
	    {
		int n=4;    //size

		DenseMatrix A1=new DenseMatrix(n);
	        //Set Elements
//		A1.set(0,0,1.0);
//		A1.set(0,1,1.0);
//		A1.set(0,2,3.0);
//		A1.set(0,3,3.0);
//		A1.set(0,4,5.0);
//		A1.set(1,1,1.0);
//		A1.set(1,2,5.0);
//		A1.set(1,3,2.0);
//		A1.set(1,4,3.0);
//		A1.set(2,2,4.0);
//		A1.set(2,3,2.0);
//		A1.set(2,4,3.0);
//		A1.set(3,2,6.0);
//		A1.set(3,3,1.0);
//		A1.set(3,4,9.0);
//		A1.set(4,2,3.0);
//		A1.set(4,3,1.0);
//		A1.set(4,4,-1.0);
		
		
		A1.set(0,0,2.0);
		A1.set(0,1,1.0);
		A1.set(1,1,1.0);
		A1.set(1,2,-3.0);
		A1.set(2,0,1.0);
		A1.set(2,2,1.0);
		A1.set(0,3,1.0);
		A1.set(3,1,3.0);
		A1.set(3,2,8.0);

		
		System.out.println("Original Matrix");
		System.out.println("Size "+A1.getSize()+" nnz= "+A1.getNnz());
		A1.display();  // display matrix in dense format
		
		
		double determinant = A1.det(A1);
		
		System.out.println("the determinant of the matrix is :"+determinant);
		

//	        Matrix A2=new SparseMatrixLinkedList(A1);
//		
//		A2.display2();  // display matrix in link-list format
//	        A2.set(0,0,1.0); // change one element
//		A2.set(4,4,1.0); // increase dynamically
//
//		System.out.println("Modified Matrix");
//		System.out.println("Size "+A2.getSize()+" nnz= "+A2.getNnz());
//		A2.display2();  // display matrix in link-list format
//
//		Matrix A3=new DenseMatrix(A2);
//		A3.display2();  // display matrix in dense format
//
//		
//		
//		System.out.println("Diagonal elements");
//		double[] diagS=A2.getDiagonal();
//		double[] diagD=A3.getDiagonal();
//		for (int i=0;i<A2.getSize();i++){System.out.println("Diagonal DenseMatrix "+diagD[i]+"  Diagonal SparseMAtrix"+diagS[i]);}
//		System.out.println();
//		
//		 //Define a vector
//	        Vector b=new Vector(A2.getSize());
//		b.set(0,0.0);
//		b.set(1,0.0);
//		b.set(2,1.0);
//		b.set(3,0.0);
//	        System.out.println("Vector b");
//	        b.display2();
//		 //multiplication
//	        Vector fD=A2.multiply(b); // f=A*b
//		Vector fS=A3.multiply(b); // f=A*b
//		
//		System.out.println("Matrix-Vector Multiplication-- here third column of matrix");
//	        for (int i=0;i<fD.getSize();i++){System.out.println(fD.get(i)+" "+fS.get(i));
	        
	        }
	    }
	



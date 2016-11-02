class MatrixApplication1
{
    public static void main(String args[])
    {
	int n=3;    //size
	int nnz=6;  //nnz

	Matrix A1=new DenseMatrix(n);
        //Set Elements
	A1.set(0,0,2.0);
	A1.set(0,1,1.0);
	A1.set(1,1,1.0);
	A1.set(1,2,-3.0);
	A1.set(2,0,1.0);
	A1.set(2,2,1.0);
	

	System.out.println("Matrix A1");
	A1.display();  // display matrix in dense format

	System.out.println("Diagonal elements of A1");
	//// one could do
	// for (int i=0;i<A1.getSize();i++){System.out.println(A1.get(i,i));}
	//// However we will use the following
	double[] diag=A1.getDiagonal();
	for (int i=0;i<A1.getSize();i++){System.out.println(diag[i]);}
	System.out.println();
	// Define a vector
        Vector b=new Vector(n);
	b.set(0,1.0);
	b.set(1,1.0);
	b.set(2,1.0);
        System.out.println("Vector b");
        b.display();
	// multiplication
        Vector f=A1.multiply(b); // f=A*b
	System.out.println("Matrix-Vector Multiplication");
        f.display();
    }
}

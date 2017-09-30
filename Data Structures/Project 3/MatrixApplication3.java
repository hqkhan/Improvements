import java.util.Random;


class MatrixApplication3
{
    public static void main(String args[])
    {
	long startTime, endTime;
	Matrix A1=new DenseMatrix(5000,100000);
	Matrix A2=new SparseMatrixLinkedList(A1);	

	// Define a vector
	Random rand = new Random();
	Vector b=new Vector(A1.getSize(),rand);
       
	Vector f;
	// multiplication
	startTime = System.currentTimeMillis(); // capture time
	f=A1.multiply(b); // F=A*B
	endTime = System.currentTimeMillis(); // capture time
	System.out.println("Matrix-Vector Multiplication using dense matrix done in "+(endTime-startTime)+"ms");
     

	// multiplication
        startTime = System.currentTimeMillis(); // capture time
	f=A2.multiply(b); // F=A*B
	endTime = System.currentTimeMillis(); // capture time
	System.out.println("Matrix-Vector Multiplication using sparse matrix done in "+(endTime-startTime)+"ms");
    }
}

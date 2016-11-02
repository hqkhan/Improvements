import java.util.*;
public class DenseMatrix implements Matrix
{
private int size=0; // size of the matrix- number of rows/columns
private int nnz=0; // number of non-zero elements

//to analyze code
private double[][] data;
// Constructor used to initialize the matrix (all elements to zero)
DenseMatrix(int size){
	this.size=size;
	data=new double[size][size]; // all elements take the values 0.0d
}
// Constructor with Random generator (using nnz random non-zero numbers between 0.01<= x < 1.01
// on any random row,column coordinates)
DenseMatrix(int size,int nnz){
///=====> TO COMPLETE <===========///
	this(size);
	
	Random rand = new Random();
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			
			if(this.nnz >= nnz)break;
			data[i][j] = rand.nextDouble() + 0.01;
			this.nnz++;
			
			
		}
	}
}
	

// Constructor from any other matrix storage using the interface to Dense storage
DenseMatrix(Matrix A){
	this.size=A.getSize();
	this.nnz=A.getNnz();
	data=new double[size][size];
	for (int i = 0; i < size; i++)
		for (int j=0;j<size;j++)
			data[i][j]=A.get(i,j);
}

// get the size of the matrix
public int getSize(){return size;}
// get the number of non-zero elements
public int getNnz(){return nnz;}
// Assign the value x to element i,j
public void set(int i,int j, double x){
	if ((data[i][j]==0)&&(x!=0.0)) nnz++;
	if ((data[i][j]!=0)&&(x==0.0)) nnz--;
	data[i][j]=x;
}
// get the value of the element i,j
public double get(int i, int j){return(data[i][j]);}
// Print matrix using a specific format
public void display(){
	double var = 0;
	System.out.println();
	System.out.println("Display in dense format");
	for (int i = 0; i < size; i++){
		for (int j=0;j<size;j++)
		{		
			var = get(i,j);
			Object[] array = {new Double(var)};

			System.out.format("%.4f ",array);
		}
		System.out.println();
}
System.out.println();
}
// get the elements of the diagonal
public double[] getDiagonal(){
///=====> TO COMPLETE <===========///
	double[] array = new double[size];
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(i==j){
				array[i] = data[i][j]; 
				break;
			}
		}
	}
	return array;
	
}
// Multiply a matrix by a vector
public Vector multiply(Vector B){
///=====> TO COMPLETE <===========///
	Vector vector = new Vector(size);
	double num = 0.0;
	
	for (int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			
			num += data[i][j]*B.get(j);
		}
	vector.set(i, num);
	num = 0.0;
	}
	return vector;
}

//NEW DISPLAY TO CHECK
public void display2(){
	double var = 0;
	System.out.println();
//	System.out.println("Display in dense format");
	for (int i = 0; i < size; i++){
		for (int j=0;j<size;j++)
		{		
			var = get(i,j);
			Object[] array = {new Double(var)};

			//System.out.format("%.4f ",array);
		}
		//System.out.println();
}
//System.out.println();

}

//EXTRA CREDIT

public double det(DenseMatrix A){
	int j=0;
	
	//determinant
	
	double determinant = 0;
	
	//base case
	if ( A.size == 2){
		
		determinant += A.get(0,0)*A.get(1,1)- A.get(0,1)*A.get(1,0);
		return determinant;
	}
	
	
	
//	determinant += det(shrink(data,0,0))*A.get(0, 0)-det(shrink(data,0,1))*A.get(0, 1)+det(shrink(data,0,2))*A.get(0, 2);
	
	while(j < A.size){
	determinant += Math.pow(-1,j)*det(shrink(data,0,j))*A.get(0, j);
	j++;
	}
	
	
	
	
	return determinant;
}
private DenseMatrix shrink(double[][] data2,int I, int J) {
	// TODO Auto-generated method stub
	
	DenseMatrix newMatrix = new DenseMatrix(data2.length-1);
	
	int index1 = 0,index2 = 0 ;//indexes in the shrunk matrix
	
	
	
	for (int i = 0; i < data2.length; i++){
		
		for (int j=0;j<data2.length;j++)
			
		{ 
			if( i == I )break;
			
			
			if(j != J) {
				newMatrix.set(index1, index2, data2[i][j] );
				index2 ++;
			}
			
			
		}
		index2 = 0 ;
		if( i != I )index1 ++;
		}
	
	
	
	return newMatrix;
}

}
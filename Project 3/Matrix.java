		public interface Matrix
		{
		// Assign the value x to element i,j
		void set(int i,int j, double x);// O(1) for Dense;  O(n^2)
		// get the value of the element i,j
		double get(int i, int j);// O(1) for Dense; O(n^2) for  Sparse
		// Extract the diagonal of the matrix
		double[] getDiagonal();//O(n^2) for both
		// get the size of the matrix-- number of rows
		int getSize();  //method is O(1) for both matrixes 
		// get the number of non-zero elements
		int getNnz(); //method is O(1) for both matrixes 
		// Multiply a matrix by a vector
		Vector multiply(Vector B);//O(n^2) for both 
		// Print matrix using a specific format
		void display();//O(n^2) for both
		
		void display2(); 
		}

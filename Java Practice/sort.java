import java.util.Random;
public class sort{

	int array[];
	int size = 0;

	public sort(int size)
	{
		this.size = size;
		array = new int [size];
		int i, num;

		Random rand = new Random();

		for(i=0;i<size;i++)
		{	
			num = rand.nextInt(30);	
			array[i] = num;
		}
			System.out.println("Created array of size "+size);
	}

	public int getLength()
	{
		return size;
	}
	
	

	public void printarray()
	{
		int i;
		for(i=0;i<size;i++) System.out.print(array[i]+" ");
	}
//****************************
// ALL THE SORTING ALGORITHMS
// ***************************

//INSERTION SORT
	public void Insertionsort()
	{
		int key, i, j;

		for(i=1;i<size;i++)
		{
			key = array[i];
			j = i-1;

			while(j >= 0 && array[j]>key)
			{
				array[j+1] = array[j];
				j--;
			}
			array[j+1] = key;
		}
	}			

//SHELLSORT
	public void Shellsort()
	{
		int key, outer, inner, h;
		
		h = 1;
		while(h<=size/3) h=3*h+1; //setting h, 1, 4,...
		while(h>=1) //finish when h=0
		{
			for(outer=h; outer<size; outer++) //moving from h to the end of array to move back to 1/3 of the array for faster sorting
			{
				key = array[outer]; //saving key to check later with h
				inner = outer;
				while(inner>h-1 && array[inner-h]>key)
				{
					array[inner] = array[inner-h]; //replace 
					inner = inner-h;
				}
				
				array[inner] = key; //put key in place
			}
			h = (h-1)/3; //decrement h using inverse formula of setting h above. 
		}
	}


//QUICKSORT WITH IMPROVEMENTS

	public int partition(int left, int right, double pivot)
	{
	return 0;
	}

	public void recQuicksort(int left, int right) //change to if less than 10 items then use insertion sort
	{
		if(right-left<=0) return; //base step
	}	
		

//HEAPSORT
        public void Heapsort()
   	 {
        	int n = array.length;

	 	//Build heap (rearrange array)
	  for (int i = n / 2 - 1; i >= 0; i--)
	  heapify(n, i);
      
          // One by one extract an element from heap
          for (int i=n-1; i>=0; i--)
            {
 	 	// Move current root to end
 		 int temp = array[0];
 	 	 array[0] = array[i];
                 array[i] = temp;
               
            // call heapify on the reduced heap
              heapify(i, 0);
          }
         }

	  public void heapify(int n, int i)
	  {
	      int largest = i;  // Initialize largest as root
	      int l = 2*i + 1;  // left = 2*i + 1
	      int r = 2*i + 2;  // right = 2*i + 2
	 
	      // If left child is larger than root
	      if (l < n && array[l] < array[largest])
	      largest = l;
	      
	      // If right child is larger than largest so far
	      if (r < n && array[r] < array[largest])
	                largest = r;
	                 
	      // If largest is not root
	         if (largest != i)
	      {
	      	int swap = array[i];
	      	array[i] = array[largest];
	              array[largest] = swap;
	                      
	      	// Recursively heapify the affected sub-tree
	      	heapify(n, largest);
	      }
	  }
		


















}

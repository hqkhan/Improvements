public class Heapsort{


	public SortHeap(int array[]){
		int n=array.length; //getting length of array or size of heap
		int temp;

		//heapify the original array, rearrange elements
		for( i=n/2 -1; i>=0;i++)heapify(array,n,i);
		
		//now we can remove elements one by one of the heapified ones
		//we move root to the end everytime to 'sort' it
		for(i=n-1;i>=0;i--){
			temp = array[0];
			array[0] = array[i]; //replaced root with the bottom item
			array[i] = temp; //placed root to the end
	
			//we always have the item that we want at the root, we just take it and put it at the bottom to print it
			heapify(array,i,0);
	
		}
		
		



	}


	public heapify(int array[],int n, int i){
		//n is size of array or heap

		//we assume that root or root of subtree is always largest and then we check
		int largest=i;

		//right and left child
		left=2*i+1; 
		right=2*i+2;

		if(left<n && array[left]>array[largest])
			largest=left;

		if(right<n && array[right]>array[largest])
			largest=right;

		if(largest!=i){ //checking to see if root itself wasnt the largest because we wouldnt have to swap if it was
		   int temp=array[i];
		   array[i] = array[largest];
		   array[largest]=temp;

		   heapify(array,n,largest);
			
		}	
		


	}








}

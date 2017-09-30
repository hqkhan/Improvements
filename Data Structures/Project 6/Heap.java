
public class Heap
{
    
    private Edge[] heapArray; 
    private int N = 0; // current size
    private int MaxSize = 0;
    
    public Heap(int MaxSize)            // constructor - PRIORITY QUE root will always be least 
    {
	// to complete
    	heapArray = new Edge[MaxSize];
    	this.MaxSize = MaxSize;
    	
    }
    
    
    public void insert(Edge item) // insert item in heap (assumed not full)
    {
       // to complete
    	if (N!=MaxSize)
    	{
    		Edge newEdge= item;  
    		heapArray[N] = newEdge;  
    		trickleUp(N++);
    	}
    	else
    	{
    		System.out.println("heap is full");
    	}
    	  
    }
    
   
    public Edge removeMin()
    {
      // to complete
    	Edge root = heapArray[0];  
    	heapArray[0] = heapArray[--N]; //We do not remove the last node, but we change N so the last one cannot be  visible 
    	trickleDown(0);  
    	return root;
    }
    
    private void trickleUp(int i) {
      // to complete
    	// reach top of heap - done   
    	if (i==0) return;  
    	// check if parent is smaller   
    	int parent=(i-1)/2;  

    	if (heapArray[i].weight<heapArray[parent].weight)  
    	{    
    	swap(i,parent); //swap    
    	trickleUp(parent); //recursion    
    	}
    }

    
    private void trickleDown(int i) {
     // to complete
    	int leftchild = 2*i+1;
    	int rightchild = leftchild+1;
  
    	if(leftchild>=N)return;
    	
    	if(rightchild>=N)	//if right is null but we have still something at the left
    	{
    		if(heapArray[i].weight>heapArray[leftchild].weight)
    		{
    			swap(i,leftchild);
    			trickleDown(leftchild); //recursive step
    		}
    		return;
    	}
    	
    	if(heapArray[i].weight>heapArray[leftchild].weight || heapArray[i].weight>heapArray[rightchild].weight)
    	{
    		if(heapArray[leftchild].weight<heapArray[rightchild].weight)
    		{
    			swap(i,leftchild);
    			trickleDown(leftchild); //recursive step
    		}
    		else{
    			swap(i,rightchild(i));
    			trickleDown(rightchild);//recursive step
    		}
    	}
    	
    }
    
    public int rightchild(int i){
    	return i*2+2;
    }

    private void swap(int i,int j){
     // to complete (needed by trickle methods) 
    	Edge temp;
    	temp = heapArray[i];
    	heapArray[i] = heapArray[j];
    	heapArray[j] = temp;
    }
   
    
    // -------------------------------------------------------------
    public int size()              // return number of items
    { return N; }
    // -------------------------------------------------------------
    public boolean isEmpty()      // true if queue is empty
    { return (N==0); }
    // -------------------------------------------------------------

    public void displaytest(){
    	//Checking our matrix  CHECKED WORKING WELL
//    	for(int j = 0;j<heapArray.length;j++)
//    	{
    		for(int k = 0;k<heapArray.length;k++)
    		{
    			if(heapArray[k]!=null)
//    			System.out.print(heapArray[k].weight+"  ");
	    		System.out.print(heapArray[k].start+"  "+heapArray[k].end+"  "+heapArray[k].weight+"  /");

    			else{
    				System.out.println("heaparray is null: "+k);

    				break;
    			}
    				
    				
    		}
    		System.out.println("");

    	
    }


    
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
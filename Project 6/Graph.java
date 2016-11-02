import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;


public class Graph
{
    private Vertex vertexList[]; // list of vertices
    private Edge[] edgesList;
    private int adjMat[][];      // adjacency matrix
    private int Nvertex;          // Number of vertices/nodes
    private int Nedges;           // Number of vertices/nodes
  
    
    // -------------------------------------------------------------   
    public Graph(int maxVertex)               // basic constructor for option 2
    {	  
	vertexList = new Vertex[maxVertex];
	// adjacency matrix initialization
	adjMat = new int[maxVertex][maxVertex];
	Nvertex = 0;
	for(int j=0; j<maxVertex; j++)      // set adjacency
	    for(int k=0; k<maxVertex; k++)   // matrix to 0 by default
		adjMat[j][k] = 0;
    }  // end constructor



    // -------------------------------------------------------------
    public Graph(String name)               // constructor- load Graph
    {
    	
    	//creating array of vertices 
    	vertexList = readVertices(name+".v");  //returns an array of vertices
    	
    	Nvertex = vertexList.length;
//    	System.out.println("Nvertex: "+Nvertex);
    	this.setMatrix(vertexList.length);   //creates an empty graph of size length of array 
    	Edge[] edges = readEdges(name+".e");  //returns an array of edges
    	edgesList = edges;
    
//    	System.out.println("out of readEdges");
    	for(int i=0;i<edges.length;i++){
    		addEdge(edges[i].start, edges[i].end, edges[i].weight);
    	}

    	//Checking our matrix
//    	for(int j = 0;j<vertexList.length;j++)
//    	{
//    		for(int k = 0;k<vertexList.length;k++)
//    		{
//    			System.out.print(adjMat[j][k]+"  ");
//    		}
//			System.out.println("");
//
//    	}
    	
    	
	// to complete 
	
    }// end constructor



   
	// -------------------------------------------------------------
    public Graph(int nx,int ny)               // constructor with random weight grid generator
    {	  
	// to complete
    	if(nx>=ny)vertexList = new Vertex[nx*nx];
    	else vertexList = new Vertex[ny*ny];
    	
//    	Nvertex = vertexList.length; updating this number when inserting vertices

    	// adjacency matrix initialization
    	adjMat = new int[nx*nx][ny*ny];
    	Random rand = new Random();
    	
    	for(int i=0;i<nx*nx;i++)
    	{
    		int j= i+nx;
			int num = rand.nextInt(nx+ny-1);
			num ++;
			
			if(i%nx < nx-1)
			{
				addEdge(i+1, i, num); //making horizontal connection to the next vertex
				num = rand.nextInt(nx+ny-1);
				num ++;
			}
			if(i<vertexList.length-nx)
			{
				addEdge(j, i, num); //making connection to the vertex above current vertex
			}
    	}
//    		}
    	updateSquareMVertices(vertexList.length);
//    	//Checking our matrix  CHECKED WORKING WELL
//    	for(int j = 0;j<nx;j++)
//    	{
//    		for(int k = 0;k<ny;k++)
//    		{
//    			System.out.print(adjMat[j][k]+"  ");
//    		}
//			System.out.println("");
//
//    	}
//    	
			
    	
	
    }  // end constructor
public void displaytest(){
	//Checking our matrix  CHECKED WORKING WELL
	
	for(int k = 0;k<Nvertex;k++)System.out.print("  "+k);
	System.out.println("");
	for(int j = 0;j<Nvertex;j++)
	{
		System.out.print(j +"  ");
		
		
		for(int k = 0;k<Nvertex;k++)
		{
			
			System.out.print(adjMat[j][k]+"  ");
		}
		System.out.println("");

	}
}
              
    // -------------------------------------------------------------
    
    private Edge[] readEdges(String string) {
		// TODO Auto-generated method stub
    	// Read file line by line; it reads and creates an array of vertices
    	//in this case maxItems will be related to the first line which tells us how many items are in the file/array
    	
    	//count starts in 0 
    	int count=0;
    	
    	int maxItems = 0;
    	Edge[] nodes= null ;
    	
    	try {
    	    File file = new File(string);
    	    Scanner scanner = new Scanner(file);
    	    maxItems = scanner.nextInt();//getting the first line of the file which should be the number of vertices.
    	    nodes =new Edge[maxItems];
    	    scanner.nextLine();//read a blank line after the number//"When you call nextInt, the scanner reads the int, but it does not consume the '\n' character after it; nextLine does that." 
    	    
    	    //need to make another loop in which a vertex is created.
    	    //variables for the five attributes 
    	    int x;
    	    int y;
    	    int weight;
    	    
    		 Edge edge; 
    	    while (scanner.hasNext() && count<maxItems) {
    	    	
    	    		
	    		x =scanner.nextInt();// read entire line into string and go to next line
	    		y = scanner.nextInt();
	    		weight = scanner.nextInt();
	    		
	    	    scanner.nextLine();//read a blank line after the number//"When you call nextInt, the scanner reads the int, but it does not consume the '\n' character after it; nextLine does that." 

	    	

    	    	edge = new Edge(x,y,weight);
    	    	
    			nodes[count]= edge;    //insert a book into the array
    			count ++;
    			
    	    }
    	    scanner.close();
    	} catch (FileNotFoundException e) {
    	    e.printStackTrace();
    	}
    	return nodes;
        }
	


    //		------------------------------------------------------------------------------------------------------
    
    public void updateSquareMVertices(int numberOfvertices) //numberofvertices = number of points in a graph
    {
    	System.out.println("Numberofvertices is: "+numberOfvertices); 

    	int numberV = 0;  //counter
    	
    	int i =0;
    	int numberOfpoints = numberOfvertices;
    	while(numberV < numberOfpoints){ //going until number of vertices or points
//			System.out.println("numberV is: "+numberV); 
    		int j = 0;
    		while(j < Math.sqrt(numberOfpoints)){ 
//    			System.out.println("asadads is: "+Math.sqrt(numberOfpoints)); 
    			addVertex(j,i ); //updating number of vertices in the array of vertex
    			numberV++;//vertex inserted
    			
    			j++;
    		}
    		i++;
    	}
    }
    public void setMatrix(int maxVertex)
    {
	adjMat = new int[maxVertex][maxVertex];
	
	for(int j=0; j<maxVertex; j++)      // set adjacency
	    for(int k=0; k<maxVertex; k++)   // matrix to 0 by default
		adjMat[j][k] = 0;
    }  
    
    public void addVertex(int i, int j)
    {
//    	System.out.println("Nvertex/i/j is: "+ Nvertex+" "+i+" "+j);
    	vertexList[Nvertex++] = new Vertex(i,j);
    }
    // -------------------------------------------------------------
    
    
    public void addEdge(int start, int end, int weight)
    {
	adjMat[start][end] = weight;
	adjMat[end][start] = weight;
	Nedges++;
    }

    public int[][] getAdjMat()
    {
	return(adjMat);
    }

    public Vertex[] getVertexList()
    {
	return(vertexList);
    }

    public int getNvertex() // return number of vertex/nodes
    {
	return(Nvertex);
    }

    public int getNedges() // return number of edges (connected to the number of non-zero elements in matrix)
    {
	return(Nedges);
    }
       

       
    // -------------------------------------------------------------
    public Graph mstw()           // minimum spanning tree
    {
    	Graph mst=new Graph(Nvertex);       // mst returns as a graph
	//initialize the nodes (same numbering than graphs)
	
    	for (int i=0;i<Nvertex;i++) mst.addVertex(vertexList[i].i,vertexList[i].j);

        //initialize Heap for PQ
    	Heap theHeap = new Heap(Nvertex); //large enough to contain all edges
    	int currentVert = 0;
		int numpandasinserted = 0;  //number of edges
		int k = 0;
        /// To complete	(see p679 Textbook for inspiration)
	while(numpandasinserted < Nvertex-1)  //number of edges are E = Nvert -1
	{
		
		vertexList[currentVert].isInTree =true;
    	Edge[] edges =getAdjEdges(currentVert);  //get unvisited edges 
    	
//    	for(int j = 0;j<edges.length;j++) //EDGES WORKING GOOD 
//		{
//			if(edges[j] != null)
//    		System.out.print(edges[j].start+"  "+edges[j].end+"  "+edges[j].weight+"  /");
//		}
    	
    	
    	//Connecting the last node (avoid unconnected node case)
    	for(int i =0; i<edges.length;i++ ) //inserting all adjacent edges into the priority que
    	{
    		if(edges[i] != null)
    		theHeap.insert(edges[i]);
    		
    	}
//    	theHeap.displaytest();
    	numpandasinserted++;
	
    	Edge theEdge= null;
			//removing edge with minimum weight from the heap and then going to that vertex
    	while(true){
    		theEdge= theHeap.removeMin();//the least amount of weight edge returned
    		currentVert = theEdge.end; //UPDATING CURRENTVERT
    		if(!vertexList[currentVert].isInTree)
    		{
    			break;
    		}
    	}
			
		mst.addEdge(theEdge.start, theEdge.end, theEdge.weight); //add to the mst adj matrix for graphing

	}
	

		 return mst;
    }  // end mstw
	
   

		
		
	private Edge[] getAdjEdges(int currentVert)
	{
		// TODO Auto-generated method stub
		
		Edge[] gatico = new Edge[Nvertex];//long enough to hold edges
		//checking adjacent edges then adding them to the PQ
		
		Edge edge = null;
    	
    	for(int i=0;i<Nvertex;i++)
    	{
    		if(vertexList[i].isInTree == true)continue; //ignore it
    		
    		if(adjMat[currentVert][i]!= 0){
    			edge = new Edge(currentVert,i,adjMat[currentVert][i]);
    			gatico[i]=edge;
    		}
    	}
    	
    	return gatico;
	}
			
		



	// -------------------------------------------------------------
    public void plot(double xmin,double xmax,double ymin,double ymax){  //// Plot the Graph using the StdDraw.java library
	StdDraw.setCanvasSize(600,600); // size canvas	
	StdDraw.setXscale(xmin-1, xmax+1);    //  x scale
	StdDraw.setYscale( ymin-1, ymax+1);   //  y scale
	StdDraw.setPenColor(StdDraw.RED);  // change pen color
	// to complete	 
	for(int i = 0; i<vertexList.length;i++)
		{
		StdDraw.filledCircle(vertexList[i].i,vertexList[i].j,0.1);
		}
//	//creating edges
	for(int j = 0;j<adjMat.length;j++)
	{
		for(int k = j;k<adjMat.length;k++)
		{
			if(adjMat[j][k]!=0){
//				System.out.println("j :"+ j+"/ k :"+ k);

				int xo = vertexList[j].i; 
				int yo = vertexList[j].j;
				int xend =vertexList[k].i;
				int yend = vertexList[k].j;
				
//				System.out.println("x0 :"+ vertexList[j].i+"y0 :"+ vertexList[j].j);
//				System.out.println("xend :"+ vertexList[k].i+"yend :"+ vertexList[k].j);
				
				StdDraw.setPenColor(StdDraw.BLUE);
				StdDraw.line(xo,yo,xend,yend); //plotting edges
			}
			
		}
//		System.out.println("");

	}
	
	// for case 5
//	StdDraw.setPenColor(StdDraw.RED);  // change pen color
//	double d = 0.5; //making frame using this distance around all of the nodes
//	StdDraw.line(-d, -d, getXmax()+d, -d); //-->
//	StdDraw.line(getXmax()+d, -d, getXmax()+d, getXmax()+d); //^
//	StdDraw.line(getXmax()+d, getXmax()+d, -d, getXmax()+d); //<-- 
//	StdDraw.line(-d, getXmax()+d, -d, -d); // |
	
// for extra credit
//	for(int m = 0;m<getXmax()+1;m++)
//	{
//	StdDraw.line(-d, -d+m, getXmax()+d, -d+m); //-->
//	StdDraw.line(getXmax()+d, -d, getXmax()+d, getXmax()+d); //^
//	StdDraw.line(getXmax()+d, getXmax()+d, -d, getXmax()+d); //<-- 
//	StdDraw.line(-d, getXmax()+d, -d, -d); // |
//	
//	}
    }
    
    public static Vertex[] readVertices(String fileName) {
    	// Read file line by line; it reads and creates an array of vertices
    	//in this case maxItems will be related to the first line which tells us how many items are in the file/array
    	
    	//count starts in 0 
    	int count=0;
    	
    	int maxItems = 0;
    	Vertex[] nodes= null ;
    	
    	try {
    	    File file = new File(fileName);
    	    Scanner scanner = new Scanner(file);
    	    maxItems = scanner.nextInt();//getting the first line of the file which should be the number of vertices.
    	    nodes =new Vertex[maxItems];
    	    scanner.nextLine();//read a blank line after the number//"When you call nextInt, the scanner reads the int, but it does not consume the '\n' character after it; nextLine does that." 
    	    
    	    //need to make another loop in which a vertex is created.
    	    //variables for the five attributes 
    	    int x;
    	    int y;
    	    
    		 Vertex vertex; 
    	    while (scanner.hasNext() && count<maxItems) {
    	    	
    	    		
	    		x =scanner.nextInt();// read entire line into string and go to next line
	    		y = scanner.nextInt();
	    		
	    	    scanner.nextLine();//read a blank line after the number//"When you call nextInt, the scanner reads the int, but it does not consume the '\n' character after it; nextLine does that." 

	    	

    	    	vertex = new Vertex(x,y);
    	    	
    	    	
    			nodes[count]= vertex;    //insert a book into the array
    			count ++;
    			
    	    }
    	    scanner.close();
    	} catch (FileNotFoundException e) {
    	    e.printStackTrace();
    	}
    	return nodes;
        }



	public double getXmax() { //declared as double but will only be used in case of square matrices therefore will be nice numbers :)
		// TODO Auto-generated method stub
		double max = Math.sqrt(vertexList.length)-1;
		
		
		return max;
	}
	
	
	public void plot2(double xmin,double xmax,double ymin,double ymax)
	{ 
		 //// Plot the Graph using the StdDraw.java library
			StdDraw.setCanvasSize(600,600); // size canvas	
			StdDraw.setXscale(xmin-1, xmax+1);    //  x scale
			StdDraw.setYscale( ymin-1, ymax+1);   //  y scale
			StdDraw.setPenColor(StdDraw.RED);  // change pen color
			
			// for case 5
			StdDraw.setPenColor(StdDraw.RED);  // change pen color
			double d = 0.5; //making frame using this distance around all of the nodes
			StdDraw.line(-d, -d, getXmax()+d, -d); //-->
			StdDraw.line(getXmax()+d, -d, getXmax()+d, getXmax()+d); //^
			StdDraw.line(getXmax()+d, getXmax()+d, -d, getXmax()+d); //<-- 
			StdDraw.line(-d, getXmax()+d, -d, -d); // |
			
//			plot( xmin, xmax, ymin, ymax);
			
			for(int i = 0; i<vertexList.length;i++)
			{
			StdDraw.filledCircle(vertexList[i].i,vertexList[i].j,0.1);
			}
//		//creating edges
		for(int j = 0;j<adjMat.length;j++)
		{
			for(int k = j;k<adjMat.length;k++)
			{
				if(adjMat[j][k]!=0){
//					System.out.println("j :"+ j+"/ k :"+ k);

					int xo = vertexList[j].i; 
					int yo = vertexList[j].j;
					int xend =vertexList[k].i;
					int yend = vertexList[k].j;
					
//					System.out.println("x0 :"+ vertexList[j].i+"y0 :"+ vertexList[j].j);
//					System.out.println("xend :"+ vertexList[k].i+"yend :"+ vertexList[k].j);
					
					StdDraw.setPenColor(StdDraw.BLUE);
					StdDraw.line(xo,yo,xend,yend); //plotting edges
				}
				
			}
			
			
			
			for(int i=0; i<vertexList.length;i++)
			{
				
				
				int x = vertexList[i].i;
				int y = vertexList[i].j;
				
							
				double Ax = x-d;
				double Ay = y+d;
				
				double Bx = x + d;
				double By = y +d;
				
				double Cx = x+d;
				double Cy = y-d;
				
				
				ver
				double nx = Math.sqrt(Nvertex);
				double p= i+nx; //upper positon
				
				if(i%nx < nx-1)
				{
					if(!isEdgeFromTo(i+1, i)){
						StdDraw.setPenColor(StdDraw.RED);
						StdDraw.line(Bx, By, Cx, Cy); // horizontal line to the right
					}
				}
				if(i<vertexList.length-nx)
				{
					if(!isEdgeFromTo(i,(int) p)){
						StdDraw.setPenColor(StdDraw.RED);

						StdDraw.line(Ax, Ay, Bx, By); // horizontal line to the right
					}
					
				}
				
				
				
			}}
	}
	
	public boolean isEdgeFromTo(int i, int j)
	{
		
		for(int k=0; k<vertexList.length;k++)
		{
		if(adjMat[i][k] != 0 && k== j)
		{
			
			return true;
			
		}
		}
		
		return false;
	}
}  // end class Graph





////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

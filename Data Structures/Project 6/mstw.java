import java.io.*;
import java.util.*;


// mstw.java
// demonstrates minimum spanning tree with weighted graphs
// to run this program: C>java MSTWApp
////////////////////////////////////////////////////////////////


class MSTWApp
{
    public static void ToolsMenu() {
	System.out.println("Menu");
	System.out.println("====");
	System.out.println("1- Read Graph from File");
	System.out.println("2- Generate a Graph using a Grid with Random weights");
	System.out.println("3- Compute the Minimum Spanning Tree");
	System.out.println("4- Plot the Maze");
	System.out.println("5- PLOT MAZE WITH WALLS");
	System.out.println("0-Exit");
	System.out.println("");
	System.out.print("Command: ");
    }


    public static void main(String[] args)
    {
	Graph theGraph=null; // original graph
	Graph mst = null;   // MST stored as graph
        EasyIn easy = new EasyIn();
        int N, totalW;
	int mat[][];
	Vertex nodes[];
	
	
	System.out.println("\nWelcome to Maze Generator App");
	System.out.println("===============================\n");

      
	 
	int command = -1;
	while (command != 0) {
	    if (command!=-1) easy.readString(); //just a pause
	    ToolsMenu();         // Print Option Menu
	    command = easy.readInt();
	    switch(command)
		{
		case  1:// Read Graph from File
		    System.out.println("Enter File name: ");
		    theGraph=new Graph(easy.readString());
		    System.out.println("List of edges + weights: ");
		    N=theGraph.getNvertex();
//		    System.out.println("N: "+N);
		    
		    
		    nodes=new Vertex[N];
		    nodes=theGraph.getVertexList();
		    
//		    System.out.println("Number of nodes: "+nodes.length);

		    // Obtain Matrix
		    mat=new int[N][N];
		    mat=theGraph.getAdjMat();
		    

		    for (int i=0;i<N;i++)
			for (int j=0;j<=i;j++) if(mat[i][j]!=0)
				{
				nodes[i].display();
				System.out.print("<-->");
				nodes[j].display();
				System.out.println("  "+mat[i][j]);
			    }
		  
		    break;

		case  2:    //Generate a Graph using a Grid with Random weights
                    System.out.println("Enter Total Grid Size x: ");
		    int nx=easy.readInt();
                    System.out.println("Enter Total Grid Size y: ");
		    int ny=easy.readInt(); 
		    theGraph=new Graph(nx,ny);//Fix
//            theGraph.displaytest();       
		    break;


		
		case  3://   Compute the Minimum Spanning Tree
		    if (theGraph==null){ System.out.println("Graph not defined"); break;}
		    System.out.println("Minimum spanning tree: ");
		    mst=theGraph.mstw();            // minimum spanning tree
               
		 
		    System.out.println("Number of vertices: "+mst.getNvertex());
		    System.out.println("Number of edges: "+mst.getNedges());
		    System.out.println("List of edges + weights: ");
		    
		    mat=new int[mst.getNvertex()][mst.getNvertex()];
		    mat=mst.getAdjMat();
		    int countw =0;
		    nodes=mst.getVertexList();
		    for (int i=0;i<mst.getNvertex();i++)
			for (int j=0;j<=i;j++) 
				if(mat[i][j]!=0)
				{
				nodes[i].display();
				System.out.print("<-->");
				nodes[j].display();
				System.out.println("  "+mat[i][j]);
				countw+=mat[i][j];
			    }
		    	System.out.println("MST total weight: "+ countw);
		    // to complete
		    
		    break;
		    
	        case 4: //Plot the maze
		    if (mst==null){ System.out.println("MST not defined"); break;}

		    // to complete
//		    theGraph.displaytest();
		    double xmin,xmax,ymin,ymax;
		    xmin = 0;
		    ymin = 0;
		    		
		    xmax = mst.getXmax();
		    ymax = mst.getXmax();

		    
		    mst.plot(xmin,xmax,ymin,ymax); 
//		                  
		    break;
		    		   
	        case 5:
	        	if (mst==null){ System.out.println("MST not defined"); break;}
	        	
			    // to complete
//			    theGraph.displaytest();

	        	 xmin = 0;
	 		    ymin = 0;
	 		    		
	 		    xmax = mst.getXmax();
	 		    ymax = mst.getXmax();
	 		    
			    mst.plot2(xmin,xmax,ymin,ymax); 
//			                  
			    break;
		case 0: 
		    break;
		default:
		    System.out.println("Selection Invalid!- Try Again");
		}
	}

	System.out.println("Goodbye!");
    }
}



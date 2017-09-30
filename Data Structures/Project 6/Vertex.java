
class Vertex
{
    public int i,j;       // points coordinate (i,j)
    public boolean isInTree;
    // -------------------------------------------------------------
    public Vertex(int i,int j)   // constructor
    {
	this.i = i;
	this.j=j;
	isInTree = false;
    }
    // -------------------------------------------------------------
    public void display()
    {
	System.out.print("("+i+","+j+")");
    }
}  // end class Vertex


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

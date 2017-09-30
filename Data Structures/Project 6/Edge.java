
public class Edge
{
    public int start;   // index of a vertex starting edge
    public int end;     // index of a vertex ending edge
    public int weight;  // weight from start to end
    // -------------------------------------------------------------
    public Edge(int sv, int dv, int d)  // constructor
    {
	start = sv;
	end = dv;
	weight = d;
    }
    // -------------------------------------------------------------
}  // end class Edge
////////////////////////////////////////////////////////////////
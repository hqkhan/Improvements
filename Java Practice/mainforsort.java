import static java.lang.Math.pow;
public class mainforsort{

	public static void main(String args[])
	{
		long starttime, endtime;	
		long starttime2, endtime2;	

		sort myarray = new sort(10000);
		myarray.printarray();
		System.out.println();

		starttime = System.currentTimeMillis();
		myarray.Shellsort();
		endtime = System.currentTimeMillis();
		System.out.println("Time it took for array to sort using shellsort = "+Math.pow(endtime-starttime,1)+" seconds");
		System.out.println("Time it took for array to sort using shellsort = "+(endtime-starttime)+" miliseconds");
		myarray.printarray();	

		
	//	System.out.println();
	//	sort myarray2 = new sort(100);
	//	//myarray2.printarray();
	//	System.out.println();

	//	starttime2 = System.currentTimeMillis();
	//	myarray2.Heapsort();
	//	endtime2 = System.currentTimeMillis();
	//	System.out.println("Time it took for array to sort using Insertionsort = "+Math.pow(endtime2-starttime2,1)+" seconds");

	//	myarray2.printarray();	

	}
}

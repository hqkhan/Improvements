import java.util.*;
public class Vector
{
private int size=0;
private double[] data;
// Constructor used to initialize the vector
Vector(int size){
	this.size=size;
	data=new double[size]; // all elements take the values 0.0d
}
// Constructor with Random generator
Vector(int size,Random rand){
	this.size=size;
	data=new double[size];
	for (int i = 0; i < size; i++)
		data[i] = rand.nextDouble(); //random number x between 0<= x < 1.0
}
// Assign the value x to element i
public void set(int i, double x){data[i]=x;}
// get the value of the element i
public double get(int i){return(data[i]);}
// get the size of the vector
public int getSize(){return size;}
// Print vector using a specific format
public void display(){
	System.out.println();
	System.out.println("Display vector");
	for (int i = 0; i < size; i++) System.out.println(data[i]);
	System.out.println();
}
public void display2(){display();}
}

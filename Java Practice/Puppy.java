public class Puppy
{
	String name;
	int age;

	public Puppy(int age, String name)
	{
		this.name = name;
		this.age = age;
		System.out.println("Age of dog = "+age);
		System.out.println("Name of dog = "+name);
	}

	public String bark()
	{
		System.out.println("Dog: "+name+" is barking");
	}
}


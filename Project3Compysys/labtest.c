#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

FILE *powerFile;

double k = 8.617/100000;
double Ea = 0.8;

//Global variables
double value;
double Carray[4]; //to store  C0,C1,C2, and C3 from text file 

//Assuming that the diagonal is nnz because sum will have division by 0 otherwise
double Rmatrix[5][5];//To store all the resistances from text file

double K[4][4]; //coefficients for our diff eq
double Tamb; //ambient temperature
double h = 0.005; //our step size

//Temperature of cores
double Tcore[5]; //stores main temperatures

//Assuming that we have 4 cores
int numDiffeq=4; //number of cores
//storing temporary temperatures in between coefficients calculations
double newAr[5];
double Age[5];	

//power array
double power[4];
double time = 0;

double firsttime = 1;
	
	//New stuff
	
	//TEMPERATURE RISES AT THIS RATE
	
	// Calculate (Ti-Tj)/Ri,j with i fixed and j varying
        double sumT(int i)
     {
		double sum=0;
            int j;
    	    for(j=0; j<numDiffeq+1; j++)
		{ 
			if(j==i){j=i+1;} //if diagonal, we ignore because sum will be 0
			sum+=(Tcore[i]-newAr[j])/Rmatrix[i][j]; 
	      	}	
		
		return sum; //return sum	
     } //end of sum function
	

	double f(int core) //core is just to know which core we are evaluating the function of
	{
	//	printf("Power is: %lf\n",power[core]);
	//	printf("sum is: %lf\n",sumT(core));
	//	printf("capac is: %lf\n",Carray[core]);
		return((power[core] - sumT(core))/Carray[core]);
	}

	double beta(int core) //this is used  when calculating age
	{
		double value; //to return 
 	        double alphaTamb=exp(-Ea/(k*Tamb));
		assert(alphaTamb != 0);

  	//	printf("AlphaTamb is %l2.30f ",alphaTamb); 
  	//	printf("Ea is %lf ",Ea); 
  	//	printf("k is %lf ",k); 
  	//	printf("Tamb is %lf ",Tamb); 

  	//	printf("Product is %lf ",(-Ea/(k*Tamb))); 
 		 value = exp(-Ea/(k*Tcore[core]))/alphaTamb;
	
		
		return value;	
			
	}

/*****************************************************************/
/******************RUNGE KUTTA************************************/
/*****************************************************************/	
	double rk(int numDiffeq, double Ar[], double initialValue, double (*f)(int) ){
		assert(numDiffeq>0);
		assert(*f != NULL);
		int i; //counter for our for loops

		//FINAL SOLUTIONS WILL BE IN Ar array BASED ON WHAT THE USER GIVES

		//setting initial values depending upon parameters
		if(firsttime ==1){
			firsttime=0;
			for(i=0; i<numDiffeq+1; i++){
			    Ar[i]=initialValue; //Ar array is where main calculations occur 	
			    newAr[i]=initialValue; //sumT uses this array which will be 0 in the beginning
			}
		}
	
		for (i=0;i<numDiffeq;i++)
		{
			K[0][i] = h*(*f)(i);//i:core ; getting the values of coefficient K0 for each core ASK ABOUT *F
		}
		
		//update temperatures
		newAr[0] = Ar[0] + K[0][0]/2;
		newAr[1] = Ar[1] + K[0][1]/2;
		newAr[2] = Ar[2] + K[0][2]/2;
		newAr[3] = Ar[3] + K[0][3]/2;
		//find K2
		for (i=0;i<numDiffeq;i++)
		{
			//find power of core
			// fscanf(powerFile, "%lf", &pow);//powerFIle defined as global varaible		
			K[1][i] = h*(*f)(i);//getting the values of coefficient K2 for each core
		}
		
		//update temperatures
		newAr[0] = Ar[0] + K[1][0]/2;
		newAr[1] = Ar[1] + K[1][1]/2;
		newAr[2] = Ar[2] + K[1][2]/2;
		newAr[3] = Ar[3] + K[1][3]/2;
		
		
		//find K3
		for (i=0;i<numDiffeq;i++)
		{
			//find power of core
			// fscanf(powerFile, "%lf", &pow);//powerFIle defined as global varaible		
			K[2][i] = h*(*f)(i);//getting the values of coefficient K3 for each core
		}
		
		
		//update temperatures
		newAr[0] = Ar[0] + K[2][0];
		newAr[1] = Ar[1] + K[2][1];
		newAr[2] = Ar[2] + K[2][2];
		newAr[3] = Ar[3] + K[2][3];
		
		//find K4
		for (i=0;i<numDiffeq;i++)
		{
			//find power of core
			// fscanf(powerFile, "%lf", &pow);//powerFIle defined as global varaible		
			K[3][i] = h*(*f)(i);//getting the values of coefficient K4 for each core
		}
		
		//find new temperatures
		Ar[0] = Ar[0] + (K[0][0]+2*K[1][0]+2*K[2][0]+K[3][0])/6;
	        Ar[1] = Ar[1] + (K[0][1]+2*K[1][1]+2*K[2][1]+K[3][1])/6;
		Ar[2] = Ar[2] + (K[0][2]+2*K[1][2]+2*K[2][2]+K[3][2])/6;
		Ar[3] = Ar[3] + (K[0][3]+2*K[1][3]+2*K[2][3]+K[3][3])/6;
	}

/*****************************************************************/
/******************RUNGE KUTTA END********************************/
/*****************************************************************/	


	void FindTempAge(FILE *powFile, FILE *of){

	    int n=0; //# of diff eq
	    int i=0; //current core we are working
	    int count=0;
	    int core;
	    double pow;
		 
	   //pointers to functions 	
	    double (*tempfunct)(int);
            tempfunct= &f;
	    double (*betafunct)(int);
            betafunct= &beta;
		
	    //flag to stop our while loop that is reading powers
	    int flag=1;


		while(flag==1){

			while(n<4){
				if(fscanf(powFile, "%lf", &pow)==EOF){  //going to read 4 times and then quit
					flag=-1;				
					break; 
				}
				power[n]= pow;
				n++;
			}	
			n=0; //n is only to read power file based on number of columns	
			
			rk(numDiffeq,Tcore, Tamb, tempfunct);//sumT uses ambient temp at the beginning 
			rk(numDiffeq, Age, 0, betafunct); //finding Age of every core

			time=time+h;
			fprintf(of,"%lf ",time); //Writing time first entry
			
			for(i=0;i<numDiffeq;i++){
				fprintf(of, "%lf %lf ",Tcore[i],Age[i]);
			}
			fprintf(of, "\n");
			
		}
}


//****************MAIN*************************
int main(int argc,char* argv[])
{
	
    assert(argc >= 4); //making sure argc has greater or equal to 4 inputs

    int n=0;
    int i,j; //counters
	
	if(argc==4)Tamb=300; //set to default value of 300K
	else sscanf(argv[3],"%lf",&Tamb); //or else we take as input from user
	
	assert(Tamb>0); //checking that temperature can't be less than 0 

	for (i= 0; i<4;i++)Tcore[i]=Tamb;

	FILE *paramFile;	
	FILE *powerFile;
	FILE *outputFile;
	
	paramFile = fopen(argv[1], "r");
	assert(paramFile != NULL);
    	powerFile = fopen(argv[2],"r");
	assert(powerFile != NULL);
   	 
	if(argc==5){outputFile = fopen(argv[4],"w");}
	else{outputFile=fopen(argv[3],"w");}
	
	assert(outputFile != NULL);
		

	//Initializing Carray (checked)
	//Note: Assuming first line has 4 C values
	for (i=0; i<4;i++){
		fscanf(paramFile, "%lf", &value); //should print each C value and now  CHAR contains the C value
		Carray[i]= value;
		assert(value != 0);
	}
		
	//Initializing Rmatrix (checked)
	//Note: Assuming that matrix is 5 by 5
	
	//for resistances, storing in Rmatrix
	for (i=0; i<5;i++)
	{				
		for(j=0; j<5; j++){
			fscanf(paramFile, "%lf", &value);//reading a new value
			Rmatrix[i][j]= value;
			assert(value != 0);
			//printf(" R%d,%d --> %d ", i, j, value);	//-->checking correct value is in correct location
			//if(j==4)printf("\n"); //go to new line after row is done		
		}
	}

	//WHERE EVERYTHING BEGINS
	FindTempAge(powerFile, outputFile);         

	fclose(paramFile);
	fclose(powerFile);
	fclose(outputFile);

return 0;
}		

	






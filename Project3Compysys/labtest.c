#include <stdio.h>
#include <stdlib.h>

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
//storing temporary temperatures in between coefficients calculations
double T1;
double T2;
double T3;
double T4;

//Assuming that we have 4 cores
int numCores=4; //number of cores
//power array
int AgeOrTemp=0;
double newAr[5] = {T1,T2.T3,T4,Tamb};
double Age[5];	

double power[4];
double time = 0;
	
	//New stuff
	
	//TEMPERATURE RISES AT THIS RATE
	
	// Calculate (Ti-Tj)/Ri,j with i fixed and j varying
        double sumT(int i)
     {
		double sum=0;
        
    	    for(int j=0; j<numCores+1; j++)
		{ 
			if(j==i){j=i+1;} //if diagonal, we ignore because sum will be 0
			sum+=(Tcore[i]-newAr[j])/Rmatrix[i][j]; 
	      	}	
		
		return sum; //return sum	
     } //end of sum function
	

	double f(int core) //w is our power, C is capacitance
	{
		//printf("Power is: %lf\n",power[core]);
		//printf("sum is: %lf\n",sumT(core));
		//printf("capac is: %lf\n",Carray[core]);
		return((power[core] - sumT(core))/Carray[core]);
	}

	double beta(int core)
	{
		double value;
 	        double alphaTamb=exp(-Ea/K*Tamb);
   
   
 		 value = exp(-Ea/K*Tcore[core])/alphaTamb;
	
		
		return value;	
			
	}

/*****************************************************************/
/******************RUNGE KUTTA************************************/
/*****************************************************************/	
	double rk(int numCores, double Ar[], double initialValue, double (*f)(double ,double ) ){

		int i; //counter for our for loops

		for (i=0;i<numCores;i++)
		{
			K[0][i] = h*((*f)(i));//i:core ; getting the values of coefficient K0 for each core ASK ABOUT *F
		}
		//printf("CHECKING K: %lf %lf %lf %lf",K[0][0], K[0][1], K[0][2], K[0][3]); 
			
		//update temperatures
		T1 = Tcore[0] + K[0][0]/2;
		T2 = Tcore[1] + K[0][1]/2;
		T3 = Tcore[2] + K[0][2]/2;
		T4 = Tcore[3] + K[0][3]/2;
		
		//find K2
		for (i=0;i<numCores;i++)
		{
			//find power of core
			// fscanf(powerFile, "%lf", &pow);//powerFIle defined as global varaible		
			K[1][i] = h*((*f)(i));//getting the values of coefficient K2 for each core
		}
		
		
		//update temperatures
		T1 = Tcore[0] + K[1][0]/2;
		T2 = Tcore[1] + K[1][1]/2;
		T3 = Tcore[2] + K[1][2]/2;
		T4 = Tcore[3] + K[1][3]/2;
		
		
		//find K3
		for (i=0;i<numCores;i++)
		{
			//find power of core
			// fscanf(powerFile, "%lf", &pow);//powerFIle defined as global varaible		
			K[2][i] = h*((*f)(i));//getting the values of coefficient K3 for each core
		}
		
		
		//update temperatures
		T1 = Tcore[0] + K[2][0];
		T2 = Tcore[1] + K[2][1];
		T3 = Tcore[2] + K[2][2];
		T4 = Tcore[3] + K[2][3];
		
		//find K4
		for (i=0;i<numCores;i++)
		{
			//find power of core
			// fscanf(powerFile, "%lf", &pow);//powerFIle defined as global varaible		
			K[3][i] = h*((*f)(i));//getting the values of coefficient K4 for each core
		}
		
		//find new temperatures
		Tcore[0] = Tcore[0] + (K[0][0]+2*K[1][0]+2*K[2][0]+K[3][0])/6;
		Tcore[1] = Tcore[1] + (K[0][1]+2*K[1][1]+2*K[2][1]+K[3][1])/6;
		Tcore[2] = Tcore[2] + (K[0][2]+2*K[1][2]+2*K[2][2]+K[3][2])/6;
		Tcore[3] = Tcore[3] + (K[0][3]+2*K[1][3]+2*K[2][3]+K[3][3])/6;
	}
/*****************************************************************/
/******************RUNGE KUTTA END********************************/
/*****************************************************************/	


	void FindTemperature(FILE *powFile, FILE *of){

	    double Temperature=Tamb;
	    int n=0; //# of diff eq
	    int i=0; //current core we are working
	    int count=0;
	    int core;
	    double pow;
		 
		//while(fscanf(powFile, "%lf", &pow)!=EOF){//check lf
			//find power of core
			//fscanf(powerFile, "%lf", &pow);//powerFIle defined as global variable	
		double (*functionptr)(int);
		functionptr= &f;
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
			n=0;	
			rk(numCores,functionptr);//sumT uses ambient temp at the beginning 
			
			fprintf(of,"%lf ",time);
			time=time+h;
			for(i=0;i<numCores;i++){
			fprintf(of, "%lf ",Tcore[i]);
			}
			fprintf(of, "\n");
			count++;
		}
}


//****************MAIN*************************
int main(int argc,char* argv[])
{
	
    int size;
    int n=0;
    int i,j; //counters
    int count=0;
	if(argc==4)Tamb=300; //set to default value of 300K
	else sscanf(argv[3],"%lf",&Tamb); //or else we take as input from user

	for (i= 0; i<4;i++)Tcore[i]=Tamb;
	T1 = Tamb; //initially Tamb
	T2 = Tamb; //initially Tamb
	T3 = Tamb; //initially Tamb
	T4 = Tamb; //initially Tamb	

	FILE *paramFile;	
	FILE *powerFile;
	FILE *outputFile;
	
	paramFile = fopen(argv[1], "r");
   	 //size = getSize(paramFile);
    	powerFile = fopen(argv[2],"r");
   	 //outputFile = fopen(argv[4], "w");
	if(argc==5){outputFile = fopen(argv[4],"w");}
	else{outputFile=fopen(argv[3],"w");}
		
	if (paramFile == NULL)
   	{
       		 printf("Error! opening program file\n");
      		  // Program exits if file pointer returns NULL.
      		  exit(1);         
    }
	
	if (outputFile == NULL)
   	 {
       		 printf("Error! opening output file\n");
     	  	 // Program exits if file pointer returns NULL.
       		 exit(1);         
     }
	 
	//Initializing Carray (checked)
	//Note: Assuming first line has 4 C values
	for (i=0; i<4;i++){
		fscanf(paramFile, "%lf", &value); //should print each C value and now  CHAR contains the C value
		Carray[i]= value;
	}
		
	//Initializing Rmatrix (checked)
	//Note: Assuming that matrix is 5 by 5
	
	//for resistances, storing in Rmatrix
	for (i=0; i<5;i++)
	{				
		for(j=0; j<5; j++){
			fscanf(paramFile, "%lf", &value);//reading a new value
			if(value == (int)"\n")count++;
			Rmatrix[i][j]= value;
			//printf(" R%d,%d --> %d ", i, j, value);	//-->checking correct value is in correct location
			//if(j==4)printf("\n"); //go to new line after row is done		
		}
	}

	//WHERE EVERYTHING BEGINS
	FindTemperature(powerFile, outputFile);         

	fclose(paramFile);
	fclose(powerFile);
	fclose(outputFile);


return 0;
}		

	






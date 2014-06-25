// This file is a part of an ADT
// Chetrusca.h is the header file
// The ADT is based on a structure that discribe cars 
// Made by Chetrusca Maxim 3.02.2011


#include "Chetrusca.h" 




void input(CAR *car,int n)
{// Inputs an array of structure CAR from the keyboard. The number of cars n is given.
	int i;
	for (i=0; i<n; ++i)
 { 
	 printf("\nGive the information about the %i car:\n",i+1);
	 puts("Name of the model");
	 scanf("%s",car[i].model);
	 puts("Write the country");
	 scanf("%s",car[i].country);
	 puts("What is the year of manufacturing ?");
	 scanf("%i",&car[i].date);
	 puts("What is the capacity of engine?");
	 scanf("%i",&car[i].capacity);
	 puts("What is the price ?");
	 scanf("%i", &car[i].cost);
	}
}

/////////////////////////////////////////////////////////////////////////

void output(CAR *s,int n)
{// Outputs an array of structure CAR on the screen; n - number of cars.
int i;
for (i=0; i<n; ++i)
{ printf(" \nInformation about car No: %i \n",i+1);
puts("Model:");
printf("%s \n",s[i].model);
puts("Country:");
printf("%s \n",s[i].country);
puts("Date of manufacturing:");
printf("%i \n",s[i].date);
puts("The capacity of engine:");
printf("%i \n",s[i].capacity);
puts("Cost:");
printf("%i \n",s[i].cost);
puts("Press any key for next model");
}

}

/////////////////////////////////////////////////////////////////////////

int search(CAR* cars,int n, char *wanted )
{ // Searches a car by a given name. n- number of cars; wanted - the name of the car to search.
	int i;
	for (i=0; i<n; ++i)
	{
		if (strcmp(cars[i].model,wanted)==0)
		{ 
		puts("Model found!"); 
		return i;
		}
	}
	puts("Model not found.");
	return -1;
}
/////////////////////////////////////////////////////////////////////////

void sort(CAR* cars,int n)
{ //Sorts the array of cars, by price. Bubble sort used. n - numb. of cars;
	int i,j; 
	CAR car;
	for (i=0; i<n-1; ++i)
	{
		for (j=0; j<n-i-1; ++j) 
		{
			if (cars[j].cost>cars[j+1].cost)
			{
				car=cars[j]; 
				cars[j]=cars[j+1];
				cars[j+1]=car;
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////
void edit(CAR* cars,int n, int k)
{//Performs changes in this list of cars, if it's needed. After question, press 'y' or 'n'
	char ans;
	puts("Do you want to change the name of model? y/n");
	fflush(stdin);
	scanf("%c",&ans);
	if (ans=='y')
	{
		puts("Introduce the new name of model:");
		scanf("%s",cars[k].model);
	}
	puts("Do you want to change the country of model? y/n");
	fflush(stdin);
	scanf("%c",&ans);
	if (ans=='y')
	{
		puts("Introduce the new name of country:");
		scanf("%s",cars[k].country);
	}
	puts("Do you want to change the date of manufacturing of model? y/n");
	fflush(stdin);
	scanf("%c",&ans);
	if (ans=='y')
	{
		puts("Introduce the new date of manufacturing:");
	    scanf("%i",&cars[k].date);
	}
	puts("Do you want to change the capacity of model? y/n");
	fflush(stdin);
	scanf("%c",&ans);
	if (ans=='y')
	{
		puts("Introduce the new capacity of the car:");
		scanf("%i",&cars[k].capacity);
	}
	puts("Do you want to change the cost of model? y/n");
	fflush(stdin);
	scanf("%c",&ans);
	if (ans=='y')
	{
		puts("Introduce the new cost of car:");
	    scanf("%i",&cars[k].cost);
	}
}
/////////////////////////////////////////////////////////////////////////


void add(CAR* cars, int *n, int pos)
{//Adds a new car to the existing list of n cars, to the possition pos .
	int i ;
	(*n)++;
	cars=(CAR*)realloc(cars,(*n)*sizeof(CAR));
	if (!cars)
	{
		puts("Memory was not reallocated");
		return ;
	}
	for (i=(*n); i>=pos; --i)
	{
		cars[i]=cars[i-1];
	}
	puts("Give the information about new car:");
	
	 puts("Type the model");
	 scanf("%s",cars[pos].model);
	 puts("Write the country");
	 scanf("%s",cars[pos].country);
	 puts("Type the year of manufacturing with numbers ");
	 scanf("%i",&cars[pos].date);
	 puts("What is the capacity of engine?");
	 scanf("%i",&cars[pos].capacity);
	 puts("What is the price?");
	 scanf("%i", &cars[pos].cost);
return ;
}
/////////////////////////////////////////////////////////////////////////


CAR* reading(CAR* cars, int *n, char *fname)
{//Reads from a file info about an array of cars
	int i=0;
	FILE *f;
	char date[6],capacity[6],price[10];
	f=fopen(fname,"r");
	if (!f)
	{
		puts("File not found.");
		return cars ;
	}
	cars=(CAR*)realloc(cars,sizeof(CAR));
	if (!cars)
	{
		puts("Memory was not reallocated.");
		return cars;
	}

	fscanf(f,"%s %s %s %s %s", cars[0].model,cars[0].country, date, capacity, price);
	cars[0].date=atoi(date);
	cars[0].capacity=atoi(capacity);
	cars[0].cost=atoi(price);
	while (getc(f)!=EOF)
	{
		//printf("%s %s %i %i %i \n",cars[i].model,cars[i].country,cars[i].date,cars[i].capacity,cars[i].cost);
		i++;
		cars=(CAR*)realloc(cars,(i+1)*sizeof(CAR));
		if (!cars)
		{
		puts("Memory was not reallocated.");
		return cars;
		}
			
		fscanf(f,"%s %s %s %s %s",cars[i].model, cars[i].country, date, capacity, price);
		cars[i].date=atoi(date);
		cars[i].capacity=atoi(capacity);
		cars[i].cost=atoi(price);

	}
	puts("File successfully scaned.");
	(*n)=i;
	fclose(f);
	return cars;
}
/////////////////////////////////////////
//END OF FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////
typedef struct
{
	char model[10];
	char country[15];
	int date;
	int capacity;
	int cost;
}CAR;


/////////////////////////////////////////////////////////////////////////
void input(CAR *,int n);
void output(CAR *,int n);
int search(CAR*,int n, char * );
void sort(CAR*,int n);
void edit(CAR* cars,int n, int k);
void add(CAR*, int *n, int pos);
CAR* reading(CAR*, int *n, char *);



/////////////////////////////////////////////////////////////////////////
int main ()
{
	CAR *cars=NULL;
	char *model=NULL;
	int i=0,n=0,k=0,operation=0;
	char fname[30];
	FILE *f=NULL;

while (1) 
{ 
	puts("Press any key to continue");
	puts("      Menu :");
	puts("1. Dynamic memory allocation");
	puts("2. Input of array elements from keyboard");
	puts("3. Searching the element in array ");
	puts("4. Sorting of array");
    puts("5. Editing the element of array ");
	puts("6. Adding a new element in the end ");
	puts("7. Deleting the specified element from array ");
	puts("8. Inserting a new element. ");
	puts("9. Recording array elements in a file. ");
	puts("10.Reading array elements from a file. ");
	puts("11.Output of array elements to the screen. ");
	puts("12.Clearing the memory allocated for array. ");
	puts("0. Exit from the program.");
	printf("\n \n ");
	puts("Enter the operation to be performed:");
	scanf("%i",&operation);
	switch (operation)
	{ 
		case 1 : 
			{
				puts("For how many cars do you need memory ?");
				scanf("%i",&n);
				cars=(CAR*)calloc(n,sizeof(CAR));
				if (!cars) 
				{
					puts("Memory not allocated.Case 1."); return 1;
				}
				
				break;
	
			}
		case 2 :
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				 input(cars,n);
				 break;
				}
		case 3 :
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				model=(char*)malloc(15*sizeof(char));
				if (!model) 
				{
					puts("Memory was not allocated for char * model."); 
					return 1;
				}
				puts("What model are you interested in ?");
				 scanf("%s",model);
				 k=search(cars,n,model);
				 free(model);
				 if (k>=0) 
				 {
				 printf("\nIt costs %i $.\n",cars[k].cost);
				 }
				 break;
			}
		case 4 :
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				puts("Sorted the cars by price.");
				sort(cars,n);
				break;
			}
		case 5 :
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				model=(char*)malloc(15*sizeof(char));
				if (!model) 
				{
					puts("Memory was not allocated."); 
					return 1;
				}
				puts("Introduce the model you want to edit:");
				scanf("%s",model);
				 k=search(cars,n,model);
				 free(model);
				  if (k>=0) 
				 {
				 edit(cars,n,k);
				  }
				 break; 
			}
		case 6 :
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				add(cars,&n,n);
				break;
			}
		case 7 :
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				puts("Write what element you want to delete:");
				scanf("%i",&k);
				k--;
				for (i=k; i<n-1; ++i) 
				{
					cars[i]=cars[i+1];
				}
				n--;
				cars=(CAR*)realloc(cars,(n)*sizeof(CAR));
				if (!cars)
				{
					puts("Memory was not reallocated."); 
					return 1;
				}
				break;
			}
		case 8:
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				puts("Give the possition of new element:");
				scanf("%i",&k);
				add(cars,&n,k-1);
				break;
			}
		case 9 :
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				puts("What is the name of file ? ");
				scanf("%s",fname);
				f=fopen(fname,"w");
				if (!f)
				{
					puts("File not open.");
					return 1;
				}
				for (i=0; i<n; ++i) 
				{
					fprintf(f,"%s %s %i %i %i\n",cars[i].model,cars[i].country,cars[i].date,cars[i].capacity,cars[i].cost);
				}
				fclose(f);
				puts("Done writting in file.");
				break;
			}
		case 10 :
			{
				puts("Introduce the name of the file:");
				scanf("%s",fname);
				cars=reading(cars,&n,fname);
				break;
			}
		case 11 : 
			{
				if (!cars) 
				{
					puts("Memory not allocated.Case 1.");  break;
				}
				output(cars,n);
				break;
			}
		case 12:
			{
				cars=(CAR*)realloc(cars,0);
				puts("Memory deallocated.");
				break;
			}
		case 0 :
			{
				return 0; 
			}
defalult :
			{
				puts("Unknown command.");
			}
	}
}



	return 0;
}

/////////////////////////////////////////////////////////////////////////





void input(CAR *car,int n)
{
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
{
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
{ int i;
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
{ 
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
{
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
	puts("Do you want to change the capacity of manufacturing of model? y/n");
	fflush(stdin);
	scanf("%c",&ans);
	if (ans=='y')
	{
		puts("Introduce the new capacity of the car:");
		scanf("%i",&cars[k].capacity);
	}
	puts("Do you want to change the cost of manufacturing of model? y/n");
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
{
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
{
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

	fscanf(f,"%s %s %s %s %s",cars[0].model,cars[0].country,date,capacity,price);
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
			
		fscanf(f,"%s %s %s %s %s",cars[i].model,cars[i].country,date,capacity,price);
		cars[i].date=atoi(date);
		cars[i].capacity=atoi(capacity);
		cars[i].cost=atoi(price);

	}
	puts("File successfully scaned.");
	(*n)=i;
	fclose(f);
	return cars;
}

/////////////////////////////////////////////////////////////////////////

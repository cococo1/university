#include "Chetrusca.c" 
// An ADT, contains CAR structure, and some functions. 

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
					fprintf(f,"%s %s %i %i %i\n", cars[i].model, cars[i].country, cars[i].date, cars[i].capacity, cars[i].cost);
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

////////////////////////////////////////////////////////////////////////

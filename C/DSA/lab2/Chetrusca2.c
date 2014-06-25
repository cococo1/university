// This file should be attached to Chetrusca2.h header file.
// Here is the defenition of functions declared there.
// Created : 19/02/2011 ; 
// Author : Chetrusca Maxim


#include "Chetrusca2.h"


void show_menu(void)
{
	system("CLS");
	puts("\t\t ___MENU___ ");
	puts("1. Create a new list of cars;");
	puts("2. Input the list of cars from the keyboard;");
	puts("3. Output the list of cars on the screen;");
	puts("4. Search a car by the name of the model;");
	puts("5. Edit some data about a car;");
	puts("6. Swap two cars;");
	puts("7. Sort the list of cars in ascending order by price;");
	puts("8. Destroy the existing list of cars;");
	puts("9. Exit the program.");
	puts("");
	puts("Select an operation to be performed ( type a number):");
}

/////////////////////////////////////////////////////////



CAR* memory_allocation(int n)
{
	CAR *head=NULL, *current, *pointer;
	int i;
	head=(CAR*)malloc(sizeof(CAR));
	if (n==0) 
	{
		puts("Number of cars you introduced is 0");
		return NULL;
	}
	n--; // The variable head is defined anyway,
	// either there is one or more elements; n-- to avoid allocating memory for one more element
	if (!head)
	{
		puts("Memory not allocated. Case 1");
		return NULL;
	}
	head->next=NULL;

	for (i=0;i<n;i++)
	{
		current=(CAR*)malloc(sizeof(CAR));
		if (!current)
		{
			puts("Memory not allocated. Case 2");
            return NULL;
		}
		current->next=NULL;

		if (i==0)
		{
			head->next=current;
		}
		else
		{
			pointer->next=current;
		}

        pointer=current;
	}
	puts("Memory allocated.");
	return head;
}
/////////////////////////////////////////////////////////




void input (CAR *head)
{
	CAR *current;
	int i=0;
	if (!head) { puts("The list does not exist, allocate memory first, then input."); return; }
    current=head;
	puts("Enter info about the cars:");
    while(current)
        {
            printf("\nCar %d: ", i+1);
			puts("\nModel:");
			scanf("%s", current->model);
			puts("\nCountry:");
            scanf("%s", current->country);
			puts("\nYear of manufacturing:");
			scanf("%i", &current->date);
			puts("\nPrice of the model:");
			scanf("%i", &current->cost);
			puts("\nCapacity of engine:");
			scanf("%i", &current->capacity);

            current=current->next;
            i++;
        }
	puts("Input finished.");
}


/////////////////////////////////////////////////////////



void output (CAR *head)
{
	int i=0;
	if (!head) { puts("The list does not exist, allocate memory first, then input, then output."); return; }
	while (head)
	{
		puts("");
		printf("Info about car No %d", i+1);
		printf("\nAdress of the current element: %p",head);
		printf("\nModel: %s", head->model);
        printf("\nCountry: %s", head->country);
        printf("\nYear of manufacturing: %i", head->date);
        printf("\nPrice of model: %i",head->cost);
        printf("\nCapacity of engine: %d", head->capacity);
		puts("");
        head=head->next;
        i++;
	}

}
/////////////////////////////////////////////////////////


CAR* search (CAR *head, char* asked_model)
{
	int i=0;
	if (!head) { puts("The list does not exist, allocate memory first, then input."); return NULL; }
	while (head)
	{
		i=strcmp(head->model,asked_model);
		if (i==0)
		{
			return head;
		}
		head=head->next;
	}
	return NULL;
}



///////////////////////////////////////////////////////////

void edit (CAR* model_to_modify)
{

	//User should answer questions using 'y' and 'n' keys .
	if (!model_to_modify)
	{
		puts("Error: You want to modify a model that does not exist.");
		return;
	}
	char answer;
label: one: puts("Do you want to modify the name of the model? y/n");
	fflush(stdin);
	scanf("%c",&answer);
	if ((answer!='y')&&(answer!='n')) { puts("Unknown answer, please try again:"); goto one;}
	if (answer=='y')
	{
		puts("Introduce the new name of this model:");
		fflush(stdin);
		scanf("%s",model_to_modify->model);
	}
two:	puts("Do you want to modify the country of the model? y/n");
	fflush(stdin);
	scanf("%c",&answer);
	if ((answer!='y')&&(answer!='n')) { puts("Unknown answer, please try again:"); goto two;}
	if (answer=='y')
	{
		puts("Introduce the new country of this model:");
		fflush(stdin);
		scanf("%s",model_to_modify->country);
	}
three:	puts("Do you want to modify the capacity of engine of the model? y/n");
	fflush(stdin);
	scanf("%c",&answer);
	if ((answer!='y')&&(answer!='n')) { puts("Unknown answer, please try again:"); goto three;}
	if (answer=='y')
	{
		puts("Introduce the new capacity of this model:");
		fflush(stdin);
		scanf("%i",&model_to_modify->capacity);
	}
four: puts("Do you want to modify the price of this model? y/n");
	fflush(stdin);
	scanf("%c",&answer);
	if ((answer!='y')&&(answer!='n')) { puts("Unknown answer, please try again:"); goto four;}
	if (answer=='y')
	{
		puts("Introduce the new price of this model:");
		fflush(stdin);
		scanf("%i",&model_to_modify->cost);
	}
five:	puts("Do you want to modify the year of manufacturing of this model? y/n");
	fflush(stdin);
	scanf("%c",&answer);
	if ((answer!='y')&&(answer!='n')) { puts("Unknown answer, please try again:"); goto five;}
	if (answer=='y')
	{
		puts("Introduce the new year of manufacturing of this model:");
		fflush(stdin);
		scanf("%i",&model_to_modify->date);
	}
}

//////////////////////////////////////////////////////////

int list_length(CAR *head) //Returns the length of the list
{
	int n=0;
	while (head)
	{
		++n;
		head=head->next;
	}
	return n;
}
/////////////////////////////////////////////////////////

void swap(CAR *a, CAR* b)
{
	CAR *next_a,*next_b,t;
	if (!a || !b) { puts("Elements does not exist"); return; };
	next_a=a->next;
	next_b=b->next;
	t=*a;
	*a=*b;
	*b=t;
	a->next=next_a;
	b->next=next_b;
}
//////////////////////////////////////////////////////////


void sort (CAR *head)
{
	int i,j,n;
	CAR *one, *two;
	if (!head) { puts("The list is empty."); return; }
	n=list_length(head);
	for (i=0; i<n-1; ++i) 
	{
		one=head;
		two=head->next;
		for (j=0; j<n-i-1; ++j)
		{
			if (one->cost>two->cost)
			{
				swap(one, two);
			}
			one=one->next;
			two=two->next;
		}
	}
	puts("List of cars sorted by price.");
}
//////////////////////////////////////////////////


void free_list(CAR** head)
{
	CAR *c;
	if (!*head) {puts("The list is already empty."); return;}
	while (*head)
	{
		c=*head;
		*head=(*head)->next;
		free(c);
		c=NULL;
	}
	*head=NULL;
	puts("Memory is free.");
}
//////////////////////////////////////////////////////////



//////////////////////////////////////////
//END OF FILE .

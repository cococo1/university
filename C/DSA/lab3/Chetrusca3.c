// This file should be attached to Chetrusca3.h header file.
// Here is the defenition of functions declared there.
// Last time modified: 10/03/2011 ;
// Author : Chetrusca Maxim


#include "Chetrusca3.h"


extern CAR *head; // A global variable used as pointer to first element of link list.


//---------------------------------------------------

int memory_allocation(int n)
{

	CAR  *current=NULL, *pointer=NULL;
	int i=0;
	head=(CAR*)malloc(sizeof(CAR));
	if (n==0 ||!head) return 0;

	head->next=NULL;

	for (i=0;i<n-1;i++)
	{
		current=(CAR*)malloc(sizeof(CAR));
		if (!current)
		{
            return 0;
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
	return 1;
}
//---------------------------------------------------


void input ()
{
	CAR *current=NULL;
	int i=0;
	if (!head) { puts("The list does not exist, allocate memory first, then input."); return; }
    current=head;
	puts("Enter info about the cars:");
    while(current)
        {
            printf("\nCar %d: ", i+1);
			puts("\nModel:");
			fflush(stdin);
			scanf("%s", current->model);
			puts("\nCountry:");
			fflush(stdin);
            scanf("%s", current->country);
			puts("\nYear of manufacturing:");
			fflush(stdin);
			scanf("%i", &current->date);
			puts("\nPrice of the model:");
			fflush(stdin);
			scanf("%i", &current->cost);
			puts("\nCapacity of engine:");
			fflush(stdin);
			scanf("%i", &current->capacity);

            current=current->next;
            i++;
        }
	puts("Input finished.");
}
//---------------------------------------------------

void output ()
{
	int i=0;
	CAR *current=NULL;
	if (!head)  return;
	current=head;
	while (current)
	{
		puts("");
		printf("Info about car No %d", i+1);
		printf("\nAdress of the current element: %p",current);
		printf("\nAdress of the next element: %p",current->next);
		printf("\nModel: %s", current->model);
        printf("\nCountry: %s", current->country);
        printf("\nYear of manufacturing: %i", current->date);
        printf("\nPrice of model: %i",current->cost);
        printf("\nCapacity of engine: %d", current->capacity);
		puts("");
        current=current->next;
        i++;
	}

}
//---------------------------------------------------

int search (char* asked_model, CAR **result)
{
	int i=0;
	CAR *current=head;
	if (!current)  return 0;
	while (current)
	{
		i=strcmp(current->model,asked_model);
		if (i==0)
		{
			*result=current;
			return 1;
		}
		current=current->next;
	}
	return 0;
}
//---------------------------------------------------

int edit (CAR* model_to_modify)
{
	char answer=0;
	//User should answer questions using 'y' and 'n' keys .
	if (!model_to_modify) return 0;

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
	return 1;
}
//------------------------------------------------------

int list_length() //Returns the length of the list
{
	int n=0;
	CAR *current=head;
	while (current)
	{
		++n;
		current=current->next;
	}
	return n;
}
//------------------------------------------------------

int swap(CAR *a, CAR* b)
{
	CAR *next_a=NULL, *next_b=NULL, t;
	if (!a || !b) return 0;
	next_a=a->next;
	next_b=b->next;
	t=*a;
	*a=*b;
	*b=t;
	a->next=next_a;
	b->next=next_b;
	return 1;
}
//------------------------------------------------------


int sort ()
{
	int i=0,j=0,n=0;
	CAR *one=NULL, *two=NULL, *current=head;
	if (!current) return 0;
	n=list_length();
	for (i=0; i<n-1; ++i)
	{
		one=current;
		two=current->next;
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
	return 1;
}
//------------------------------------------------------

int insert(CAR *after_this_adress,CAR new_element)
{
	CAR *current=NULL;
	if (!after_this_adress) return 0;
	current=(CAR*)malloc(sizeof(CAR));
	if (!current)  return 0;
	current->next=after_this_adress->next;
	after_this_adress->next=current;
	current->capacity=new_element.capacity;
	current->cost=new_element.cost;
	strcpy(current->country,new_element.country);
	current->date=new_element.date;
	strcpy(current->model,new_element.model);
	return 1;
}
//------------------------------------------------------

int deleting( CAR *adress)
{
	CAR *p=NULL ;
	if (!head || !adress )  return 0;
	if (head==adress) { p=head; head=head->next; free(p); p=NULL; return 1; }
	p=head;

	while ((p->next!=adress) && (p))
	{
		p=p->next;
	}
	if (!p) return 0;
	p->next=adress->next;
	free(adress);
	adress=NULL;
	return 1;
}
//------------------------------------------------------

int write_in_file(char* file_name)
{
	FILE *f=NULL;
	CAR *current=NULL;
	if (!head)  return 0;
	current=head;
	f=fopen(file_name,"w");
	if (!f) return 0;
	while (current)
	{
		fprintf(f,"%s %s %i %i %i\n",current->model,current->country, current->capacity, current->cost, current->date);
		current=current->next;
	}
	fclose(f);
return 1;
}
//------------------------------------------------------

int read_from_file(char* file_name)
{
	int i=0;
	FILE *f=NULL;
	CAR  *c=NULL, *p=NULL;
	char capacity[10], cost[10], date[10];
	f=fopen(file_name,"r");
	if (!f || head)  return 0;


	while (!feof(f))
	{

		if (i==0)
		{
		    head=(CAR*)malloc(sizeof(CAR));
		    if (!head)  return 0;
		    head->next=NULL;
			fscanf(f,"%s %s %s %s %s",head->model,head->country, capacity, cost, date);
			head->capacity=atoi(capacity);
			head->cost=atoi(cost);
			head->date=atoi(date);
			p=head;

		}
		else
		{
		    c=(CAR*)malloc(sizeof(CAR));
		    if (!c) return 0;
		    c->next=NULL;
			fscanf(f,"%s %s %s %s %s",c->model,c->country, capacity, cost, date);
			c->capacity=atoi(capacity);
			c->cost=atoi(cost);
			c->date=atoi(date);
			p->next=c;
			p=c;
		}
		++i;

	}
	deleting(p);
    return 1;

}
//------------------------------------------------------

void free_list()
{
	CAR *c=NULL;
	if (!head) return ;
	while (head)
	{
		c=head;
		head=head->next;
		free(c);
		c=NULL;
	}
	head=NULL;
}
//------------------------------------------------------

CAR* adress_of_last(void)
{
    CAR *current=NULL;
    current=head;
    while (current->next)
    {
        current=current->next;
    }
    return current;
}
//------------------------------------------------------

void divide_list(CAR* head2)
{
    CAR *current=NULL;
    if (!head || !head2) return;
    if (head==head2) {head=NULL; return; }
    current=head;
    while (current->next!=head2 && current)
    {
        current=current->next;
    }
    if (!current) return;
    current->next=NULL;
}
//------------------------------------------------------

void concat_lists(CAR* head2)
{
    CAR *current=NULL;
    if (!head || !head2) return;
    current=head;
    while (current->next)
    {
        current=current->next;
    }
    current->next=head2;
}
//------------------------------------------------------
////////////////////////////////////////////////////////
//END OF FILE .

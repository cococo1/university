// A program for performing some operations upon a car database .Uses singly link-lists.
// Last time modified: 10/03/2011
// Author : Chetrusca Maxim


#include "Chetrusca3.h"

void show_menu(void); //Simple function used to display the menu of operations;
void test_input(void); // A test function , used to simulate the input function;

CAR *head=NULL; // A global variable used as pointer to first element of link list.


int main ()
{
	CAR *p1=NULL, *p2=NULL, new_element, *head2=NULL;

	char name[20],answer=0, name2[20];
    int n=0,operation=0,if_succeded=0,input_performed=0;


	while (1)
	{
		show_menu();
		fflush(stdin);
		scanf("%s",&name);
		operation=atoi(name);

		switch (operation)
		{
		case 1 :
			{
				// system("CLS"); //clrscr();
				if (head)
				{
label: label_1: puts("List already exist. Do you want to destroy it and create new one ? y/n");
					fflush(stdin);
					scanf("%c",&answer);
					if ((answer!='y') && (answer!='n')) { puts("Invalid answer. Please, try again:"); goto label_1;}
					if (answer=='y') free_list();
					else goto label_2;
				}
				puts("Give the number of cars:");
				fflush(stdin);
				scanf("%i",&n);
				if (n==0) { puts("You introduced 0."); goto label_2; }
				if_succeded=memory_allocation(n);
				if (if_succeded) puts("Allocation succeded.");
				else puts("Error . Memory not allocated.");
			label_2:	puts("Press any key to continue;");
				break;
			}
		case 2:
			{
				// system("CLS");
				
				if (!head) {puts("List is empty.");  break;}
				if (input_performed)
				 {
            label_3:    puts("The list already contain data. Do you want to rewrite it ? y/n");
				     fflush(stdin);
				     scanf("%c",&answer);
				     if (answer!='y' && answer!='n') {puts("Unknown answer, please try again:"); goto label_3; }
				     if (answer=='n') break;
                 }
				input();
				//test_input();
				input_performed=1;
				puts("Input completed. Press any key to continue.");
				break;
			}
		case 3:
			{
				// system("CLS");
				if (!head || !input_performed) {puts("List is empty."); break; }
				output();
				break;
			}
		case 4:
			{
				// system("CLS");
				if (!head || !input_performed) {puts("List is empty."); break; }
				puts("Give the name of model of car you want to search:");
				fflush(stdin);
				scanf("%s",name);
				if_succeded=search(name,&p1);
				if (if_succeded)
				{
					puts("Model found! Here is the info about it:");
				    printf("Model: %s \n",p1->model);
				    printf("Country: %s \n",p1->country);
				    printf("Capacity of engine: %i \n",p1->capacity);
				    printf("Year of manufacturing: %i \n",p1->date);
				    printf("Price: %i \n",p1->cost);
				}
				else
				{
				    puts("Model not found.");
				}
				p1=NULL;
				break;
			}
		case 5:
			{
				// system("CLS");
				if (!head || !input_performed) {puts("List is empty."); break; }
				puts("Introduce the name of model you want to edit:");
				fflush(stdin);
				scanf("%s",name);
				if_succeded=search(name,&p1);
				if (!if_succeded) {puts("Such a car does not exist."); break;}
				puts("Model found!");
				edit(p1);
				puts("Modifying complete.");
				break;
			}
		case 6:
			{
				// system("CLS");
				if (!head || !input_performed) {puts("List is empty."); break; }
				puts("Introduce the name of the first model to swap:");
				fflush(stdin);
				scanf("%s",name);
				if_succeded=search(name,&p1);
				if (!if_succeded) {puts("Such a car does not exist."); puts("Press any key to continue:"); break; }
				puts("Introduce the name of the second model to swap:");
				fflush(stdin);
				scanf("%s",name2);
				if_succeded=search(name2,&p2);
				if (!if_succeded) {puts("Such a car does not exist."); puts("Press any key to continue:");  break; }
				swap(p1,p2);
				puts("Cars swapped.");
				p1=NULL;
				p2=NULL;
				break;
			}
		case 7:
			{
				// system("CLS");
				if (!head || !input_performed) {puts("List is empty."); break; }
				if_succeded=sort();
				if (!if_succeded) puts("Error while sorting.");
				else puts("Sorting completed. Press any key to continue:");
				break;
			}
		case 8:
			{
				// system("CLS");
				puts("Are you sure you want to destroy the existing list ? y/n");
				fflush(stdin);
				scanf("%c",&answer);
				if ((answer!='y') && (answer!='n')) { puts("Invalid answer.");}
				if (answer=='y') {free_list(); puts("Memory is free.");  }
				input_performed=0;
				break;
			}
        case 9 :
			{
			    // system("CLS");
                if (!head || !input_performed) {puts("List is empty."); break;};
			    printf("The length of the list is: %i", list_length());
				break;
			}
		case 0 :
			{
			    free_list();
				return 0;
			}
        case 10:
        {
          // system("CLS");
          if (!head || !input_performed) {puts("List is empty.(Input needed)."); break;};
          puts("Data about new element:");
          puts("Give the name of the model :");
          fflush(stdin);
          scanf("%s",new_element.model);
          puts("Give the country of the element:");
          fflush(stdin);
          scanf("%s",new_element.country);
          puts("Give the year of manufacturing of new car:");
          fflush(stdin);
          scanf("%i",&new_element.date);
          puts("Give the capacity of engine:");
          fflush(stdin);
          scanf("%i",&new_element.capacity);
          puts("Give the price of the car:");
          fflush(stdin);
          scanf("%i",&new_element.cost);

          p1=adress_of_last();
          if (!p1) {puts("Error!"); break; }
          if_succeded=insert(p1,new_element);
          if (!if_succeded) puts("Something's wrong!");
          else  puts("New element added.");
          p1=NULL;
          break;
        }
        case 11:
        {
            // system("CLS");
            if (!head || !input_performed) {puts("List is empty."); break; }
            puts("Introduce the name of model of car you want to delete:");
            fflush(stdin);
            scanf("%s",name);
            if_succeded=search(name,&p1);
            if (!if_succeded || !p1) {puts("Model not found."); break;}
            if_succeded=deleting(p1);
            if(!if_succeded) puts("Error!");
            else puts("Element deleted.");
            break;
        }
        case 12:
        {
          // system("CLS");
          if (!head || !input_performed) {puts("List is empty."); break; }

          puts("Data about new element:");
          puts("Give the name of the model :");
          fflush(stdin);
          scanf("%s",new_element.model);
          puts("Give the country of the element:");
          fflush(stdin);
          scanf("%s",new_element.country);
          puts("Give the year of manufacturing of new car:");
          fflush(stdin);
          scanf("%i",&new_element.date);
          puts("Give the capacity of engine:");
          fflush(stdin);
          scanf("%i",&new_element.capacity);
          puts("Give the price of the car:");
          fflush(stdin);
          scanf("%i",&new_element.cost);

          puts("Introduce the name of the model after which you want to insert a new car:");
          fflush(stdin);
          scanf("%s",name);
          if_succeded=search(name,&p1);
          if (!if_succeded || !p1) {puts("Model not found. Press any key to continue:"); break; }
          if_succeded=insert(p1,new_element);
          if (!if_succeded) puts("Error!");
          else puts("Element inserted. Press any key to continue:");
          p1=NULL;
 
          break;
        }
        case 13:
        {
            // system("CLS");
            if (!head) {puts("List is empty (memory not allocated).");  break; }
            p1=adress_of_last();
            if (!p1) puts("Error!");
            else printf("The adress of the last element is : %p",p1);
            p1=NULL;
         // getch();
          break;
        }
        case 14:
        {
            // system("CLS");
             if (!head || !input_performed) {puts("List is empty ."); break; }
             puts("Introduce the name of the model, which will become the first element of the second link list:");
             fflush(stdin);
             scanf("%s",name);
             if_succeded=search(name,&head2);
             if (!if_succeded || !head2) {puts("Model not found."); break;}
             divide_list(head2);
             puts("List divided.");
             // getch();
    label_4:
             puts("   Select next operation: ");
             puts("1. Output first link list; ");
             puts("2. Output second link list; ");
             puts("0. Continue work with first list; ");
             fflush(stdin);
             scanf("%s",name);
		     operation=atoi(name);
		     switch (operation)
		     {
		         case 0:
		         {
		             break;
		         }
		         case 1:
		         {
		             if (!head) puts("List is empty.");
		             output();
		             // getch();
		             goto label_4;
		             break;
		         }
		         case 2:
		         {
		             n=0;
		             p2=head2;
		             while (p2)
		             {
		                 puts("");
		                 printf("Info about car No %d", n+1);
		                 printf("\nAdress of the current element: %p",p2);
		                 printf("\nAdress of the next element: %p",p2->next);
		                 printf("\nModel: %s", p2->model);
                         printf("\nCountry: %s", p2->country);
                         printf("\nYear of manufacturing: %i", p2->date);
                         printf("\nPrice of model: %i",p2->cost);
                         printf("\nCapacity of engine: %d", p2->capacity);
		                 puts("");
                         p2=p2->next;
                         n++;
                    }
                    p2=NULL;
                    // getch();
                     goto label_4;
                     break;
		         }
		         default:
		         {
		             puts("Unknown command. Please, try again:");
		             // getch();
                    goto label_4;
		         }
		     }
		     // getch();
		     break;
        }
        case 15:
		{
		    // system("CLS");
		    if (!head || !input_performed || !head2) {puts("One of the lists is empty."); break; }
          concat_lists(head2);
          puts("Concatenated the list that was separated in operation 14 back to first link list.");
          break;
		}
		case 16:
		{
		     // system("CLS");
		    if (!head || !input_performed) {puts("List is empty ."); break; }
		    puts("Give the name of the file :");
		    fflush(stdin);
		    scanf("%s",name);
		  if (!strcmp(name,"Chetrusca3.h") || !strcmp(name,"Chetrusca3.c") || !strcmp(name,"main.c"))
		  {
		       puts("Bad file name.");
		       break;
		  }
		    if_succeded=write_in_file(name);
		    if (!if_succeded) puts("Error while writting in file.");
		    else puts("Info saved in file.");
            break;
		}
		case 17:
		{
		    // system("CLS");
		    if (head) {puts("First, free the existent list, then read from file."); break; }
		    puts("Give the name of the file:");
		    fflush(stdin);
		    scanf("%s",name);
		    if_succeded=read_from_file(name);
		    if (!if_succeded) { puts("Error while reading from file"); input_performed=0; }
		    else { puts("Data read from file."); input_performed=1; }
            break;
		}



		default :
			{
			    // system("CLS");
				puts("Unknown command, please try again:");
				// getch();
			}
		}

	}

	// getch();
	return 0;
}



//------------------------------------------------------

void show_menu(void)
{
	// system("CLS");
	puts("\t\t ___MENU___ ");
	puts("1. Create a new list of cars;");
	puts("2. Input the list of cars from the keyboard;");
	puts("3. Output the list of cars on the screen;");
	puts("4. Search a car by the name of the model;");
	puts("5. Edit some data about a car;");
	puts("6. Swap two cars;");
	puts("7. Sort the list of cars in ascending order by price;");
	puts("8. Destroy the existing list of cars;");
	puts("9. Find how many cars are in the list; ");
	puts("10. Add a new car at the end; ");
	puts("11. Delete a car; ");
	puts("12. Insert a car; ");
	puts("13. Output the adress of the last element; ");
	puts("14. Divide the list into two; ");
	puts("15. Merge two lists of cars; ");
	puts("16. Write info about cars in file; ");
	puts("17. Read data from file; ");
    puts("0. Exit the program.");
	puts("");
	puts("Select an operation to be performed ( type a number):");
}
//------------------------------------------------------

void test_input(void)
{
	int i=1;
	CAR *current=head;
	if (!current) { puts("Error!"); return; }
	while (current)
	{
		current->capacity=i;
		current->cost=rand()%10;
		puts("Give the country");
		fflush(stdin);
		scanf("%s",current->country);
		current->date=i;
		puts("Give the model");
		fflush(stdin);
		scanf("%s",current->model);
		current=current->next;
		i++;
	}
}
//------------------------------------------------------
// END OF FILE./////////////////////////////////////////

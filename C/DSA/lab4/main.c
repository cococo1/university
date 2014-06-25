//This is a file with main function for :
//Laboratory work Nr. 4, DSA, processing a binary tree ; work on a car database;
//Modified : 07/04/2011
//Author : Chetrusca Maxim

#include <stdio.h>
#include <stdlib.h>
#include "Chetrusca4.h"

#define getch(); ;
#define CLS ' '

void display_menu(void);

//-----------------------------------


int main ()
{
	// system("CLS");
	char name[20],choice;
	node *root=NULL;
	node *p=NULL;
	int operation=-1,input_performed=0;
	while (1)
	{
		display_menu();
		puts("Choose an operation from menu :");
		fflush(stdin);
		scanf("%i",&operation);
		switch (operation)
		{
		case 1:
			{
				// system("CLS");
				if (root) {puts("The tree already exist."); break;}
				puts("Using queue - press q;");
				puts("Using stack - press s;");
				fflush(stdin);
				scanf("%c",&choice);
				if (choice=='q') root=qcreate_a_tree();
				else if (choice=='s') root=screate_a_tree();
				else puts("Unknown command.");
				if (root) puts("The binary tree was created.");
				// getch();
				break;
			}
		case 2:
			{
				// system("CLS");
				if (!root || input_performed)
				{puts("The tree does not exist, or the input was already performed."); break;} 
				puts("Using queue - press q;");
				puts("Using stack - press s;");
				fflush(stdin);
				scanf("%c",&choice);
				if (choice=='q') qinput_tree(root);
				else if (choice=='s') sinput_tree(root);
				else  { puts("Unknown command."); break;}
				input_performed=1;
				puts("The input was performed.");
				getch();
				break;
			}
		case 3:
			{
				system("CLS");
				if (!root || !input_performed) 
				{puts("The tree does not exist, or the input was not performed."); getch(); break;}
				puts("Using queue - press q;");
				puts("Using stack - press s;");
				fflush(stdin);
				scanf("%c",&choice);
				if (choice=='q') qoutput_tree(root);
				else if (choice=='s') soutput_tree(root);
				else { puts("Unknown command."); getch(); break;}
				puts("The output was performed.");
				getch();
				break;
			}
		case 4:
			{
				system("CLS");
				if (!root || !input_performed) 
				{puts("The tree does not exist, or the input was not performed."); getch(); break;}
				puts("Using queue - press q;");
				puts("Using stack - press s;");
				fflush(stdin);
				scanf("%c",&choice);
				puts("Give the name of the car to search:");
				fflush(stdin);
				scanf("%s",name);
				if (choice=='q') p=qsearch_node(root,name);
				else if (choice=='s') p=ssearch_node(root,name);
				else { puts("Unknown command."); getch(); break;}
				if (!p) {puts("Car not found."); getch(); break;}
				printf("Car was found ! The price of the car : %i \n",p->price);
				getch();
				break;
			}
		case 5:
			{
				system("CLS");
				if (!root) {puts("The tree does not exist."); getch(); break;}
				puts("Using queue - press q;");
				puts("Using stack - press s;");
				fflush(stdin);
				scanf("%c",&choice);
				if (choice=='q') printf("The number of nodes is: %i \n",qtotal_number(root));
				else if (choice=='s') printf("The number of nodes is: %i \n",stotal_number(root));
				else { puts("Unknown command."); getch(); break;}
				getch();
				break;
			}
		case 6:
			{
				system("CLS");
				if (!root) {puts("The tree does not exist."); getch(); break;}
				puts("Using queue - press q;");
				puts("Using stack - press s;");
				fflush(stdin);
				scanf("%c",&choice);
				if (choice=='q')printf("The height of the tree is : %i \n", qheight(root));
				else if (choice=='s') printf("The height of the tree is : %i \n", sheight(root));
				else { puts("Unknown command."); getch(); break;}
				getch();
				break;
			}
		case 7:
			{
				system("CLS");
				if (!root) {puts("The tree does not exist."); getch(); break;}
				puts("Using queue - press q;");
				puts("Using stack - press s;");
				fflush(stdin);
				scanf("%c",&choice);
				if (choice=='q') qfree_memory(&root);
				else if (choice=='s') sfree_memory(&root);
				else { puts("Unknown command."); getch(); break;}
				input_performed=0;
				puts("Memory is free.");
				getch();
				break;
			}
		case 0:
			{
				sfree_memory(&root);
				return 0;
			}
		default:
			{
				system("CLS");
				puts("Unknown command, please try again.");
				getch();
			}
		}

	}
	return 0;
}
//-------------------------------------------------------------------
void display_menu(void)
{
	system("CLS");
	puts("\t \t MENU: ");
	puts("1. Create a binary tree ;");
	puts("2. Input info about cars from keyboard ;");
	puts("3. Output info about cars on the screen ;");
	puts("4. Search a car by name of model ;");
	puts("5. Output the number of nodes ;");
	puts("6. Output the height of the tree ;");
	puts("7. Clear the memory ;");
	puts("0. Exit the program .");
	puts("");
	puts("");
	
}
//-------------------------------------------------------------------
//END OF FILE.

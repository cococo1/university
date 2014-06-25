//This is a header file to Chetrusca4.cpp
//Laboratory work Nr. 4, DSA, processing a binary tree ; work on a car database;
//Modified : 07/04/2011
//Author : Chetrusca Maxim

typedef struct node //Binary tree
{
	struct node* left;
	struct node* right;
	struct node* parent_adress;
	int node_number;
	char model[20];
	char country[20];
	int year;
	int price;
	int capacity;
}node;

typedef struct elq // queue for in-width traversal of binary tree
{
	node* adress;
	struct elq *next;
}elq;

typedef struct els  //Stack for in-depth traversal of binary tree
{
	node* adress;
	struct els *prev;
}els;


//-------------------------------------------------
//FUNCTION'S PROTOTYPES :
//functions that start with "q" uses queues; with "s" - uses stacks;

int inq(elq **first,elq **last,node* new_element);
// This function adds a new adress of node into queue ;
// *first - adress of the first element of queue ;
// *last - adress of the last element of queue ;
// new_element - adress of a node that will be stored in queue;
//Returns 1 if success, 0 if failed at memory allocation ;
node* delq(elq **first,elq **last);
//This function deletes one adress of the node from queue and returns it ;
int push(els **top, node* adress);
//This function adds a new adress of a node into stack ;
//**top - adress of the adress of the top element from stack;
//*adress - the new info that should be passed into the stack;
node* pop(els**top);
//Deletes one adress from stack and returns it;
node* qcreate_a_tree(void);
//Creates a binary tree using queue and returns the adress of the root ;
node* screate_a_tree(void);
//Creates a binary tree using stack and returns the adress of the root ;
int qinput_tree(node *root); //uses queue
int sinput_tree(node *root);//uses stack
//Inputs the info for each node of the tree from keyboard; root - the adress of the first node;
//Returns 0 if root is NULL, or some problems occur during adding an adress into queue(stack);
int qoutput_tree(node* root);
int soutput_tree(node* root);
//Outputs the info about each node on the screen;
//Returns 0 if root is NULL, or some problems occur during adding an adress into queue;
node* qsearch_node(node* root,char* name);
node* ssearch_node(node* root,char* name);
//Searches a node (a car) by a given name of model, returns adress of the node;
//Returns NULL if not found, or some problems occur. Case sensitive comparison.
int qtotal_number(node*root);
int stotal_number(node*root);
//Returns the total number of nodes in tree;
//Returns 0 if some problems happens during adding an adress into queue;
int qheight(node* root);
int sheight(node* root);
//Returns the height of the binary tree, -1 if root is NULL;
int qfree_memory(node** root);
int sfree_memory(node** root);
//frees memory ( the whole binary tree);
//-------------------------------------------------
//END OF FILE .

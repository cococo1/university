//Implementations for functions, declared in Chetrusca4.h
//Laboratory work 4, DSA, processing a Binary tree; work on a car database;
//Modified : 07/04/2011
//Author : Chetrusca Maxim

#include "Chetrusca4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//FUNCTIONS DEFINITIONS :
//-------------------------------------------------
int inq(elq **first,elq **last,node* new_element)
{
	elq *c=(elq*)malloc(sizeof(elq));
	if (!c) return 0;
	c->adress=new_element;
	c->next=NULL;
	if (!*first)*first=c;
	else (*last)->next=c;
	*last=c;
	return 1;
}
//-------------------------------------------------
node* delq(elq **first,elq **last)
{
	node* element=(*first)->adress;
	elq* c=*first;
	if (*first==*last)
	{
		*first=NULL;
		*last=NULL;
	}
	else(*first)=(*first)->next;
	free(c);
	return element;
}
//-------------------------------------------------
int push(els **top, node* adress)
{
	els *c;
	c=(els*)malloc(sizeof(els));
	if (!c) return 0;
	c->adress=adress;
	c->prev=*top;
	*top=c;
	return 1;
}
//-------------------------------------------------
node* pop(els**top)
{
	node* p=NULL;
	els *c=NULL;
	p=(*top)->adress;
	c=(*top);
	*top=(*top)->prev;
	free(c);
	return p;
}
//-------------------------------------------------
node* qcreate_a_tree(void)
{
	elq* first=NULL, *last=NULL ;
	node *root=NULL,*p=NULL,*some_node=NULL;
	int answer=0,i=1;
	puts("Do you want to create the root? (0/1)");
	fflush(stdin);
	scanf("%i",&answer);
	if (!answer) return NULL;
	root=(node*)malloc(sizeof(node));
	if (!root) return NULL;
	root->node_number=i;
	root->parent_adress=NULL;
	i++;
	if (!inq(&first,&last,root)) { free(root); return NULL;}
	while (first)
	{
		some_node=delq(&first,&last);
		printf("Do you want to create the left child of node %i ? (0/1) \n",some_node->node_number);
		fflush(stdin);
		scanf("%i",&answer);
		if (answer)
		{
			p=(node*)malloc(sizeof(node));
			if (!p) {some_node->left=NULL; some_node->right=NULL; return root;}
			p->node_number=i;
			p->parent_adress=some_node;
			i++;
			if (!inq(&first,&last,p)) {some_node->left=NULL; some_node->right=NULL; return root;}
			some_node->left=p;
		}
		else some_node->left=NULL;

		printf("Do you want to create the right child of node %i ? (0/1) \n",some_node->node_number);
		fflush(stdin);
		scanf("%i",&answer);
		if (answer)
		{
			p=(node*)malloc(sizeof(node));
			if (!p) { some_node->right=NULL; return root;}
			p->node_number=i; 
			p->parent_adress=some_node;
			i++;
			if (!inq(&first,&last,p)) { some_node->right=NULL; return root;}
			some_node->right=p;
		}
		else some_node->right=NULL;
	}
	return root;
}
//-------------------------------------------------
node* screate_a_tree(void)
{
	els *top=NULL;
	node *root=NULL,*p=NULL, *s=NULL;
	int answer=0,i=1;
	puts("Do you want to create the root? (0/1)");
	fflush(stdin);
	scanf("%i",&answer);
	if (!answer) return NULL;
	root=(node*)malloc(sizeof(node));
	if (!root) return NULL;
	/*puts("Give the number:");
	fflush(stdin);
	scanf("%i",&i);*/
	root->node_number=1;
	root->parent_adress=NULL;
	i++;
	if (!push(&top,root)) { free(root); return NULL; }
	while (top)
	{
		s=pop(&top);
		printf("Do you want to create the right child of node %i ? (0/1) \n",s->node_number);
		fflush(stdin);
		scanf("%i",&answer);
		if (answer)
		{
			p=(node*)malloc(sizeof(node));
			if (!p) {s->left=NULL; s->right=NULL; return root;}
			puts("Give the number of the node:");
			fflush(stdin);
			scanf("%i",&p->node_number);
			//p->node_number=i;
			p->parent_adress=s;
			//i++;
			if (!push(&top,p)) {s->left=NULL; s->right=NULL; return root;}
			s->right=p;
		}
		else s->right=NULL;

		printf("Do you want to create the left child of node %i ? (0/1) \n",s->node_number);
		fflush(stdin);
		scanf("%i",&answer);
		if (answer)
		{
			p=(node*)malloc(sizeof(node));
			if (!p) {s->left=NULL; return root;}
			puts("Give the number of the node:");
			fflush(stdin);
			scanf("%i",&p->node_number);
			//p->node_number=i;
			p->parent_adress=s;
			//i++;
			if (!push(&top,p)) {s->left=NULL; return root;}
			s->left=p;
		}
		else s->left=NULL;
	}
	return root;
}
//-------------------------------------------------
int sinput_tree(node *root)
{
	els *top=NULL;
	node* p=NULL, *s=NULL;
	if (!root) return 0;
	if (!push(&top,root)) return 0;
	while (top)
	{
		p=pop(&top);
		printf("Info about car %i : \n",p->node_number);
		puts("Give the name of the model:");
		fflush(stdin);
		scanf("%s",p->model);
		puts("Give the name of the country:");
		fflush(stdin);
		scanf("%s",p->country);
		puts("Give the year of manufacturing:");
		fflush(stdin);
		scanf("%i",&p->year);
		puts("Give the price in $:");
		fflush(stdin);
		scanf("%i",&p->price);
		puts("Give the capacity of engine:");
		fflush(stdin);
		scanf("%i",&p->capacity);
		s=p->right;
		if (s) if (!push(&top,s)) return 0;
		s=p->left;
		if (s) if (!push(&top,s)) return 0;
	}
	return 1;
	}


//-------------------------------------------------
int qinput_tree(node *root)
{
	elq *first=NULL, *last=NULL;
	node *p=NULL, *s=NULL;
	if (!root) return 0;
	if (!inq(&first,&last,root)) return 0;
	while (first)
	{
		p=delq(&first,&last);
		printf("Info about car %i : \n",p->node_number);
		puts("Give the name of the model:");
		fflush(stdin);
		scanf("%s",p->model);
		puts("Give the name of the country:");
		fflush(stdin);
		scanf("%s",p->country);
		puts("Give the year of manufacturing:");
		fflush(stdin);
		scanf("%i",&p->year);
		puts("Give the price in $:");
		fflush(stdin);
		scanf("%i",&p->price);
		puts("Give the capacity of engine:");
		fflush(stdin);
		scanf("%i",&p->capacity);
		s=p->left;
		if (s) if (!inq(&first,&last,s)) return 0;
		s=p->right;
		if (s) if (!inq(&first,&last,s)) return 0;
	}
	return 1;
}
//-------------------------------------------------
int soutput_tree(node* root)
{
	els *top=NULL;
	node *p=NULL,*s=NULL;
	if (!root) return 0;
	if (!push(&top,root)) return 0;
	while (top)
	{
		p=pop(&top);
		printf("Info about car %i : \n",p->node_number);
		printf("Model: %s  \n",p->model);
		printf("Country: %s  \n",p->country);
		printf("Year of manufacturing: %i  \n",p->year);
		printf("Price in $: %i  \n",p->price);
		printf("Capacity of engine: %i  \n",p->capacity);
		//printf("Adress of the parent : %p \n",p->parent_adress);
		printf("Adress of the left child : %p \n",p->left);
		printf("Adress of the right child : %p \n",p->right);
		s=p->right;
		if (s) if (!push(&top,s)) return 0;
		s=p->left;
		if (s) if (!push(&top,s)) return 0;
	}
	return 1;
}
//-------------------------------------------------
int qoutput_tree(node* root)
{
	elq* first=NULL, *last=NULL;
	node *p=NULL,*s=NULL;
	if (!root) return 0;
	if(!inq(&first,&last,root)) return 0;
	while (first)
	{
		p=delq(&first,&last);
		printf("Info about car %i : \n",p->node_number);
		printf("Model: %s  \n",p->model);
		printf("Country: %s  \n",p->country);
		printf("Year of manufacturing: %i  \n",p->year);
		printf("Price in $: %i  \n",p->price);
		printf("Capacity of engine: %i  \n",p->capacity);
		//printf("Adress of the parent : %p \n",p->parent_adress);
		printf("Adress of the left child : %p \n",p->left);
		printf("Adress of the right child : %p \n",p->right);
		s=p->left;
		if (s) if (!inq(&first,&last,s)) return 0;
		s=p->right;
		if (s) if (!inq(&first,&last,s)) return 0;
	}
	return 1;
}
//-------------------------------------------------
node* qsearch_node(node* root,char* name)
{
	elq *first=NULL, *last=NULL;
	node *p=NULL, *s=NULL;
	int k=1;
	if (!root) return NULL;
	if (!inq(&first,&last,root)) return NULL;
	while (first)
	{
		p=delq(&first,&last);
		k=strcmp(p->model,name);
		if (!k) return p;
		s=p->left;
		if (s) if (!inq(&first,&last,s)) return NULL;
		s=p->right;
		if (s) if (!inq(&first,&last,s)) return NULL;
	}
	return NULL;
}
//-------------------------------------------------
node* ssearch_node(node* root,char* name)
{
	els *top=NULL;
	node *p=NULL, *s=NULL;
	int k=1;
	if (!root) return NULL;
	if (!push(&top,root)) return NULL;
	while (top)
	{
		p=pop(&top);
		k=strcmp(p->model,name);
		if (!k) return p;
		s=p->right;
		if (s) if (!push(&top,s)) return NULL;
		s=p->left;
		if (s) if (!push(&top,s)) return NULL;
	}
	return NULL;

}
//-------------------------------------------------
int qtotal_number(node*root)
{
	elq *first=NULL, *last=NULL;
	node *p=NULL, *s=NULL;
	int n=0;
	if (!root) return 0;
	if (!inq(&first,&last,root)) return 0;
	while (first)
	{
		p=delq(&first,&last);
		n++;
		s=p->left;
		if (s) if (!inq(&first,&last,s)) return 0;
		s=p->right;
		if (s) if (!inq(&first,&last,s)) return 0;
	}
	return n;
}
//-------------------------------------------------
int stotal_number(node*root)
{
	
	els *top=NULL;
	node *p=NULL, *s=NULL;
	int n=0;
	if (!root) return 0;
	if (!push(&top,root)) return 0;
	while (top)
	{
		p=pop(&top);
		n++;
		s=p->right;
		if (s) if (!push(&top,s)) return 0;
		s=p->left;
		if (s) if (!push(&top,s)) return 0;
	}
	return n;
}
//-------------------------------------------------
int qfree_memory(node** root)
{
	elq *first=NULL, *last=NULL;
	node *p=NULL, *s=NULL;
	if (!*root) return 0;
	if (!inq(&first,&last,*root)) return 0;
	while (first)
	{
		p=delq(&first,&last);
		s=p->left;
		if (s) if (!inq(&first,&last,s)) return 0;
		s=p->right;
		if (s) if (!inq(&first,&last,s)) return 0;
		free(p);
		p=NULL;
	}
	*root=NULL;
	return 1;
}
//-------------------------------------------------
int sfree_memory(node** root)
{
	els *top=NULL;
	node *p=NULL, *s=NULL;
	if (!*root) return 0;
	if (!push(&top,*root)) return 0;
	while (top)
	{
		p=pop(&top);
		s=p->right;
		if (s) if (!push(&top,s)) return 0;
		s=p->left;
		if (s) if (!push(&top,s)) return 0;
		free(p);
		p=NULL;
	}
	*root=NULL;
	return 1;
}

//-------------------------------------------------
int qheight(node* root)
{
	elq* first=NULL, *last=NULL;
	node *p=NULL, *l=NULL, *r=NULL;
	int max=0,k=0;
	if (!root) return -1;
	if (!inq(&first,&last,root)) return -1;
	while (first)
	{
		p=delq(&first,&last);
		l=p->left;
		r=p->right;
		if (l) if (!inq(&first,&last,l)) return 0;
		if (r) if (!inq(&first,&last,r)) return 0;
		if (!l && !r) //=> p is a terminal node.
		{
			k=0;
			while (p!=root)
			{
				k++;
				p=p->parent_adress;
			}
			if (k>max) max=k;
		}
	}
	return max;
}
//-------------------------------------------------
int sheight(node* root)
{
	els* top=NULL;
	node *p=NULL, *l=NULL, *r=NULL;
	int max=0,k=0;
	if (!root) return -1;
	if (!push(&top,root)) return -1;
	while (top)
	{
		p=pop(&top);
		l=p->left;
		r=p->right;
		if (r) if (!push(&top,r)) return 0;
		if (l) if (!push(&top,l)) return 0;
		if (!l && !r) //=> p is a terminal node.
		{
			k=0;
			while (p!=root)
			{
				k++;
				p=p->parent_adress;
			}
			if (k>max) max=k;
		}
	}
	return max;
}
//-------------------------------------------------
//END OF FILE .

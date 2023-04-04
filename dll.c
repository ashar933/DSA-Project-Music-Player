#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
 
list_t* create_list()  // return a newly created empty doubly linked list
{
	// DO NOT MODIFY!!!
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

void insert_front(list_t* list, int data)  // TODO: inserts data to the beginning of the linked list
{  
   node_t* temp=(node_t*)malloc(sizeof(node_t));
   temp->data=data;
   temp->prev=temp->next=NULL;
   if (list->head==NULL){
	   list->head=temp;
	   list->size++;
   }
   else{
	   temp->next=list->head;
	   list->head->prev=temp;
	   list->head=temp;
	   list->size++;
   }
   node_t* cur=list->head;
   node_t* prev=NULL;
   while(cur!=NULL){
	   prev=cur;
	   cur=cur->next;
   }
   list->tail=prev;
}

void insert_back(list_t* list, int data) // TODO: inserts data to the end of the linked list
{  
   node_t* temp=(node_t*)malloc(sizeof(node_t));
   temp->data=data;
   temp->prev=temp->next=NULL;
   if (list->head==NULL){
	   list->head=temp;
	   list->tail=temp;
	   list->size++;
   }
   else{
	   node_t* cur=list->head;
	   node_t* prev=NULL;
	   while(cur!=NULL){
	   prev=cur;
	   cur=cur->next;
   }
       list->tail=prev;
	   list->tail->next=temp;
	   temp->prev=list->tail;
	   list->tail=temp;
	   list->size++;
   }
}

void insert_after(list_t* list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
   node_t* temp=(node_t*)malloc(sizeof(node_t));
   temp->data=data;
   temp->prev=temp->next=NULL;
   node_t* cur=search(list,prev);
   if (cur==NULL){
   return;}
   else{
	   if (cur->next!=NULL){
	   node_t* second=cur->next;
	   temp->next=second;
	   temp->prev=cur;
	   cur->next=temp;
	   second->prev=temp;
	   }
	   else{
		   cur->next=temp;
		   temp->prev=cur;
		   list->tail=temp;
	   }
 }
 list->size++;
 
} 


void delete_front(list_t* list) // TODO: delete the start node from the linked list.
{
	if (list->size==0){return;}
	else{
		node_t* cur=list->head;
		node_t* second=cur->next;
		if (second==NULL){
			list->head=list->tail=NULL;
			free(cur);
			cur=NULL;
		}
		else{
			list->head=second;
			second->prev=NULL;
			free(cur);
			cur=NULL;
		}
	}list->size--;   
}

void delete_back(list_t* list) // TODO: delete the end node from the linked list.
{if (list->size==0){return ;}
 else if(list->size==1){
	 list->head=list->tail=NULL;
 }
else{
	node_t* last=list->tail;
	node_t* seclast=last->prev;
	list->tail=seclast;
	seclast->next=NULL;
	free(last);
	last=NULL;
}list->size--;	 
 }


void delete_node(list_t* list, int data) // TODO: delete the node with “data” from the linked list.
{if (list->size==0){return ;}
 else{
	node_t* cur=search(list,data);
	if (cur==NULL){return ;}
	else{
		if (cur->prev==NULL){delete_front(list);}
		else if(cur->next==NULL){delete_back(list);}
		else{
			node_t* before =cur->prev;
			before->next=cur->next;
			cur->next->prev=before;
			free(cur);
			cur=NULL;
		}
	}
 }
}

node_t* search(list_t* list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{	node_t* found=list->head;
	while(found->data!=data && found!=NULL){
	found=found->next;
	}
	return found;
}

int is_empty(list_t* list) // return true or 1 if the list is empty; else returns false or 0
{
	// DO NOT MODIFY!!!
	return list->size == 0;
}

int size(list_t* list) // returns the number of nodes in the linked list.  
{
	// DO NOT MODIFY!!!
	return list->size;
}

void delete_nodes(node_t* head) // helper
{
	// DO NOT MODIFY!!!
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}

void delete_list(list_t* list) // free all the contents of the linked list
{
	// DO NOT MODIFY!!!
	delete_nodes(list->head);
	free(list);
}

void display_list(list_t* list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
	// DO NOT MODIFY!!!
	node_t* it = list->head;
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}


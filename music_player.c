#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t* create_playlist() // return a newly created doubly linked list
{
	// DO NOT MODIFY!!!
	playlist_t* playlist = (playlist_t*) malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}

void delete_playlist(playlist_t* playlist) // delete the playlist
{
	// DO NOT MODIFY!!!
	delete_list(playlist->list);
	free(playlist);
}

music_queue_t* create_music_queue() // return a newly created queue
{
	// DO NOT MODIFY!!!
	return create_queue();
}

void clear_music_queue(music_queue_t* q) // clear the queue q
{	
	// DO NOT MODIFY!!!
	delete_queue(q);
}

void add_song(playlist_t* playlist, int song_id, int where) // TODO: add a song id to the end of the playlist
{  
	song_t* temp=(song_t*)malloc(sizeof(song_t));
   	temp->data=song_id;
   	temp->prev=temp->next=NULL;
	if (where==-1)
	{
   
   		if (playlist->list->head==NULL)
		{
	   		playlist->list->head=temp;
	   	}
   		else
		{
	   		temp->next=playlist->list->head;
	   		playlist->list->head->prev=temp;
	   		playlist->list->head=temp;
   		}
   		song_t* cur=playlist->list->head;
   		song_t* prev=NULL;
   		while(cur!=NULL)
		{
	   		prev=cur;
	   		cur=cur->next;
   		}
   		playlist->list->tail=prev;
		playlist->list->size++;
		playlist->num_songs++;
		//printf("%d %d \n", playlist->list->size, playlist->num_songs);
   		return;
	}
   
   	else if(where==-2)
	{
   		if (playlist->list->head==NULL)
		{
			playlist->list->head=temp;
			playlist->list->tail=temp;
	    	playlist->list->size++;
	    	playlist->num_songs++;
	    	return ;
   		}
   		else
		{
			playlist->list->tail->next=temp;
	    	temp->prev=playlist->list->tail;
		    playlist->list->tail=temp;
	    	playlist->list->size++;
		    playlist->num_songs++;
	       	return;
    	}	
	}
	
	else if(where>0)
	{		
		song_t* cur=search_song(playlist,where);
		if (cur==NULL)
		{
			return;
		}
		else
		{
			if (cur->next!=NULL)
			{
				song_t* second=cur->next;
				temp->next=second;
				temp->prev=cur;
				cur->next=temp;
				second->prev=temp;
			}
			else
			{
				cur->next=temp;
				temp->prev=cur;
				playlist->list->tail=temp;
			}
		}
		playlist->list->size++;
		playlist->num_songs++;
		return ;
	}
	else
		return ;
}

void delete_song(playlist_t* playlist, int song_id) // TODO: remove song id from the playlist
{
	if (playlist->list->size==0)
	{
		return;
	}
	else
	{
		song_t* cur=search_song(playlist,song_id);
		if (cur==NULL)
		{
			return;
		}
		else
		{
			if (playlist->last_song==cur)
				playlist->last_song=NULL;
			else if (cur->prev==NULL)
			{
				song_t* cur=playlist->list->head;
				if (playlist->list->size==1)
				{
					playlist->list->head=playlist->list->tail=NULL;
					free(cur);
					cur=NULL;
				}
				else
				{
					playlist->list->head=cur->next;
					cur->next->prev=NULL;
					free(cur);
					cur=NULL;
				}
			}
			else if(cur->next==NULL)
			{	
				if(playlist->list->size==1)
				{
				    playlist->list->head=playlist->list->tail=NULL;
				    free(cur);
					cur=NULL;
				}
				else
				{
					song_t* last=playlist->list->tail;
					song_t* seclast=last->prev;
					playlist->list->tail=seclast;
					seclast->next=NULL;
					free(last);
					last=NULL;
				}	
			}
			else
			{
				song_t* before = cur->prev;
				before->next=cur->next;
				cur->next->prev=before;
				free(cur);
				cur=NULL;
			}
		}
		playlist->list->size--;  
		playlist->num_songs--;
		
		return ;
	}
}

song_t* search_song(playlist_t* playlist, int song_id) // TODO: return a pointer to the node where the song id is present in the playlist
{
	song_t* found=playlist->list->head;
	while(found!=NULL)
	{
		if(found->data==song_id)
			return found;
		found=found->next;
	}
	return NULL;
}

void search_and_play(playlist_t* playlist, int song_id) // TODO: play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
	song_t* cur=search_song(playlist,song_id);
	playlist->last_song=cur;
	if (cur==NULL)
		return;
	play_song(song_id);
	return ;
}

void play_next(playlist_t* playlist, music_queue_t* q) // TODO: play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
	if (q->front==NULL)
	{
		if (playlist->last_song==NULL || playlist->last_song->next==NULL)
		{
			playlist->last_song=playlist->list->head;
			play_song(playlist->last_song->data);
		}
		else
		{
			playlist->last_song=playlist->last_song->next;
			play_song(playlist->last_song->data);
		}
		return;   
	}
	else if(q->front!=NULL)
	{
		int x=dequeue(q);
		play_song(x);
		return ;
	}
	else
		return ;
}

void play_previous(playlist_t* playlist) // TODO: play the previous song from the linked list
{
	if(playlist->list->head!=NULL)
	{
		if (playlist->last_song==NULL || playlist->last_song->prev==NULL)
		{
			playlist->last_song=playlist->list->tail;
			play_song(playlist->last_song->data);
		}
		else
		{
			playlist->last_song=playlist->last_song->prev;
			play_song(playlist->last_song->data);
		}
		return ;
	}
	else
		return ;
	
	
}

void play_from_queue(music_queue_t* q) // TODO: play a song from the queue
{
	int x=dequeue(q);
	play_song(x);
}

void insert_to_queue(music_queue_t* q, int song_id) // TODO: insert a song id to the queue
{
	enqueue(q,song_id);
}

void reverse(playlist_t* playlist) // TODO: reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
	if (playlist->list->head==NULL)
		return;
	else
	{
		song_t* temp=playlist->list->head;
		song_t* tempo=NULL;
		song_t* cur=temp;
		song_t* prevn=NULL;
		
		while(temp->next!=NULL)
		{
			cur=temp->next;
			temp->next=temp->prev;
			temp->prev=cur;
			prevn=temp;
			temp=cur;
			cur=cur->next;	
		}
		temp->next=prevn;
		temp->prev=NULL;
		
		tempo=playlist->list->head;
		playlist->list->head=playlist->list->tail;
		playlist->list->tail=tempo;
		return;
	}
}

void k_swap(playlist_t* playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{
	if(playlist->list->size!=0){
	int n=playlist->num_songs;
	int i=0;
	song_t* temp=playlist->list->head;
	song_t* cur= playlist->list->head;
	for (i=0;i+k<n;i++)
	{
		cur=temp;
		for(int y=0; y<k; y++)
		{
			cur=cur->next;
		}
		song_t* curn= cur->next;
		song_t* tempp=temp->prev;
		song_t* curp= cur->prev;
		song_t* tempn=temp->next;
		if(k==1)
		{
			curp=cur;
			tempn=temp;
		}
		cur->next=tempn;
		cur->prev=tempp;
		temp->next=curn;
		temp->prev=curp;
		if (tempn!=NULL)
			tempn->prev=cur;
		if (curn!=NULL)
			curn->prev=temp;
		if (curp!=NULL)
			curp->next=temp;
		
		if (temp==playlist->list->head)
		{
			playlist->list->head=cur;	
		}
		else
		{
			tempp->next=cur;
		}
		temp=tempn;
	}
   
    song_t* last=playlist->list->head;
    while(last->next!=NULL)
	{
	    last=last->next;
    }
    playlist->list->tail=last;
}}

void shuffle(playlist_t* playlist, int k) // TODO: perform k_swap and reverse
{
	k_swap(playlist,k);
	reverse(playlist);
}

song_t* debug(playlist_t* playlist) // TODO: if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
	song_t* cur=playlist->list->tail->next;
	return cur;
}

void display_playlist(playlist_t* p) // Displays the playlist
{
	// DO NOT MODIFY!!!
	display_list(p->list);
}

void play_song(int song_id)
{
	// DO NOT MODIFY!!!
	printf("Playing: %d\n", song_id);
}


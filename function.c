#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

SnakeCell *AddRectangle(Snake *snake, SDL_Rect rec)
{
	/*Initialisation de la nouvelle cellule*/

	SnakeCell *newrect=malloc(sizeof(SnakeCell));
	newrect->rectangle=rec;
	newrect->next=NULL;

	/*Ajout du rectangle*/

	if(Snake->length<3){
		if 
	}

	SnakeCell *current=snake;
	while (current->next!=NULL){
		current=current->next;
	}
	current->next=newrect;
	newrect=
}
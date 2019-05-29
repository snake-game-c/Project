#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

SnakeCell *AddRectangle(Snake *snake)
{
	/*Initialisation de la nouvelle cellule*/

	SDL_Rect *rec=malloc(sizeof(SDL_Rect));
	rec->w=COTE;
	rec->h=COTE;

	SnakeCell *newrect=malloc(sizeof(SnakeCell));
	newrect->rectangle=rec;
	newrect->next=NULL;

	/*------------------------------------*/

	/*--------Ajout du rectangle----------*/

	SnakeCell *current=snake->head; 

	//On atteint le pointeur de la dernière cellule
	while (current->next!=NULL){
		current=current->next;
	}

	//On part du point d'origine du dernier rectangle
	rec->x=current->rectangle->x;
	rec->y=current->rectangle->y;

	/*On adapte le point de rec suivant la direction de la dernière cellule*/

	if (current->direction==NORTH){
	    rec->x+=COTE;
	}
	else if (current->direction==EAST){
		rec->y-=COTE;
	}
	else if (current->direction==WEST){
		rec->y+=COTE;
	}
	else if (current->direction==SOUTH){
		rec->x-=COTE;
	}

	//On oublie pas de donner la même direction au rectangle qu'on vient d'ajouter

	newrect->direction=current->direction;
	current->next=newrect;

	/*------------------------------------*/

	return snake;
}
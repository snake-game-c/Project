#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

Snake *AddRectangle(Snake *snake)
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
	
	snake->length++;
	return snake;
}

Snake *MoveSnake(Snake *snake,int dir)
{	
	SnakeCell *current=snake->head;
	//mise a jour de la tete
	if (dir==NORTH){
		current->rectangle->x-=COTE;
		current->direction=dir;
	}
	else if (dir==EAST){
		current->rectangle->y+=COTE;
		current->direction=dir;
	}
	else if (dir==WEST){
		current->rectangle->y-=COTE;
		current->direction=dir;
	}
	else if (dir==SOUTH){
		current->rectangle->x+=COTE;
		current->direction=dir;
	}
	SnakeCell *previous=current;
	current=current->next;
	int dirtempprev=previous->direction;
	int dirtempnext;
	// modification de la position du rectangle actuel selon sa direction
	// et modification de sa direction par la direction du rectangle precedent
	while (current!=NULL){
			dirtempnext=current->direction;
		if (current->direction==NORTH){
			current->rectangle->x-=COTE;
			current->direction=dirtempprev;
		}
		else if (current->direction==EAST){
			current->rectangle->y+=COTE;
			current->direction=dirtempprev;
		}
		else if (current->direction==WEST){
			current->rectangle->y-=COTE;
			current->direction=dirtempprev;
		}
		else if (current->direction==SOUTH){
			current->rectangle->x+=COTE;
			current->direction=dirtempprev;
		}
		dirtempprev=dirtempnext;
		current=current->next;
	}
	return snake;
}

void PrintSnakeConsole(Snake *snake)
{
	SnakeCell *current=snake->head;
	int Case=0;
	while(current!=NULL){
		printf("Case %d : \n",Case);
		Case++;
		printf("\tCoordonnees du point d origine (%d,%d)\n",current->rectangle->x,current->rectangle->y);
		printf("\tDirection %d\n",current->direction);
		current=current->next;
	}
}

Snake *InitialiseSnake(int x1, int y1, int dir)
{
	SnakeCell *tete=malloc(sizeof(SnakeCell));
	SDL_Rect *rec=malloc(sizeof(SDL_Rect));
	tete ->rectangle=rec;
	tete->rectangle->x=x1;
	tete->rectangle->y=y1;
	tete->rectangle->w=COTE;
	tete->rectangle->h=COTE;

	tete->direction=dir;
	tete->next=NULL;

	Snake *snake=malloc(sizeof(Snake));
	snake->head=tete;
	snake->length=1;

	return snake;
}

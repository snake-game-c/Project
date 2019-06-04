#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	    rec->y+=COTE;
	}
	else if (current->direction==EAST){
		rec->x-=COTE;
	}
	else if (current->direction==WEST){
		rec->x+=COTE;
	}
	else if (current->direction==SOUTH){
		rec->y-=COTE;
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
		current->rectangle->y-=COTE;
		current->direction=dir;
	}
	else if (dir==EAST){
		current->rectangle->x+=COTE;
		current->direction=dir;
	}
	else if (dir==WEST){
		current->rectangle->x-=COTE;
		current->direction=dir;
	}
	else if (dir==SOUTH){
		current->rectangle->y+=COTE;
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
			current->rectangle->y-=COTE;
			current->direction=dirtempprev;
		}
		else if (current->direction==EAST){
			current->rectangle->x+=COTE;
			current->direction=dirtempprev;
		}
		else if (current->direction==WEST){
			current->rectangle->x-=COTE;
			current->direction=dirtempprev;
		}
		else if (current->direction==SOUTH){
			current->rectangle->y+=COTE;
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

void PrintSnake(Snake *snake, SDL_Renderer *renderer){

	 SnakeCell *current=snake->head;

	 while(current!=NULL){
	 	SDL_RenderFillRect(renderer,current->rectangle);
	 	current=current->next;
	 }

	 SDL_RenderPresent(renderer);
}

SDL_bool EndGame(Snake *snake){    //Indique si le jeu est fini ou non

	int x_current;
	int y_current;

	int x_head=snake->head->rectangle->x;
	int y_head=snake->head->rectangle->y;

	/* Si le snake depasse les dimensions de la fenetre*/
	if (x_head<=0 || x_head>=WIDTH ||y_head<=0 || y_head>=HEIGHT){
		return SDL_TRUE;
	}
	else{
		SnakeCell *current=snake->head;

		while(current!=NULL){
			x_current=current->rectangle->x;
			y_current=current->rectangle->y;
			if ((x_head<=x_current+COTE || x_head>=x_current)&&(y_head<=y_current+COTE || y_head>=y_current)){
				return SDL_TRUE;
			}
			current=current->next;
		}
	}
	return SDL_FALSE;

}

SDL_bool IsInsideSnake(int x1, int y1, Snake *snake){
	SnakeCell *current=snake->head;
	int x_current;
	int y_current;
		while(current!=NULL){
			x_current=current->rectangle->x;
			y_current=current->rectangle->y;
			if ((x1<=x_current+COTE || x1>=x_current)&&(y1<=y_current+COTE || y1>=y_current)){
				return SDL_TRUE;
			}
			current=current->next;
		}
	return SDL_FALSE;

}

void Pop_Bonus(Snake *snake, SDL_Renderer *renderer,int *x_bonus,int *y_bonus){
	 *x_bonus=(rand()%(WIDTH/COTE-1))*COTE;
	 *y_bonus=(rand()%(HEIGHT/COTE-1))*COTE;

	 while(IsInsideSnake(*x_bonus,*y_bonus,snake)){
	 		*x_bonus=(rand()%(WIDTH/COTE-1))*COTE;
	 		*y_bonus=(rand()%(HEIGHT/COTE-1))*COTE;
	 }

}



/*void Game(void){
	InitialiseSnake()
}*/
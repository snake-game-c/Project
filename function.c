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

Snake *MoveSnake(Snake *snake,int dir,SDL_Renderer *renderer)
{	
	SnakeCell *current=snake->head;
	//mise a jour de la tete
	if (dir==NORTH){
		MoveSnake30FPS(snake,current->rectangle,NORTH,renderer);
		current->direction=dir;
	}
	else if (dir==EAST){
		MoveSnake30FPS(snake,current->rectangle,EAST,renderer);
		current->direction=dir;
	}
	else if (dir==WEST){
		MoveSnake30FPS(snake,current->rectangle,WEST,renderer);
		current->direction=dir;
	}
	else if (dir==SOUTH){
		MoveSnake30FPS(snake,current->rectangle,SOUTH,renderer);
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
			MoveSnake30FPS(snake,current->rectangle,NORTH,renderer);
			current->direction=dirtempprev;
		}
		else if (current->direction==EAST){
			MoveSnake30FPS(snake,current->rectangle,EAST,renderer);
			current->direction=dirtempprev;
		}
		else if (current->direction==WEST){
			MoveSnake30FPS(snake,current->rectangle,WEST,renderer);
			current->direction=dirtempprev;
		}
		else if (current->direction==SOUTH){
			MoveSnake30FPS(snake,current->rectangle,SOUTH,renderer);
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

	SDL_SetRenderDrawColor(renderer,255,255,255,255); //blanc

	 SnakeCell *current=snake->head;

	 while(current!=NULL){
	 	SDL_RenderFillRect(renderer,current->rectangle);
	 	current=current->next;
	 }

	 SDL_SetRenderDrawColor(renderer,0,0,0,255);//noir

	 SDL_RenderPresent(renderer);
}

SDL_bool EndGame(Snake *snake){    //Indique si le jeu est fini ou non

	int x_current;
	int y_current;

	int x_head=snake->head->rectangle->x;
	int y_head=snake->head->rectangle->y;

	/* Si le snake depasse les dimensions de la fenetre*/
	if (x_head<0 || x_head>WIDTH ||y_head<0 || y_head>HEIGHT){
		return SDL_TRUE;
	}
	else{
		SnakeCell *current=snake->head->next;
		
		while(current!=NULL){
			x_current=current->rectangle->x;
			y_current=current->rectangle->y;
			if ((x_head<=x_current+COTE && x_head>=x_current)&&(y_head<=y_current+COTE && y_head>=y_current)){
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
			if ((x1<=x_current+COTE && x1>=x_current)&&(y1<=y_current+COTE && y1>=y_current)){
				return SDL_TRUE;
			}
			current=current->next;
		}
	return SDL_FALSE;

}

void Pop_Bonus(Snake *snake, SDL_Renderer *renderer,int *x_bonus,int *y_bonus){

	SDL_SetRenderDrawColor(renderer,255,255,255,255); //blanc
	 *x_bonus=(rand()%(WIDTH/COTE-1))*COTE;
	 *y_bonus=(rand()%(HEIGHT/COTE-1))*COTE;

	 printf("x %d\n",*x_bonus);
	 printf("y %d\n",*y_bonus);

	 while(IsInsideSnake(*x_bonus,*y_bonus,snake)){
	 		*x_bonus=(rand()%(WIDTH/COTE-1))*COTE;
	 		*y_bonus=(rand()%(HEIGHT/COTE-1))*COTE;
	 		printf("x in while %d\n",*x_bonus);
	 		printf("y in while %d\n",*y_bonus);
	 }

	 SDL_Rect bonus;
	 bonus.x=*x_bonus;
	 bonus.y=*y_bonus;
	 printf("x after while%d\n",*x_bonus);
	 printf("y after while%d\n",*y_bonus);
	 bonus.w=COTE;
	 bonus.h=COTE;
	 SDL_RenderFillRect(renderer,&bonus);
	 SDL_SetRenderDrawColor(renderer,0,0,0,255); //retourne en noir

}

void MoveSnake30FPS(Snake *snake,SDL_Rect *rectangle, int dir,SDL_Renderer *renderer){
	int i;
	int current_time;
	int previous_time=0;

	if (dir==NORTH){
		i=rectangle->y;
		while(rectangle->y>i-COTE){
			rectangle->y--;
			current_time=SDL_GetTicks();
			if (current_time-previous_time>30){
				PrintSnake(snake,renderer);
				previous_time=current_time;
			}else{
				SDL_Delay(30-(current_time-previous_time));
			}
		}
	}
	if (dir==EAST){
		i=rectangle->x;
		while(rectangle->x<i+COTE){
			rectangle->x++;
			current_time=SDL_GetTicks();
			if (current_time-previous_time>30){
				PrintSnake(snake,renderer);
				previous_time=current_time;
			}else{
				SDL_Delay(30-(current_time-previous_time));
			}
		}
	}
	if (dir==WEST){
		i=rectangle->x;
		while(rectangle->x>i-COTE){
			rectangle->x--;
			current_time=SDL_GetTicks();
			if (current_time-previous_time>30){
				PrintSnake(snake,renderer);
				previous_time=current_time;
			}else{
				SDL_Delay(30-(current_time-previous_time));
			}
		}
	}
	if (dir==SOUTH){
		i=rectangle->y;
		while(rectangle->y<i+COTE){
			rectangle->y++;
			current_time=SDL_GetTicks();
			if (current_time-previous_time>30){
				PrintSnake(snake,renderer);
				previous_time=current_time;
			}else{
				SDL_Delay(30-(current_time-previous_time));
			}
		}
	}
}


//void Game(Snake *snake, SDL_Renderer *renderer,int *x_bonus, int *y_bonus){
//	Pop_Bonus(snake,renderer,x_bonus,y_bonus); 	//Fait apparaitre un bonus sur l'ecran
//	PrintSnake(snake,renderer); //Affiche le snake
//
//	while(EndGame(snake)==SDL_FALSE){
//		SDL_Event event;
//		while(SDL_PollEvent(&event)){
//			switch(event.type){    //En fonction de l'evenement 
//
//				case SDL_KEYDOWN:  //Une touche est pressee
//					switch(event.key.keysym.sym){  //En fonction de la touche pressee
//
//						case SDLK_LEFT: 
//							/*Action a faire si la touche gauche est pressee*/
//							printf("LEFT\n");
//							SDL_RenderClear(renderer);
//							MoveSnake(snake,EAST,renderer);
//							break;
//
//						case SDLK_RIGHT: 
//							/*Action a faire si la touche droite est pressee*/
//							printf("RIGHT\n");
///							SDL_RenderClear(renderer);
	//						MoveSnake(snake,WEST,renderer);
//							break;
//
//						case SDLK_UP:
//							/*Action a faire si la touche haute est pressee*/ 
///							printf("UP\n");
	//						SDL_RenderClear(renderer);
	//						MoveSnake(snake,NORTH,renderer);
//							break;
//					
//						case SDLK_DOWN: 
//							/*Action a faire si la touche basse est pressee*/
//							printf("DOWN\n");
//							SDL_RenderClear(renderer);
//							MoveSnake(snake,SOUTH,renderer);
//							break;
//
//						default:
//							SDL_RenderClear(renderer);
//							MoveSnake(snake,snake->head->direction,renderer);
//							break;
//					}
//					break;
//
//				default:
//					break;
//			}
//		}
//
//		if (IsInsideSnake(*x_bonus,*y_bonus,snake)){
//			AddRectangle(snake);
//			SDL_RenderClear(renderer);
//			Pop_Bonus(snake,renderer,x_bonus,y_bonus);
//			PrintSnake(snake,renderer);
//		}
//	}
//}*/

void PrintSquare(SDL_Renderer *renderer,int x1, int y1){
	SDL_SetRenderDrawColor(renderer,255,255,255,255); //blanc
	SDL_Rect rect={x1,y1,COTE,COTE};
	SDL_RenderFillRect(renderer,&rect);
	SDL_SetRenderDrawColor(renderer,0,0,0,255); //blanc
}
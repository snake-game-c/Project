#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "function.h"

void MoveSnake(Snake *snake,int dir, SDL_Renderer *renderer)
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
	PrintSnake(snake,renderer);
}

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

Snake *MoveSnake2(Snake *snake,int dir,SDL_Renderer *renderer)
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
		printf("x_head %d\n",x_head);
		printf("y_head %d\n",y_head);
		return SDL_TRUE;
	}
	else{
		SnakeCell *current=snake->head->next;
		int pos=0; /*numero de la position de current, avec 0 la premiere position*/		
		
		while(current!=NULL){
			x_current=current->rectangle->x;
			y_current=current->rectangle->y;
			/*Cas ou la longueur du serpent est superieur a 2 : la tete a un bord commun avec le suivant*/
			if (pos<=1){
				pos++;
				current=current->next;
			}else{
				if ((x_head<=x_current+COTE && x_head>=x_current)&&(y_head<=y_current+COTE && y_head>=y_current)){
					printf("test de la tete sur le serpent\n");
					return SDL_TRUE;
				}
				pos++;
				current=current->next;
			}
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
	 //printf("x after while%d\n",*x_bonus);
	 //printf("y after while%d\n",*y_bonus);
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
//							SDL_RenderClear(renderer);
//							MoveSnake(snake,WEST,renderer);
//							break;
//
//						case SDLK_UP:
//							/*Action a faire si la touche haute est pressee*/ 
//							printf("UP\n");
//							SDL_RenderClear(renderer);
//							MoveSnake(snake,NORTH,renderer);
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

/*-------------------------------------Fonctions d'affichage-------------------------------------*/

void one(SDL_Renderer *renderer,int x1, int y1){  //affiche le nombre 1 (x1 et y1 sont les coordonnees du carre en haut a gauche du chiffre)
	PrintSquare(renderer,x1,y1);
	PrintSquare(renderer,x1,y1+COTE);
	PrintSquare(renderer,x1,y1+2*COTE);
	PrintSquare(renderer,x1,y1+3*COTE);
	PrintSquare(renderer,x1,y1+4*COTE);
	SDL_RenderPresent(renderer);
}

void two(SDL_Renderer *renderer,int x1, int y1){
	PrintSquare(renderer,x1,y1);
	PrintSquare(renderer,x1+COTE,y1);
	PrintSquare(renderer,x1+2*COTE,y1);
	PrintSquare(renderer,x1+2*COTE,y1+COTE);
	PrintSquare(renderer,x1+2*COTE,y1+2*COTE);
	PrintSquare(renderer,x1+COTE,y1+2*COTE);
	PrintSquare(renderer,x1,y1+2*COTE);
	PrintSquare(renderer,x1,y1+3*COTE);
	PrintSquare(renderer,x1,y1+4*COTE);
	PrintSquare(renderer,x1+COTE,y1+4*COTE);
	PrintSquare(renderer,x1+2*COTE,y1+4*COTE);
	SDL_RenderPresent(renderer);
}

void three(SDL_Renderer *renderer,int x1, int y1){
	PrintSquare(renderer,x1,y1);
	PrintSquare(renderer,x1+COTE,y1);
	PrintSquare(renderer,x1+2*COTE,y1);
	PrintSquare(renderer,x1+2*COTE,y1+COTE);
	PrintSquare(renderer,x1+2*COTE,y1+2*COTE);
	PrintSquare(renderer,x1+COTE,y1+2*COTE);
	PrintSquare(renderer,x1,y1+2*COTE);
	PrintSquare(renderer,x1+2*COTE,y1+3*COTE);
	PrintSquare(renderer,x1,y1+4*COTE);
	PrintSquare(renderer,x1+COTE,y1+4*COTE);
	PrintSquare(renderer,x1+2*COTE,y1+4*COTE);
	SDL_RenderPresent(renderer);
}

void four(SDL_Renderer *renderer,int x1, int y1){
	PrintSquare(renderer,x1,y1);
	PrintSquare(renderer,x1+2*COTE,y1);
	PrintSquare(renderer,x1,y1+COTE);
	PrintSquare(renderer,x1+2*COTE,y1+COTE);
	PrintSquare(renderer,x1+2*COTE,y1+2*COTE);
	PrintSquare(renderer,x1+COTE,y1+2*COTE);
	PrintSquare(renderer,x1,y1+2*COTE);
	PrintSquare(renderer,x1+2*COTE,y1+3*COTE);
	PrintSquare(renderer,x1+2*COTE,y1+4*COTE);
	SDL_RenderPresent(renderer);
}

void five(SDL_Renderer *renderer,int x1,int y1){
	PrintSquare(renderer,x1,y1);
	PrintSquare(renderer,x1+COTE,y1);
	PrintSquare(renderer,x1+2*COTE,y1);
	PrintSquare(renderer,x1,y1+COTE);
	PrintSquare(renderer,x1+2*COTE,y1+2*COTE);
	PrintSquare(renderer,x1+COTE,y1+2*COTE);
	PrintSquare(renderer,x1,y1+2*COTE);
	PrintSquare(renderer,x1+2*COTE,y1+3*COTE);
	PrintSquare(renderer,x1,y1+4*COTE);
	PrintSquare(renderer,x1+COTE,y1+4*COTE);
	PrintSquare(renderer,x1+2*COTE,y1+4*COTE);
	SDL_RenderPresent(renderer);
}

void six(SDL_Renderer *renderer,int x1,int y1){
	five(renderer,x1,y1);
	PrintSquare(renderer,x1,y1+3*COTE);
	SDL_RenderPresent(renderer);
}

void seven(SDL_Renderer *renderer,int x1,int y1){
	PrintSquare(renderer,x1,y1);
	PrintSquare(renderer,x1+COTE,y1);
	one(renderer,x1+2*COTE,y1);
	SDL_RenderPresent(renderer);
}

void eight(SDL_Renderer *renderer,int x1,int y1){
	two(renderer,x1,y1);
	PrintSquare(renderer,x1,y1+COTE);
	PrintSquare(renderer,x1+2*COTE,y1+3*COTE);
	SDL_RenderPresent(renderer);
}

void nine(SDL_Renderer *renderer,int x1,int y1){
	three(renderer,x1,y1);
	PrintSquare(renderer,x1,y1+COTE);
	SDL_RenderPresent(renderer);
}

void zero(SDL_Renderer *renderer,int x1,int y1){
	one(renderer,x1,y1);
	one(renderer,x1+2*COTE,y1);
	PrintSquare(renderer,x1+COTE,y1);
	PrintSquare(renderer,x1+COTE,y1+4*COTE);
	SDL_RenderPresent(renderer);
}

void PrintScore(Snake *snake, SDL_Renderer *rendu, int x1, int y1){
	int score=snake->length;
	int unite=score%10;
	int dizaine=score/10;
	int centaine=score/100;

	switch(centaine){
		case 0:
			break;
		case 1:
			one(rendu,x1,y1);
			break;
		case 2:
			two(rendu,x1,y1);
			break;
		case 3:
			three(rendu,x1,y1);
			break;
		case 4:
			four(rendu,x1,y1);
			break;
		case 5:
			five(rendu,x1,y1);
			break;
		case 6:
			six(rendu,x1,y1);
			break;
		case 7:
			seven(rendu,x1,y1);
			break;
		case 8:
			eight(rendu,x1,y1);
			break;
		case 9:
			nine(rendu,x1,y1);
			break;
		default:
			break;
	}

	switch(dizaine){
		case 0:
			zero(rendu,x1+4*COTE,y1);
			break;
		case 1:
			one(rendu,x1+4*COTE,y1);
			break;
		case 2:
			two(rendu,x1+4*COTE,y1);
			break;
		case 3:
			three(rendu,x1+4*COTE,y1);
			break;
		case 4:
			four(rendu,x1+4*COTE,y1);
			break;
		case 5:
			five(rendu,x1+4*COTE,y1);;
			break;
		case 6:
			six(rendu,x1+4*COTE,y1);
			break;
		case 7:
			seven(rendu,x1+4*COTE,y1);
			break;
		case 8:
			eight(rendu,x1+4*COTE,y1);
			break;
		case 9:
			nine(rendu,x1+4*COTE,y1);
			break;
		default:
			break;
	}

	switch(unite){
		case 0:
			zero(rendu,x1+8*COTE,y1);
			break;
		case 1:
			one(rendu,x1+8*COTE,y1);
			break;
		case 2:
			two(rendu,x1+8*COTE,y1);
			break;
		case 3:
			three(rendu,x1+8*COTE,y1);
			break;
		case 4:
			four(rendu,x1+8*COTE,y1);
			break;
		case 5:
			five(rendu,x1+8*COTE,y1);;
			break;
		case 6:
			six(rendu,x1+8*COTE,y1);
			break;
		case 7:
			seven(rendu,x1+8*COTE,y1);
			break;
		case 8:
			eight(rendu,x1+8*COTE,y1);
			break;
		case 9:
			nine(rendu,x1+8*COTE,y1);
			break;
		default:
			break;
	}

}
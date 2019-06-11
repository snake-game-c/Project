#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "function.h"


// linux gcc main.c function.c $(sdl2-config --cflags --libs) -o snake
// Windows gcc -Wall src/Project/main.c src/Project/function.c -o bin/Snake -I include -L lib -lmingw32 -lSDL2main -lSDL2

void ExitWithError(char *message)
{
	SDL_Log("ERREUR %s -> %s", message,SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{	
	srand(time(NULL));
	/*--------Initialisation de la fenêtre et du rendu--------*/

	SDL_Window *fenetre=NULL;
	SDL_Renderer *rendu=NULL; 
	srand(time(NULL));

	
	/*-----------Initilisation de la SDL-----------*/

	if (SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ExitWithError("Impossible de charger la SDL");
	}

	/*-----------FENETRE-----------*/

	fenetre=SDL_CreateWindow("Jeu du Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,HEIGHT,WIDTH,0);

	if(fenetre==NULL){
		ExitWithError("Impossible de créer une fenetre");
	} 

	/*-----------RENDU-----------*/

	rendu=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);

	if (rendu==NULL){
		SDL_DestroyWindow(fenetre);
		ExitWithError("Impossible de créer un rendu");

	}

	SDL_SetRenderDrawColor(rendu,255,255,255,255);
	

	/*Initialisation du Snake*/
	Snake *snake=InitialiseSnake(90,90,EAST); /*Initialisation avec un multiple de COTE*/
	/*----------------------*/

	/*Definition des variables de jeu*/
	int x_bonus;
	int y_bonus;

	//printf("1\n");
	Pop_Bonus(snake,rendu,&x_bonus,&y_bonus); 	//Fait apparaitre un bonus sur l'ecran
	//printf("2\n");
	PrintSnake(snake,rendu); //Affiche le snake
	//printf("3\n");
	/*----------------------*/

	/*Gestion des evenements*/

	SDL_bool program_launched=SDL_TRUE;

	int current_time;
	int previous_time=0;

	while(program_launched){
		SDL_Event event;
		SDL_bool key_pressed=SDL_FALSE;

		if(EndGame(snake)==SDL_FALSE){
			current_time=SDL_GetTicks();

			while(SDL_PollEvent(&event)){
				switch(event.type){    //En fonction de l'evenement 

					case SDL_QUIT:
						program_launched=SDL_FALSE;
						break;

					case SDL_KEYDOWN:  //Une touche est pressee
						switch(event.key.keysym.sym){  //En fonction de la touche pressee

							case SDLK_LEFT: 
							/*Action a faire si la touche gauche est pressee*/
								printf("LEFT\n");
								SDL_RenderClear(rendu);
								PrintSquare(rendu, x_bonus, y_bonus);
								MoveSnake(snake,WEST,rendu);
								key_pressed=SDL_TRUE;
								//PrintSnakeConsole(snake);
								break;

							case SDLK_RIGHT: 
							/*Action a faire si la touche droite est pressee*/
								printf("RIGHT\n");
								SDL_RenderClear(rendu);
								PrintSquare(rendu, x_bonus, y_bonus);
								MoveSnake(snake,EAST,rendu);
								key_pressed=SDL_TRUE;
								//PrintSnakeConsole(snake);
								break;

							case SDLK_UP:
							/*Action a faire si la touche haute est pressee*/ 
								printf("UP\n");
								SDL_RenderClear(rendu);
								PrintSquare(rendu, x_bonus, y_bonus);
								MoveSnake(snake,NORTH,rendu);
								key_pressed=SDL_TRUE;
								//PrintSnakeConsole(snake);
								break;
					
							case SDLK_DOWN: 
							/*Action a faire si la touche basse est pressee*/
								printf("DOWN\n");
								SDL_RenderClear(rendu);
								PrintSquare(rendu, x_bonus, y_bonus);
								MoveSnake(snake,SOUTH,rendu);
								key_pressed=SDL_TRUE;
								//PrintSnakeConsole(snake);
								break;

							case SDLK_ESCAPE:
								program_launched=SDL_FALSE;
								break;

							default:
								break;
						}
						break;

					default:
						//PrintSnakeConsole(snake);
						break;
				
				}
			}
			if (key_pressed!=SDL_TRUE){

	 			if(current_time-previous_time>300){
	 			previous_time=current_time;
	 			SDL_RenderClear(rendu);
				PrintSquare(rendu,x_bonus,y_bonus);
	 			MoveSnake(snake, snake->head->direction,rendu);
	 			}
			//PrintSnakeConsole(snake);
			key_pressed=SDL_FALSE;
			}
		if (IsInsideSnake(x_bonus,y_bonus,snake)){
			AddRectangle(snake);
			SDL_RenderClear(rendu);
			Pop_Bonus(snake,rendu,&x_bonus,&y_bonus);
			PrintSnake(snake,rendu);
			//PrintSnakeConsole(snake);
			}
		
		}else{
			printf("EndGame=TRUE\n");
			break;
		}
	}


	/*----------------------*/


	/*Fermeture de la SDL*/
	SDL_DestroyWindow(fenetre);
	SDL_DestroyRenderer(rendu);
	SDL_Quit();
	return 0;
}

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
	Snake *snake=InitialiseSnake(100,100,EAST);
	/*----------------------*/

	/*Definition des variables de jeu*/
	int x_bonus;
	int y_bonus;

	printf("1\n");
	Pop_Bonus(snake,rendu,&x_bonus,&y_bonus); 	//Fait apparaitre un bonus sur l'ecran
	printf("2\n");
	PrintSnake(snake,rendu); //Affiche le snake
	printf("3\n");
	/*----------------------*/

	/*Gestion des evenements*/

	SDL_bool program_launched=SDL_TRUE;

	while(program_launched){
		SDL_Event event;

		if(EndGame(snake)==SDL_FALSE){
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
								break;

							case SDLK_RIGHT: 
							/*Action a faire si la touche droite est pressee*/
								printf("RIGHT\n");
								SDL_RenderClear(rendu);
								PrintSquare(rendu, x_bonus, y_bonus);
								MoveSnake(snake,EAST,rendu);
								break;

							case SDLK_UP:
							/*Action a faire si la touche haute est pressee*/ 
								printf("UP\n");
								SDL_RenderClear(rendu);
								PrintSquare(rendu, x_bonus, y_bonus);
								MoveSnake(snake,NORTH,rendu);
								break;
					
							case SDLK_DOWN: 
							/*Action a faire si la touche basse est pressee*/
								printf("DOWN\n");
								SDL_RenderClear(rendu);
								PrintSquare(rendu, x_bonus, y_bonus);
								MoveSnake(snake,SOUTH,rendu);
								break;

							case SDLK_ESCAPE:
								program_launched=SDL_FALSE;
								break;

							default:
								break;
						}
						break;

					default:
						SDL_RenderClear(rendu);
						PrintSquare(rendu,x_bonus,y_bonus);
						MoveSnake(snake,snake->head->direction,rendu);
						break;
				
				}
		}
		if (IsInsideSnake(x_bonus,y_bonus,snake)){
			AddRectangle(snake);
			SDL_RenderClear(rendu);
			Pop_Bonus(snake,rendu,&x_bonus,&y_bonus);
			PrintSnake(snake,rendu);
			}
		
		}
	}


	/*----------------------*/


	/*Fermeture de la SDL*/
	SDL_DestroyWindow(fenetre);
	SDL_DestroyRenderer(rendu);
	SDL_Quit();
	return 0;
}

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

/* MEMO

	**fonctions**
		*** initialisation***

		. int SDL_Init(flag1 | flag2 | ...)   -> Initiliase une fenêtre avec les flags passé en paramètre (voir pdf)
											 Renvoie 0 si elle s'est exécutée correctement
		. void SDL_Log("texte formaté",arg1,...) ->affiche un message sous forme de log (comme le printf)
		. char *SDL_GetError() -> renvoie un numéro d'erreur si la SDL s'est mal initialisée
		. void SDL_Quit -> permet de quitter la SDL (indispensable comme le free())
		. Il existe d'autres fonctions pour initialiser d'autres systèmes de la SDL (video, audio) par la suite (il faut absolument utilisé les fonctins de libérationa associées)
		
		.SDL_Delay(int temps) -> Mets en pose l'execution pendant un temps précisé en parametre (en ms)

		***fenetre***

		. SDL_Window *SDL_CreateWindow(char *titre, float x ou flag, float y ou flag, int largeur, int hauteur, flag1, flag2, ...) -> crée une fenetre (avec son titre, x et y sont les coordonées du point en haut à gauche de la fenetre ou des options de flag sur x et y, cf pdf) et retourne le pointeur vers cette fenêtre
		. SDL_DestroyWindow(SDL_Window *window)-> détruit la fenetre passée en parametre (free)


	**Variables, types, structure**

		. SDL_Window -> type fenetre
	
	*Commande de compilation de la SDL*

		Windows -> gcc -Wall src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
		GNU-LINUX -> gcc mainc.c $(sdl2-config --cflags --libs) -o prog

	**RENDU**
		**fonctions** 
			.SDL_CreateRenderer(SDL_Window *window, driver, flags)->créer un rendu et retourne un pointeur (en général driver=-1) si cela ne s'est pas bien passé retourne NULL
			.SDL_DestroyRenderer(SDL_Renderer *renderer)->détruit un rendu(free)
			.SDL_RenderPresent(SDL_Renderer *renderer) -> affiche le rendu ou le raffraichit
			.SDL_RenderClear(SDL_Renderer *renderer) -> efface un rendu, renvoie 0 si tout s'est bien déroulé sinon renvoie une valeur négative
			.SDL_CreateWindowAndRenderer(int hauteur, int largeur,flags,SDL_Window **window, SDL_Renderer **renderer)->permet de créer une fenetre et un rendu en même temps (retourne 0 si s'est bien déroulé)

		**Variables, types, structures**
			.SDL_Renderer -> type de rendu
			.SDL_Rect -> structure de rectangle (champs : x,y,w,h) = coordonnées des points d'origine (tout en haut à gauche), largeur, hauteur

		**flags**
			. SDL_RENDERER_SOFTWARE -> logiciel (proccesseur)
			. SDL_RENDERER_ACCELERATED -> accélération matériel (carte graphique)
			. SDL_RENDERER_PRESENTVSYNC -> synchronisation verticale
			. SDL_RENDERER_TARGETTEXTURE
			. 0 -> par défaut

		**fonction de dessin**
			***Dessin sur les scènes de rendu***
			. SDL_SetRenderDrawColor(SDL_Renderer *renderer, int Red, int Green, int Blue, canal alpha) -> permet de changer la couleur du rendu (tracé, etc) dans une couleur rgb (retourne 0 si l'opération s'est bien déroulée), le canal alpha permet de gérer l'opacité (0 à 255)
			. SDL_RenderDrawPoint(SDL_Renderer *renderer, int x, int y) -> dessine un point dans le rendu avec la couleur courante au coordonées x,y. (renvoie 0 si ok)
			. SDL_RenderDrawLine(..., int x1, int y1, int x2, int y2) -> dessine une ligne du point de coordonées (x1,y1) à (x2,y2) (renvoie 0 si ok)
			. SDL_RenderDrawRect(renderer, SDL_Rect *rectangle) -> dessine le rectangle creux (renvoie 0 si ok)
			. SDL_RenderFillRect(renderer, SDL_Rect *rectangle) -> dessine un rectangle creux (0 si ok)
	
	**Textures et surfaces**
		**types, structures, variables**
			. SDL_Surface -> type surface
			. SDL_Texture -> type texture	
		**fonctions***
			. SDL_Surface *SDL_LoadBMP(char *chemin)-> permet de charger une image en tant que surface (retourne un pointeur vers une surface)
			. SDL_CreateTextureFromSurface(SDL_Renderer *renderer, SDL_surface *surface)
			. SDL_FreeSurface(SDL_Surface *surface) -> libère une surface



	**Evenements**
			***types, variables, structures***
				.SDL_bool -> type booléen qui peut prendre deux valeurs SDL_FALSE (0) et SDL_TRUE(1)
				.SDL_Event -> strcuture qui possède bcp d'informations (cf documentation sdl)
			***fonctions***
				. SDL_PollEvent(SDL_Event *event) -> fonction qui va capturé TOUS les évenements se produisant (clic de souris, etc.) et qui va modifier event en conséquence
				.
*/

void SDL_ExitWithError(char *message){
	SDL_Log("ERREUR: %s >%s", message,SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){

	SDL_Window *window=NULL;
	SDL_Renderer *renderer=NULL;

	//Initialisation de la SDL et verification
	if (SDL_Init(SDL_INIT_VIDEO)!=0){
		SDL_ExitWithError("Initialisation de la SDL");
	}

	/*-----------------------------FENETRE--------------------------------*/
	window=SDL_CreateWindow("Première fenêtre",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);

	if (window==NULL){
		SDL_ExitWithError("Creation de la fenetre echouee");
	}

	/*-----------------------------RENDU--------------------------------*/
	renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	if(renderer==NULL){
		SDL_ExitWithError("Creation rendu echouee");
	}

	SDL_RenderPresent(renderer);

	/*-------------------------------------------------------------*/
	
	SDL_Surface *image=NULL;
	SDL_Texture *texture=NULL;	

	image=SDL_LoadBMP("src/Bliss.bmp");
	if (image==NULL)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de charger l'image");
	}
	texture=SDL_CreateTextureFromSurface(renderer,image);
	SDL_

	if (texture==NULL){
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_ExitWithError("Impossible de creer la texture");
	}



	SDL_Delay(3000);
	//Sortie de la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS; //return 0;
}




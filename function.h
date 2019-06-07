#ifndef __FUNCTION__H__
#define __FUNCTION__H__

//On définit quatre constantes qui vont nous permettre de connaitre la direction dans laquelle avance chaque rectangle du Snake a chaque instant.
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define COTE 15 //taille des carrés composant le snake en pixel
#define HEIGHT 495
#define WIDTH 495

/*-------------Definitions des structures-------------*/

//Le Snake est réprésenté comme une liste chainée

/*Une cellule du Snake(contient un rectangle)*/
typedef struct SnakeCell{
	SDL_Rect *rectangle;  //chaque cellule contient un rectangle
	struct SnakeCell *next; //un pointeur vers la prochaine cellule
	int direction;  //la direction courante du rectangle
}SnakeCell;

/*Structure Snake*/
typedef struct Snake{
	SnakeCell *head; //Contient la tête du Snake
	int length; //la longueur du Snake
}Snake;

/*----------------------------------------------------*/




/*---------------Prototypes des fonctions---------------*/

Snake *AddRectangle(Snake *snake);
void PrintSnake(Snake *snake, SDL_Renderer *renderer);
Snake *MoveSnake(Snake *snake,int dir,SDL_Renderer *renderer);
void PrintSnakeConsole(Snake *snake);
Snake *InitialiseSnake(int x1, int y1, int dir);
SDL_bool EndGame(Snake *snake);
SDL_bool IsInsideSnake(int x1, int y1, Snake *Snake);
void Pop_Bonus(Snake *snake, SDL_Renderer *renderer,int *x_bonus,int *y_bonus);
void MoveSnake30FPS(Snake *snake,SDL_Rect *rectangle, int dir, SDL_Renderer *renderer);
void PrintSquare(SDL_Renderer *renderer,int x1, int y1);
/*----------------------------------------------------*/


#endif

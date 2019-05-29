#ifndef __FUNCTION__H__
#define __FUNCTION__H__

typedef struct SnakeCell{
	SDL_Rect rectangle;
	SDL_Rect *next;
}SnakeCell;

SnakeCell *AddRectangle(SnakeCell *snake, SDL_Rect rec);
void PrintSnake(SnakeCell *snake, SDL_Window *window, SDL_Window *window, SDL_Renderer *renderer);


#endif
#include"Object.h"


void DrawBorder(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, 0, 0, 0, TILE*TILE);
	SDL_RenderDrawLine(renderer, 0, 0, TILE*TILE, 0);
	SDL_RenderDrawLine(renderer, TILE*TILE, 0, TILE * TILE, TILE * TILE);
	SDL_RenderDrawLine(renderer, 0, TILE * TILE, TILE * TILE, TILE * TILE);
}
bool CheckCollision(int x1, int y1, int x2, int y2) {
	return (x1 == x2 && y1 == y2);
}

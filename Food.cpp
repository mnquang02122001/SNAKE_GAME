#include"Food.h"

Food::Food() {
	food_frame_.x = 4 * TILE; //* (rand() % TILE);
	food_frame_.y = 4 * TILE; //* (rand() % TILE);
	food_frame_.w = 0;
	food_frame_.h = 0;
}

Food::~Food(){}

void Food::renderFood(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	food_frame_.w = TILE;
	food_frame_.h = TILE;
	SDL_RenderFillRect(renderer, &food_frame_);
}
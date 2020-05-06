#ifndef FOOD_H_
#define FOOD_H_
#include"CommonFunc.h"

struct Food {
	SDL_Rect food_frame_;
	Food();
	~Food();
	void renderFood(SDL_Renderer* renderer);
};
#endif // 


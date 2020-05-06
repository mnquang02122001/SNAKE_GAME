#include"CommonFunc.h"
#include"Snake.h"
#include"Object.h"
#include"Food.h"
Snake p_snake;
Food p_food;
int main(int argc, char* argv[]) {
	initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	//srand(time(0));
	while (true) {
		srand(time(0));
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		
		p_snake.HandleInput(event);
		if (CheckCollision(p_snake.x_pos_, p_snake.y_pos_, p_food.food_frame_.x, p_food.food_frame_.y)==true) {
			p_snake.tail_length_++;
		}

		p_snake.UpdateTail();
		p_snake.renderSnake(renderer);
		p_food.renderFood(renderer);
		DrawBorder(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}

	waitUntilKeyPressed();
	quitSDL(window, renderer);

	return 0;
}
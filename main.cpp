#include"CommonFunc.h"
#include"Snake.h"
#include"Object.h"
#include"Food.h"
Snake p_snake;
Food p_food;
int main(int argc, char* argv[]) {
	initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	bool re_spawn = false;
	while (true) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);


		p_snake.HandleInput(event);
		if (re_spawn) {
			re_spawn = false;
			pair<int, int> loc_food = p_snake.SpawnFood();
			//p_food.x_pos = loc_food.first; 
			p_food.setXPOS(loc_food.first);
			p_food.setYPOS(loc_food.second);
			//p_food.y_pos = loc_food.second;
			if (p_food.getXPOS() == -1000 && p_food.getYPOS() == -1000) {
				re_spawn = true;
			}
		}
		if (CheckCollision(p_snake.getXPOS(), p_snake.getYPOS(), p_food.getXPOS(), p_food.getYPOS())) {
			pair<int, int> loc_food = p_snake.SpawnFood();
			p_food.setXPOS(loc_food.first);
			p_food.setYPOS(loc_food.second);
			if (p_food.getXPOS() == -1000 && p_food.getYPOS() == -1000) {
				re_spawn = true;
			}
			p_snake.tail_length_++;
		}
		p_snake.UpdateTail();
		if (p_snake.CheckGameOver()) {
			p_snake.NewGame();
			re_spawn = false;
			pair<int, int> loc_food = p_snake.SpawnFood();
			p_food.setXPOS(loc_food.first);
			p_food.setYPOS(loc_food.second);
			if (p_food.getXPOS() == -1000 && p_food.getYPOS() == -1000) {
				re_spawn = true;
			}
		}
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
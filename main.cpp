#include"CommonFunc.h"
#include"Snake.h"
#include"Object.h"
#include"Food.h"
#include"Text.h"
Snake p_snake;
Food p_food;
Object p_background;
int main(int argc, char* argv[]) {
	initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	if (!p_background.LoadImg("img//BackGround123.jpg", renderer)) {
		cout << "ERROR";
		return 0;
	}
	if (TTF_Init() < 0) {
		cout << "ERROR";
		return 0;
	}
	bool re_spawn = false;
	DisPlayMenu(renderer, event);
	while (true) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);


		p_snake.HandleInput(event);
		if (re_spawn) {
			re_spawn = false;
			pair<int, int> loc_food = p_snake.SpawnFood();
			p_food.setXPOS(loc_food.first);
			p_food.setYPOS(loc_food.second);
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
			p_snake.IncreaseTailLength();
		}
		p_snake.UpdateTail();
		if (p_snake.CheckGameOver()) {
			DisplayGameOver(renderer, event, p_snake.getLength());
			p_snake.NewGame();
			re_spawn = false;
			pair<int, int> loc_food = p_snake.SpawnFood();
			p_food.setXPOS(loc_food.first);
			p_food.setYPOS(loc_food.second);
			if (p_food.getXPOS() == -1000 && p_food.getYPOS() == -1000) {
				re_spawn = true;
			}
		}
		if (p_snake.CheckWin()) {
			DisPlayYouWin(renderer, event);
			p_snake.NewGame();
			re_spawn = false;
			pair<int, int> loc_food = p_snake.SpawnFood();
			p_food.setXPOS(loc_food.first);
			p_food.setYPOS(loc_food.second);
			if (p_food.getXPOS() == -1000 && p_food.getYPOS() == -1000) {
				re_spawn = true;
			}
		}
		p_background.RenderBackGround(renderer);
		p_snake.renderSnake(renderer);
		p_food.renderFood(renderer);
		RenderScrore(renderer, p_snake.getLength());
		DrawBorder(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}
	TTF_Quit();
	waitUntilKeyPressed();
	quitSDL(window, renderer);

	return 0;
}
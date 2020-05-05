#include"CommonFunc.h"

int main(int argc, char* argv[]) {
	initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	waitUntilKeyPressed();
	quitSDL(window, renderer);
	return 0;
}
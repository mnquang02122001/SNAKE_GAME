#ifndef COMMONFUNC_H_
#define COMMONFUNC_H_
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SDL.h> 
#include <SDL_ttf.h>
using namespace std;
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer,
    int SCREEN_WIDTH, int SCREEN_HEIGHT, const string& WINDOW_TITLE);
void logSDLError(std::ostream& os,
    const std::string& msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();


static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Event event;

const int SCREEN_WIDTH = 577;
const int SCREEN_HEIGHT = 577;
const string WINDOW_TITLE = "SNAKE GAME";

const int HEIGHT_TILE = 24;
const int WIDTH_TILE = 24;
const int TILE = 24;
#endif // !COMMONFUNC_H_

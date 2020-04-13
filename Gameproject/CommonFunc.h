#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<Windows.h>
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<string>
#include<fstream>

static SDL_Window* g_window;
static SDL_Renderer* g_screen;
static SDL_Event g_event;

const int SCREEN_HEIGHT = /*1280*/ 640;
const int SCREEN_WIDTH = /*640*/ 1280;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const std::string WINDOW_TITLE = "GAME PROJECT";
const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10/*10*/
struct Map {
    int max_x;
    int max_y;
    int start_x;
    int start_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};
typedef struct Map Map;
#endif // !COMMON_FUNCTION

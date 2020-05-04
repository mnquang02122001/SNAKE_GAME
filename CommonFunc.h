#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<Windows.h>
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<string>
#include<vector>
static SDL_Window* global_window;
static SDL_Renderer* global_screen;
static SDL_Event global_event;


//screen
const int FRAME_PER_SECOND = 30; //fps
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 1280;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const std::string WINDOW_TITLE = "Mai Nhat Quang's first game project";
const int RENDER_DRAW_COLOR = 0xff;

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define PLANK_TILE 0
#define STATE_MONEY 4
typedef struct Input {
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

typedef struct Map {
    int max_x;
    int max_y;
    int start_x;
    int start_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLCommonFunc {
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}
//typedef struct Map Map;
#endif // !COMMON_FUNCTION

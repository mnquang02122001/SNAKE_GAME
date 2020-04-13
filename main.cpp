#include"CommonFunc.h"
#include"BaseObject.h"
#include"Game_map.h"
#include"MainObject.h"

BaseObject g_background;
void close() {
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}
bool InitData() {
    bool sucess = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow(WINDOW_TITLE.c_str(),
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, 
                                 SCREEN_WIDTH, SCREEN_HEIGHT, 
                                 SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
        sucess = false;
    }
    else {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) {
            sucess = false;
        }
        else {
            SDL_SetRenderDrawColor(g_screen, 
                                   RENDER_DRAW_COLOR, 
                                   RENDER_DRAW_COLOR,  
                                   RENDER_DRAW_COLOR,  
                                   RENDER_DRAW_COLOR);
            int imagFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imagFlags) && imagFlags)) {
                sucess = false;
            }
        }
    }
    return sucess;

}
bool LoadBackground() {
    bool ret = g_background.LoadImg("img//BACKGROUND.jpg", g_screen);
    if (!ret) {
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (!InitData()) {
        return -1;
    }
    if (!LoadBackground()) {
        return -1; 
    }
    GameMap game_map;
    char dirmap[] = "map/map01.dat";
    game_map.LoadMap(dirmap);
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("img//player_right.png", g_screen);
    p_player.set_clips();
    bool is_quit = false;
    while (!is_quit) {
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            p_player.HandleInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        game_map.DrawMap(g_screen);

        p_player.Show(g_screen);
        SDL_RenderPresent(g_screen);
    }
    close();
    return 0;
}

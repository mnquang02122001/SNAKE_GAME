#include"CommonFunc.h"
#include"BaseObject.h"
#include"Map.h"
#include"Player.h"
#include"FPS.h"
#include"Monster.h"
BaseObject global_background;
bool InitData() {
    bool init = true;
    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result < 0) {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    global_window = SDL_CreateWindow(WINDOW_TITLE.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (global_window == NULL) {
        init = false;
    }
    else {
        global_screen = SDL_CreateRenderer(global_window, -1, SDL_RENDERER_ACCELERATED);
        if (global_screen == NULL) {
            init = false;
        }
        else {
            SDL_SetRenderDrawColor(global_screen,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR);
            int imagFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imagFlags) && imagFlags)) {
                init = false;
            }
        }
    }
    return init;
}
bool LoadBackground() {
    bool result = global_background.LoadImg("img//BackGround123.jpg", global_screen);
    if (!result) {
        return false;
    }
    return true;
}

void CloseProject() {
    global_background.Free();
    SDL_DestroyRenderer(global_screen);
    global_screen = NULL;
    SDL_DestroyWindow(global_window);
    global_window = NULL;
    IMG_Quit();
    SDL_Quit();
}
std::vector<ThreatsObject*> MakeThreadList() {
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* dynamic_objs = new ThreatsObject[20];
    for (int i = 0; i < 20; i++) {
        ThreatsObject* p_threat = (dynamic_objs + i);
        if (p_threat != nullptr) {
            p_threat->LoadImg("img//threat_left.png", global_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE);
            p_threat->set_x_pos(500 + i * 500);
            p_threat->set_y_pos(200);
            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimation(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }
    ThreatsObject* threats_objs = new ThreatsObject[20];

    for (int i = 0; i < 20; i++) {

        ThreatsObject* p_threat1 = (threats_objs + i);
        if (p_threat1 != NULL) {
            p_threat1->LoadImg("img//static_robot.png", global_screen);
            p_threat1->set_clips();
            p_threat1->set_x_pos(700 + i*1200);
            p_threat1->set_y_pos(250);
            p_threat1->set_type_move(ThreatsObject::STATIC_THREAT);
            list_threats.push_back(p_threat1);
        }
    }
    return list_threats;
}

int main(int argc, char* argv[]) {
    ImpTimer FPStimer;
    if (!InitData()) {
        return -1;
    }
    if (!LoadBackground()) {
        return -1; 
    }
    GameMap Map_Game;
    char dirmap[] = "map/map01.dat";
    Map_Game.LoadMap(dirmap);
    Map_Game.LoadTiles(global_screen);

    MainObject PLAYER;
    PLAYER.LoadImg("img//player_right.png", global_screen);
    PLAYER.set_clips();

    std::vector<ThreatsObject*> threats_list = MakeThreadList();
    
    bool quit = false;
    while (!quit) {
        FPStimer.start();
        while (SDL_PollEvent(&global_event) != 0) {
            if (global_event.type == SDL_QUIT) {
                quit = true;
            }
            PLAYER.HandleInputAction(global_event, global_screen);
        }
        SDL_SetRenderDrawColor(global_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(global_screen);

        global_background.Render(global_screen, NULL);

        Map MAP = Map_Game.getMap();

        PLAYER.HandleBullet(global_screen);
        PLAYER.SetMapXY(MAP.start_x, MAP.start_y);
        PLAYER.DoPlayer(MAP);
        PLAYER.Show(global_screen);

        Map_Game.SetMap(MAP);
        Map_Game.DrawMap(global_screen);

        for (int i = 0; i < threats_list.size(); i++) {
            ThreatsObject* THREATS = threats_list.at(i);
            if (THREATS != NULL) {
                THREATS->SetMapXY(MAP.start_x, MAP.start_y);
                THREATS->ImpMoveType(global_screen);
                THREATS->DoPlayer(MAP);
                THREATS->Show(global_screen);

                SDL_Rect RECTPLAYER = PLAYER.GetRectFrame();
                SDL_Rect RECTTHREAT = THREATS->GetRectFrame();

                bool check = SDLCommonFunc::CheckCollision(RECTPLAYER, RECTTHREAT);

                if (check) {
                    if (MessageBox(NULL, L"GAME OVER", L"Poor you!", MB_OK | MB_ICONSTOP) == IDOK) {
                        THREATS->Free();
                        CloseProject();
                        SDL_Quit();
                        return 0;
                    }
                }
            }
        }
        std::vector<BulletObject*> BULLET = PLAYER.get_bullet_list();
        for (int r = 0; r < BULLET.size(); r++) {
            BulletObject* PLAYER_BULL = BULLET.at(r);
            if (PLAYER_BULL != NULL) {
                for (int t = 0; t < threats_list.size(); t++) {
                    ThreatsObject* OBJECT_THREAT = threats_list.at(t);
                    if (OBJECT_THREAT != NULL) {
                        SDL_Rect tRect;
                        tRect.x = OBJECT_THREAT->GetRect().x;
                        tRect.y = OBJECT_THREAT->GetRect().y;
                        tRect.w = OBJECT_THREAT->get_width_frame();
                        tRect.h = OBJECT_THREAT->get_height_frame();

                        SDL_Rect BULLRect = PLAYER_BULL->GetRect();

                        bool CHECK = SDLCommonFunc::CheckCollision(BULLRect, tRect);
                        if (CHECK) {
                            PLAYER.RemoveBullet(r);
                            OBJECT_THREAT->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }
            }
        }

        SDL_RenderPresent(global_screen);

        int REALTIME = FPStimer.get_ticks();
        int TIME_1_FRAME = 1000 / FRAME_PER_SECOND; //ms

        if (REALTIME < TIME_1_FRAME) {
            SDL_Delay(TIME_1_FRAME - REALTIME);
        }
    }
    for (int i = 0; i < threats_list.size(); i++) {
        ThreatsObject* THREATS = threats_list.at(i);
        if (THREATS) {
            THREATS->Free();
            THREATS = NULL;
        }
    }
    threats_list.clear();
    CloseProject();
    return 0;
}

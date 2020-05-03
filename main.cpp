#include"CommonFunc.h"
#include"BaseObject.h"
#include"Game_map.h"
#include"MainObject.h"
#include"ImpTimer.h"
#include"ThreatsObject.h"
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
std::vector<ThreatsObject*> MakeThreadList() {
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* dynamic_objs = new ThreatsObject[20];
    for (int i = 0; i < 20; i++) {
        ThreatsObject* p_threat = (dynamic_objs + i);
        if (p_threat != nullptr) {
            p_threat->LoadImg("img//threat_left.png", g_screen);
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
            p_threat1->LoadImg("img//static_robot.png", g_screen);
            p_threat1->set_clips();
            p_threat1->set_x_pos(700 + i*1200);
            p_threat1->set_y_pos(250);
            p_threat1->set_type_move(ThreatsObject::STATIC_THREAT);

            BulletObject* p_bullet = new BulletObject();
            p_threat1->InitBullet(p_bullet, g_screen);

            list_threats.push_back(p_threat1);
        }
    }
    return list_threats;
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
    bool ret = g_background.LoadImg("img//BackGround123.jpg", g_screen);
    if (!ret) {
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    ImpTimer fps_timer;
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

    std::vector<ThreatsObject*> threats_list = MakeThreadList();

    bool is_quit = false;
    while (!is_quit) {
        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            p_player.HandleInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getMap();

        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(map_data.start_x, map_data.start_y);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        for (int i = 0; i < threats_list.size(); i++) {
            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat != NULL) {
                p_threat->SetMapXY(map_data.start_x, map_data.start_y);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);

                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                /*std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int j = 0; j < tBullet_list.size(); j++) {
                    BulletObject* pt_bullet = tBullet_list.at(j);
                    if (pt_bullet) {
                        bCol1 = SDLCommonFunc::CheckCollision(rect_player,pt_bullet->GetRect());
                        if (bCol1) {
                           p_threat->RemoveBullet(j);
                           break;
                       }
                    }
                }

                SDL_Rect rect_threat = p_threat->GetRectFrame();
                
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

                if (bCol1 || bCol2) {
                        if (MessageBox(NULL, L"GAME OVER", L"INFO" ,MB_OK | MB_ICONSTOP) == IDOK) {
                        p_threat->Free();
                        close();
                        SDL_Quit();
                        return 0;
                    }
                }*/
            }
        }
        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r = 0; r < bullet_arr.size(); r++) {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL) {
                for (int t = 0; t < threats_list.size(); t++) {
                    ThreatsObject* obj_threat = threats_list.at(t);
                    if (obj_threat != NULL) {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                        if (bCol) {
                            p_player.RemoveBullet(r);   
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }
            }
        }

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND; //ms

        if (real_imp_time < time_one_frame) {
            int delayer_time = time_one_frame - real_imp_time;
            if (delayer_time > 0) {
                SDL_Delay(delayer_time);
            }
        }
    }
    for (int i = 0; i < threats_list.size(); i++) {
        ThreatsObject* p_threat = threats_list.at(i);
        if (p_threat) {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threats_list.clear();
    close();
    return 0;
}

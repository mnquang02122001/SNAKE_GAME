#ifndef PLAYER_H
#define PLAYER_H

#include<vector>
#include"CommonFunc.h"
#include"BaseObject.h"
#include"Gun.h"

#define GRAVITY_SPEED 4
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 6
#define PLAYER_JUMP_VAL 37
#define PLAYER_FRAME_NUM 1
class MainObject : public BaseObject {
public: 
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_RIGHT = 0,
	    WALK_LEFT = 1,
	};
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterEntityOnMap(Map& map_data);
	SDL_Rect GetRectFrame();
	void set_bullet_list(std::vector<BulletObject*> bullet_list) {
		p_bullet_list_ = bullet_list;
	}
	std::vector<BulletObject*> get_bullet_list() { return p_bullet_list_; }
	void HandleBullet(SDL_Renderer* des);
	void IncreaseMoney();
	void RemoveBullet(const int& index);
	void set_comeback_time(const int& cb_time) { come_back_time = cb_time; }
private:
	int money_count;
	std::vector<BulletObject*> p_bullet_list_;
	
    float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[PLAYER_FRAME_NUM];

	Input input_type_;
	int frame_;
	int status_;
	bool on_ground_;

	int map_x_;
	int map_y_;

	int come_back_time;
};

#endif // !PLAYER_H


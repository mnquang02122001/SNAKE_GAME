#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include"CommonFunc.h"
#include"BaseObject.h"

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
	void HandleInputAction(SDL_Event events, SDL_Renderer* screeen);
	void set_clips();
//private:
	int x_val_;
	int y_val_;

	int x_pos_;
	int y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[8];

	Input input_type_;
	int frame_;
	int status_;
};

#endif // !MAIN_OBJECT_H


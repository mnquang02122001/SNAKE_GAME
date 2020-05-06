#include"CommonFunc.h"
#ifndef SNAKE_H_
#define SNAKE_H_

struct Snake {
	SDL_Rect snake_frame_;
	int tail_length_;
	vector<int> tail_x_;
	vector<int> tail_y_;

	int x_pos_;
	int y_pos_;
	int pre_x_;
	int pre_y_;

	bool up, down, left, right;

	bool input_frame_;

	bool re_do_;


	Snake();
	~Snake();
	void renderSnake(SDL_Renderer* renderer);
	void HandleInput(SDL_Event e);
	void UpdateTail();
};

#endif // !SNAKE_H_
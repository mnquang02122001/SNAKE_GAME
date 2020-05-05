#include"CommonFunc.h"
#ifndef SNAKE_H_
#define SNAKE_H_

class Snake {
public:
	Snake();
	~Snake();
	void renderSnake(SDL_Renderer* renderer, SDL_Rect snake_, int x_, int y_, int tile_,vector<int> tail_x, vector<int> tail_y, int tail_length);
private:
	SDL_Rect snake_frame_;
	int tail_length_;
	vector<int> tail_x_;
	vector<int> tail_y_;

	int x_pos_;
	int y_pos_;
	int pre_x_;
	int pre_y_;

	bool up, down, left, right;

	bool increase_frame_;

	bool re_do_;
};

#endif // !SNAKE_H_

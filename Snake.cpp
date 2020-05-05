#include"Snake.h"

Snake::Snake() {
	snake_frame_.x = 0;
	snake_frame_.y = 0;
	snake_frame_.w = 0;
	snake_frame_.h = 0;

	x_pos_ = 0;
	y_pos_ = 0;
	pre_x_ = 0;
	pre_y_ = 0;

	up = false;
	down = false;
	right = false;
	left = false;

	increase_frame_ = false;
	re_do_ = false;
}
Snake::~Snake(){}

void Snake::renderSnake(SDL_Renderer* renderer, SDL_Rect snake_, int x_, int y_,int tile_,  vector<int> tail_x, vector<int> tail_y, int tail_length) {

}
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
	tail_length_ = 0;

	up = false;
	down = false;
	right = false;
	left = false;

	input_frame_ = false;
	re_do_ = false;
}
Snake::~Snake(){}

void Snake::renderSnake(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	snake_frame_.w = TILE;
	snake_frame_.h = TILE;
	//Lay vi tri x y cua block tail
	for (int i = 0; i < tail_length_; i++)
	{
		snake_frame_.x = tail_x_[i];
		snake_frame_.y = tail_y_[i];
		SDL_RenderFillRect(renderer, &snake_frame_);
	}
	snake_frame_.x = x_pos_;
	snake_frame_.y = y_pos_;
	SDL_RenderFillRect(renderer, &snake_frame_);
}

void Snake::HandleInput(SDL_Event e) {
	input_frame_ = false;
	if (SDL_PollEvent(&e)) {
		if (event.type == SDL_QUIT) {
			return;
		}
		if (e.type == SDL_KEYDOWN && !input_frame_) {
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				right = false;
				left = true;
				up = false;
				down = false;
				input_frame_ = true;
				break;
			case SDLK_RIGHT:
				right = true;
				left = false;
				up = false;
				down = false;
				input_frame_ = true;
				break;
			case SDLK_UP:
				right = false;
				left = false;
				up = true;
				down = false;
				input_frame_ = true;
				break;
			case SDLK_DOWN:
				right = false;
				left = false;
				up = false;
				down = true;
				input_frame_ = true;
				break;
			default:
				break;
			}
		}
		
	}
	pre_x_ = x_pos_;
	pre_y_ = y_pos_;
	if (up) {
		y_pos_ -= TILE;
	}
	else if (down) {
		y_pos_ += TILE;
	}
	else if (right) {
		x_pos_ += TILE;
	}
	else if (left) {
		x_pos_ -= TILE;
	}
} 

void Snake::UpdateTail() {
	if (tail_x_.size() != tail_length_) {
		tail_x_.push_back(pre_x_);
		tail_y_.push_back(pre_y_);
	}

	for (int i = 0; i < tail_length_; i++) {
		if (i > 0) {
			tail_x_[i - 1] = tail_x_[i];
			tail_y_[i - 1] = tail_y_[i];
		}
	}
	if (tail_length_ > 0) {
		tail_x_[tail_length_ - 1] = pre_x_;
		tail_y_[tail_length_ - 1] = pre_y_;
	}
}
#include"CommonFunc.h"
#ifndef SNAKE_H_
#define SNAKE_H_

class Snake {
private:
	SDL_Rect snake_frame_;
	vector<int> tail_x_;
	vector<int> tail_y_;
	int x_pos_;
	int y_pos_;
	int pre_x_;
	int pre_y_;

	bool up, down, left, right;
public:
	int tail_length_;
	Snake();
	~Snake();
	void renderSnake(SDL_Renderer* renderer);
	void HandleInput(SDL_Event e);
	void UpdateTail();
	pair<int, int> SpawnFood();
	bool CheckGameOver();
	void NewGame();
	void setXPOS(int xpos) { x_pos_ = xpos; }
	void setYPOS(int ypos) { y_pos_ = ypos; }
	int getXPOS() const { return x_pos_; }
	int getYPOS() const  { return y_pos_; }
};

#endif // !SNAKE_H_
#ifndef GUN_H_
#define GUN_H_

#include"BaseObject.h"
#include"CommonFunc.h"

class BulletObject : public BaseObject {

public:
	BulletObject();
	~BulletObject();

	enum BulletDir {
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
		DIR_UP = 22,
		DIR_UP_LEFT = 23,
		DIR_UP_RIGHT = 24,
		DIR_DOWN_LEFT = 25,
		DIR_DOWN_RIGHT = 26
	};
	enum BulletType {
		CIRCLE_BULLET = 50,
		LASER_BULLET = 51
	};
	void set_x_val(const int& xVal) { x_val_ = xVal; }
	void set_y_val(const int& yVal) { y_val_ = yVal; }
	int get_x_val() const { return x_val_; }
	int get_y_val() const { return y_val_; }

	void set_is_move(const bool& isMove){ is_move_ = isMove; }
	bool get_is_move() const { return is_move_; }

	void set_bullet_dir(const unsigned int& Bullet_dir) { bullet_dir_ = Bullet_dir; }
	unsigned int get_bullet_dir() { return bullet_dir_; }
	void HandleMove(const int& x_border, const int& y_border);
	void set_bullet_type(const unsigned int& bullet_type) { bullet_type_ = bullet_type; }
	unsigned int get_bullet_type() { return bullet_type_; }
	bool LoadImgBullet(SDL_Renderer* screen);
private:
	int x_val_;
	int y_val_;
	bool is_move_;
	unsigned int bullet_dir_;
	unsigned int bullet_type_;
};




#endif // !GUN_H_

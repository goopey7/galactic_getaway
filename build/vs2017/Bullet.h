#pragma once
#include "GameObject.h"
#include "maths/vector2.h"

class Bullet : public GameObject {
public:
	Bullet();
	void Fire(gef::Vector2 target_vector, gef::Vector2 start_pos, int damage);
	void setAlive(bool b) { is_alive_ = b; }
	bool isAlive() { return is_alive_; }
	int getDamage() const { return damage_; }
	void setDamage(int damage) {damage_ = damage;}
	void EndCollision(GameObject* other) override;
protected:
	bool is_alive_ = false;
	int damage_ = 0;
};


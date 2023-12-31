#include "Bullet.h"
#include <cmath>

#include "system/debug_log.h"

Bullet::Bullet()
{
	tag = Tag::Bullet;
}

void Bullet::Fire(gef::Vector2 target_vector, gef::Vector2 start_pos, int damage, GameObject::Tag target, float speed)
{
	target_ = target;
	damage_ = damage;
	speed_ = speed;
	b2Vec2 b2_target_vector(target_vector.x * speed, -target_vector.y * speed);
	b2Vec2 b2_start_pos(start_pos.x, start_pos.y);
	setAlive(true);
	Translate(gef::Vector4(0, 0, -0.1)); //Moves bullet behind the gun
	physics_body_->SetEnabled(true);
	physics_body_->SetTransform(b2_start_pos, atan2(target_vector.x, target_vector.y));
	physics_body_->SetLinearVelocity({b2_target_vector.x, b2_target_vector.y});
	EnableCollisionResolution(bCollisionEnabled);
}

void Bullet::Update(float frame_time)
{
	EnableCollisionResolution(bCollisionEnabled);
	GameObject::Update(frame_time);
}

void Bullet::BeginCollision(GameObject* other)
{
	if(other->GetTag() == Tag::Bullet || other->GetTag() == Tag::Pickup)
	{
		return;
	}
	
	if(target_ == Tag::Player && other->GetTag() == Tag::Player)
	{
		Kill();
	}
	else if(target_ == Tag::Enemy && other->GetTag() == Tag::Enemy)
	{
		Kill();
	}
	else if(other->GetTag() != Tag::Player && other->GetTag() != Tag::Enemy)
	{
		Kill();
	}
}

GameObject::Tag Bullet::getTarget() const
{
	return target_;
}

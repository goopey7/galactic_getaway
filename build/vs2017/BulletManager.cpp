#include "BulletManager.h"

void BulletManager::Init(b2World* world, PrimitiveBuilder* builder, gef::AudioManager* am) {
	world_ = world;
	builder_ = builder;
	am_ = am;
}
 
void BulletManager::Update(float frame_time)
{
	for (size_t i=0; i < bullets_.size(); i++) {
		Bullet* bullet = bullets_[i];
		if(bullet != nullptr)
		{
			bullet->Update(frame_time);
			if(bullet->TimeToDie())
			{
				world_->DestroyBody(bullet->GetBody());
				bullets_.erase(bullets_.begin() + i);
				delete bullet;
				bullet = nullptr;
			}
		}
	}
}

void BulletManager::Fire(gef::Vector2 target_vector, gef::Vector2 start_pos, int damage, GameObject::Tag target, float speed) {
	bullets_.push_back(new Bullet);
	bullets_.back()->Init(0.2, 0.2, 0.2, 0, 0, world_, builder_, am_, true);
	bullets_.back()->GetBody()->SetGravityScale(0.f);
	bullets_.back()->Fire(target_vector, start_pos, damage, target, speed);
}

void BulletManager::Render(gef::Renderer3D* renderer_3d) const {
	for (Bullet* bullet : bullets_) {
		renderer_3d->DrawMesh(*bullet);
	}
}
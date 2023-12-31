#pragma once
#include "GameObject.h"
#include "maths/vector4.h"

class Door {
public:
	Door(gef::Vector4 size, gef::Vector4 pos, b2World* world, PrimitiveBuilder* builder, gef::AudioManager* am, gef::Mesh* door_wall, gef::Mesh* door_frame, gef::Mesh* door);
	void Update(float dt);
	void Open();
	void Close();
	void Render(gef::Renderer3D* renderer_3d) const;
private:
	gef::MeshInstance door_wall_;
	gef::MeshInstance door_frame_;
	GameObject* door_;
	gef::Vector4 closed_pos_;
	gef::Vector4 open_pos_;
	gef::Vector4 start_pos_;
	enum class State { OPENING, CLOSING, IDLE };
	State current_state_ = State::IDLE;
	float lerp_time_ = 0.f;
	gef::AudioManager* audio_manager_ = nullptr;
};


#pragma once
#include "maths/vector2.h"
#include "maths/vector4.h"
#include "maths/matrix44.h"
#include "graphics/mesh_instance.h"
#include <queue>

enum class EffectState { NORMAL, SHAKE, WARP };

class Camera
{
public:
	Camera();
	void Update(float dt, gef::Vector2 target_pos);
	gef::Matrix44 GetViewMatrix() { return view_matrix_; }
	void Warp() { shake_time_ = 0.2f; effect_state_ = EffectState::WARP; }
	void Shake();
	void SetPosition(gef::Vector4 pos);
	void SetAbovePlayer(bool value) { above_player_ = value; }
	gef::MeshInstance* GetBackground() { return &background_; }
	EffectState GetEffectState() { return effect_state_; }
protected:
	gef::Vector4 target_pos_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_pos_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	gef::Vector4 camera_lookat_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	gef::Vector4 lerp_start_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	gef::Vector4 offset_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	gef::Vector4 up_ = gef::Vector4(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix_;
	EffectState effect_state_ = EffectState::NORMAL;
	float shake_time_ = 0.2f;
	enum class MoveState { STATIONARY, LERP, TRACK };
	MoveState move_state_ = MoveState::STATIONARY;
	float lerp_time_ = 0.2f;
	std::queue<gef::Vector4> prev_lookats_;
	gef::Vector4 shake_start_lookat_;
	bool above_player_ = true;

	gef::Matrix44 transform_matrix_;
	gef::MeshInstance background_;
};


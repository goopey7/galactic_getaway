﻿#pragma once

namespace gef
{
	class Platform;
	class Font;
}

namespace gef
{
	class SpriteRenderer;
}

namespace gef
{
	class Renderer3D;
}

class InputActionManager;

class Scene
{
public:
	Scene(gef::Platform& platform) : platform_(&platform) {}
	virtual void Update(InputActionManager* iam, float frame_time) = 0;
	virtual void Render(gef::Renderer3D* renderer_3d) = 0;
	virtual void Render(gef::SpriteRenderer* sprite_renderer, gef::Font* font) = 0;
	virtual void Render(gef::Renderer3D* renderer_3d, gef::SpriteRenderer* sprite_renderer, gef::Font* font) = 0;
protected:
	gef::Platform* platform_;
};

﻿#include "Image.h"

#include "graphics/sprite.h"
#include "graphics/sprite_renderer.h"
#include "system/platform.h"

Image::Image(const gef::Vector2& anchor, gef::Sprite* sprite, const gef::Platform& platform)
	: UIElement(anchor, platform), sprite_(sprite)
{
	sprite_->set_position(platform.width() * anchor_.x, platform.height() * anchor_.y, -0.9f);
}

void Image::Render(gef::SpriteRenderer* sprite_renderer, gef::Font* font) const
{
	sprite_renderer->DrawSprite(*sprite_);
}

void Image::SetAlpha(float alpha)
{
	if(!ignore_alpha_)
		sprite_->set_colour(0x00ffffff | (static_cast<unsigned int>(alpha * 255) << 24));
	else
		sprite_->set_colour(0xffffffff);
}

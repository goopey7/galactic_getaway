#include "SpriteAnimator3D.h"
#include <graphics/primitive.h>
#include <graphics/texture.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
#include <graphics/material.h>
#include <filesystem>
#include <string>
#include "system/debug_log.h"

namespace fs = std::filesystem;

SpriteAnimator3D::SpriteAnimator3D(gef::Platform* platform, PrimitiveBuilder* builder, const gef::Vector4& half_size, gef::Vector4 centre)
	: platform_(platform),
	builder_(builder),
	half_size_(half_size),
	centre_(centre)
{
}

void SpriteAnimator3D::AddAnimation(const char* anim_name, const char* folder_name, float speed, bool looping) {
	gef::PNGLoader png_loader;	

	animations_[anim_name].frame_speed_ = speed;
	animations_[anim_name].looping_ = looping;
	for (auto& entry : fs::directory_iterator(folder_name)) {
		std::filesystem::path outfilename = entry.path();
		std::string outfilename_str = outfilename.string();
		const char* path = outfilename_str.c_str();
		
		gef::ImageData image_data;
		png_loader.Load(path, *platform_, image_data);
		if (image_data.image() != NULL) {
			gef::Texture* texture = gef::Texture::Create(*platform_, image_data);
			gef::Material* material = new gef::Material();
			material->set_texture(texture);
			
			gef::Mesh* mesh = builder_->CreatePlaneMesh(half_size_, centre_, &material);
			animations_[anim_name].frames_.push_back(*mesh);
		}
	}
}

const gef::Mesh* SpriteAnimator3D::Update(float dt, const gef::Mesh* current_mesh, const char* anim_name) {
	if (animations_[anim_name].looping_ || !animations_[anim_name].reached_end_) {
		time_passed_ += dt;
		if (time_passed_ >= animations_[anim_name].frame_speed_) {
			time_passed_ = 0;

			it = animations_[anim_name].frames_.begin();
			while (&*it != &animations_[anim_name].frames_.back() && &*it != current_mesh) {
				it++;
			}
			if (&*it == &animations_[anim_name].frames_.back() || &*it != current_mesh) {
				current_mesh = &animations_[anim_name].frames_.front();
			}
			else {
				it++;
				current_mesh = &*it;
				if (!animations_[anim_name].looping_ && current_mesh == &animations_[anim_name].frames_.back()) {
					animations_[anim_name].reached_end_ = true;
				}
			}
		}
	}
	return current_mesh;
}

gef::Mesh* SpriteAnimator3D::CreateMesh(const char* filepath, const gef::Vector4& half_size, gef::Vector4 centre) {
	gef::PNGLoader png_loader;
	gef::ImageData image_data;
	png_loader.Load(filepath, *platform_, image_data);
	if (image_data.image() != NULL) {
		gef::Texture* texture = gef::Texture::Create(*platform_, image_data);
		gef::Material* material = new gef::Material();
		material->set_texture(texture);

		gef::Mesh* mesh = builder_->CreatePlaneMesh(half_size, centre, &material);
		return mesh;
	}
	return nullptr;
}

const gef::Mesh* SpriteAnimator3D::GetFirstFrame(const char* anim_name) {
	return &animations_[anim_name].frames_.front();
}
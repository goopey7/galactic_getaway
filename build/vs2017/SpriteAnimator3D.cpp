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

void SpriteAnimator3D::AddAnimation(const char* anim_name, const char* folder_name) {
	gef::PNGLoader png_loader;	

	for (auto& entry : fs::directory_iterator(folder_name)) {
		std::filesystem::path outfilename = entry.path();
		std::string outfilename_str = outfilename.string();
		const char* path = outfilename_str.c_str();
		gef::DebugOut("\n");
		gef::DebugOut(path);

		gef::ImageData image_data;
		png_loader.Load(path, *platform_, image_data);
		if (image_data.image() != NULL) {
			gef::Texture* texture = gef::Texture::Create(*platform_, image_data);
			gef::Material* material = new gef::Material();
			material->set_texture(texture);
			
			gef::Mesh* mesh = builder_->CreatePlaneMesh(half_size_, centre_, &material);
			animations_[anim_name].push_back(*mesh);
		}
	}
}

const gef::Mesh* SpriteAnimator3D::Update(float dt, const gef::Mesh* current_mesh, const char* anim_name) {
	time_passed_ += dt;
	if (time_passed_ >= 0.3) {
		time_passed_ = 0;
		if (current_mesh >= &animations_[anim_name].back() || current_mesh < &animations_[anim_name].front()) {
			current_mesh = &animations_[anim_name].front();
		}
		else {
			it = animations_[anim_name].begin();
			while (&*it != current_mesh) {
				it++;
			}
			it++;
			current_mesh = &*it;
		}
	}
	return current_mesh;
}
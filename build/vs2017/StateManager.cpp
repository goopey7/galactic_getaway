﻿#include "StateManager.h"

#include "Level.h"
#include "LoadingScreen.h"
#include "Menu.h"
#include "Scene.h"

StateManager::StateManager(LoadingScreen* loading_screen)
	: loading_screen_(loading_screen)
{
}

void StateManager::Update(InputActionManager* iam, float frame_time)
{
	if(is_loading_)
	{
		loading_screen_->Update(iam, frame_time);
	}
	else if(on_main_menu_ && main_menu_ != nullptr)
	{
		main_menu_->Update(iam, frame_time);
	}
	else
	{
		current_scene_->Update(iam, frame_time);
	}
}

void StateManager::Render(gef::Renderer3D* renderer_3d)
{
	if(is_loading_)
	{
		loading_screen_->Render(renderer_3d);
	}
	else if(on_main_menu_ && main_menu_ != nullptr)
	{
		main_menu_->Render(renderer_3d);
	}
	else
	{
		current_scene_->Render(renderer_3d);
	}
}

void StateManager::Render(gef::Renderer3D* renderer_3d, gef::SpriteRenderer* sprite_renderer, gef::Font* font)
{
	if(is_loading_)
	{
		loading_screen_->Render(renderer_3d, sprite_renderer, font);
	}
	else if(on_main_menu_ && main_menu_ != nullptr)
	{
		main_menu_->Render(renderer_3d, sprite_renderer, font);
	}
	else
	{
		current_scene_->Render(renderer_3d, sprite_renderer, font);
	}
}

void StateManager::PushScene(Scene* scene)
{
	scenes_.push(scene);
	current_scene_ = scenes_.front();
}

void StateManager::PushLevel(Level* level, const char* file_name, OBJMeshLoader& mesh_loader)
{
	level->SetPauseMenu(pause_menu_);
	loading_thread_ = std::thread([this, level, file_name, &mesh_loader]
	{
		is_loading_ = true;
		level->LoadFromFile(file_name, loading_screen_, mesh_loader);
		is_loading_ = false;
	});
	loading_thread_.detach();
	scenes_.push(level);
	current_scene_ = scenes_.front();
}

void StateManager::Pause()
{
	Level* lvl = reinterpret_cast<Level*>(scenes_.front());
 	if(lvl)
 	{
 		lvl->Pause();
 	}
}

void StateManager::Unpause()
{
	Level* lvl = reinterpret_cast<Level*>(scenes_.front());
	if(lvl)
	{
		lvl->Unpause();
	}
}

Scene* StateManager::NextScene()
{
	Scene* oldScene = current_scene_;
	if(!on_main_menu_)
	{
		scenes_.pop();
	}
	on_main_menu_ = false;
	current_scene_ = scenes_.front();
	return oldScene;
}

void StateManager::SwitchToMainMenu()
{
	while (!scenes_.empty())
	{
		delete scenes_.front();
		scenes_.pop();
	}
	on_main_menu_ = true;
}

void StateManager::SetPauseMenu(Menu* pause_menu)
{
	pause_menu_ = pause_menu;
}

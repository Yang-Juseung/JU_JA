/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode3.cpp
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Juseung Yang, Jaeyeong An
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Mode3.h"


Mode3::Mode3()
	: modeNext(CS230::InputKey::Keyboard::Enter),
	modeReload(CS230::InputKey::Keyboard::R),
	player(nullptr),
	camera(math::rect2{ math::vec2(Engine::GetWindow().GetSize().x * 0.15,0), math::vec2(Engine::GetWindow().GetSize().x * 0.35, 0) })
{
}

void Mode3::Load()
{
	player = new Player(math::vec2(150, Mode3::floor), camera);
	player->Load();

	background.Add("assets/Mountains.png", 2);
	background.Add("assets/foreground.png", 1);
	background.Add("assets/clouds.png", 4);
	camera.SetPosition(math::vec2(0));
	camera.SetExtent(math::irect2{ math::ivec2(0), math::ivec2{background.Size().x - Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y} });
}
void Mode3::Update(double dt)
{
	player->Update(dt);


	if (modeNext.IsKeyReleased()) 
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode3));
	}

	if (modeReload.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}

	camera.Update(player->GetPosition());
}
void Mode3::Unload()
{
	delete player;
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x87c9fbFF);
	background.Draw(camera);

	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	player->Draw(cameraMatrix);

}
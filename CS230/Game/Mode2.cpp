/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode2.cpp
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Juseung Yang
Creation date: 3/15/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	
#include "Screens.h"
#include "Mode2.h"

Mode2::Mode2() 
	: modeNext(CS230::InputKey::Keyboard::Enter),
	modeReload(CS230::InputKey::Keyboard::R) ,
	ship(new Ship(math::vec2(Engine::GetWindow().GetSize()/2) ) )
{}

void Mode2::Load() 
{
	ship = new Ship(math::vec2(Engine::GetWindow().GetSize() / 2));
	ship->Load();
}
void Mode2::Update(double dt) 
{
	ship->Update(dt);

	if (modeNext.IsKeyReleased()) {
		Engine::GetGameStateManager().Shutdown();
	}

	if (modeReload.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}
}
void Mode2::Unload() 
{
	delete ship;
}

void Mode2::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	ship->Draw();
}

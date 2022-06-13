
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
#include "Gameover.h"

Game_end::Game_end()
	: modeNext(CS230::InputKey::Keyboard::Enter),
	modeReload(CS230::InputKey::Keyboard::R),
	hero(nullptr)
{
}
void Game_end::Load()
{
	background.Add("Assets / Gameover.png",1);
}

void Game_end::Update(double dt)
{
	hero->Update(dt);
	if (modeNext.IsKeyReleased())
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::GAME_OVER));
	}

	if (modeReload.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}
}
void Game_end::Unload()
{
	delete hero;
}

void Game_end::Draw()
{
	Engine::GetWindow().Clear(0x87c9fbFF);
}

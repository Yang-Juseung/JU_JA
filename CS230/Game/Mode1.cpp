/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode1.cpp
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Juseung Yang
Creation date: 3/15/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Mode1.h"


Mode1::Mode1()
	: modeNext(CS230::InputKey::Keyboard::Enter),
	modeReload(CS230::InputKey::Keyboard::R),
	hero(nullptr),
	ball1(new Ball(math::vec2(600, Mode1::floor))),
	ball2(new Ball(math::vec2(2700, Mode1::floor))),
	ball3(new Ball(math::vec2(4800, Mode1::floor))),
	camera(math::rect2{ math::vec2(Engine::GetWindow().GetSize().x * 0.15,0), math::vec2(Engine::GetWindow().GetSize().x * 0.35, Engine::GetWindow().GetSize().y) })
{
}

void Mode1::Load() 
{
	hero = new Hero(math::vec2(150, Mode1::floor), camera);
	ball1 = new Ball(math::vec2(600, Mode1::floor));
	ball2 = new Ball(math::vec2(2700, Mode1::floor));
	ball3 = new Ball(math::vec2(4800, Mode1::floor));
	hero->Load();
	ball1->Load();
	ball2->Load();
	ball3->Load();

	background.Add("assets/Mountains.png", 2);
	background.Add("assets/foreground.png",1);
	background.Add("assets/clouds.png", 4);
	camera.SetPosition(math::vec2(0));
	camera.SetExtent(math::irect2{ math::ivec2(0), math::ivec2{background.Size().x - Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y} });
}
void Mode1::Update(double dt) 
{
	hero->Update(dt);

	ball1->Update(dt);
	ball2->Update(dt);
	ball3->Update(dt);

	if (modeNext.IsKeyReleased()) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode2));
	}

	if (modeReload.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}

	camera.Update(hero->GetPosition());
}
void Mode1::Unload() 
{
	delete hero;
	delete ball1;
	delete ball2;
	delete ball3;
}

void Mode1::Draw()
{
	Engine::GetWindow().Clear(0x87c9fbFF);
	background.Draw(camera);

	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	hero->Draw(cameraMatrix);
	ball1->Draw(cameraMatrix);
	ball2->Draw(cameraMatrix);
	ball3->Draw(cameraMatrix);

}
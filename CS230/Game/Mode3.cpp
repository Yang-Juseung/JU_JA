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
	  hero(nullptr),
	  foothold1(new Foothold(math::vec2(600, 200))),
	  foothold2(new Foothold(math::vec2(400, 400))),
	  foothold3(new Foothold(math::vec2(200, 600))),
	  foothold4(new Foothold(math::vec2(600, 700))),
	  foothold5(new Foothold(math::vec2(100, 800))),
	  camera(math::rect2{ math::vec2(Engine::GetWindow().GetSize().x * 0.15,Engine::GetWindow().GetSize().y * 0.2), math::vec2(Engine::GetWindow().GetSize().x * 0.35, Engine::GetWindow().GetSize().y * 0.35) })
{
}

void Mode3::Load()
{
	hero = new Hero(math::vec2(150, Mode3::floor), camera);
	foothold1 = new Foothold(math::vec2(600, 200));
	foothold2 = new Foothold(math::vec2(400, 400));
	foothold3 = new Foothold(math::vec2(200, 600));
	foothold4 = new Foothold(math::vec2(600, 700));
	foothold5 = new Foothold(math::vec2(100, 800));
	hero->Load();
	foothold1->Load();
	foothold2->Load();
	foothold3->Load();
	foothold4->Load();
	foothold5->Load();

	background.Add("assets/Mountains.png", 2);
	background.Add("assets/foreground.png", 1);
	background.Add("assets/clouds.png", 4);
	camera.SetPosition(math::vec2(0));
	camera.SetExtent(math::irect2{ math::ivec2(0), math::ivec2{background.Size().x - Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y+10000} });
}
void Mode3::Update(double dt)
{
	hero->Update(dt);

	foothold1->Update(dt, hero);
	foothold2->Update(dt, hero);
	foothold3->Update(dt, hero);
	foothold4->Update(dt, hero);
	foothold5->Update(dt, hero);

	if (modeNext.IsKeyReleased()) 
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode3));
	}

	if (modeReload.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}

	camera.Update(hero->GetPosition());

}
void Mode3::Unload()
{
	delete hero;
	delete foothold1;
	delete foothold2;
	delete foothold3;
	delete foothold4;
	delete foothold5;
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x87c9fbFF);
	background.Draw(camera);

	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	math::TransformMatrix identityMatrix;
	hero->Draw(cameraMatrix);
	foothold1->Draw(cameraMatrix);
	foothold2->Draw(cameraMatrix);
	foothold3->Draw(cameraMatrix);
	foothold4->Draw(cameraMatrix);
	foothold5->Draw(cameraMatrix);
}
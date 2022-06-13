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
#include <doodle/drawing.hpp>


Mode3::Mode3()
	: modeNext(CS230::InputKey::Keyboard::Enter),
	modeReload(CS230::InputKey::Keyboard::R),
	player(nullptr),
	foothold1(new Foothold(math::vec2(600, 200))),
	foothold2(new Foothold(math::vec2(400, 400))),
	foothold3(new Foothold(math::vec2(200, 600))),
	foothold4(new Foothold(math::vec2(600, 700))),
	foothold5(new Foothold(math::vec2(100, 800))),
	foothold6(new Foothold(math::vec2(800, 900))),
	foothold7(new Foothold(math::vec2(900, 1100))),
	foothold8(new Foothold(math::vec2(1100, 1100))),
	foothold9(new Foothold(math::vec2(700, 1300))),
	foothold10(new Foothold(math::vec2(400, 1400))),
	camera(math::rect2{ math::vec2(0,Engine::GetWindow().GetSize().y * 0.2), math::vec2(Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y * 0.35) }),
	score(0),
	coin1(new Coin(math::vec2(200, 650))),
	coin2(new Coin(math::vec2(400, 1450))),
	coin3(new Coin(math::vec2(700, 1100)))
{
}

void Mode3::Load()
{
	player = new Player(math::vec2(150, Mode3::floor), camera);
	player->Load();
	foothold1 = new Foothold(math::vec2(600, 200));
	foothold2 = new Foothold(math::vec2(400, 400));
	foothold3 = new Foothold(math::vec2(200, 600));
	foothold4 = new Foothold(math::vec2(600, 700));
	foothold5 = new Foothold(math::vec2(100, 800));
	foothold6 = new Foothold(math::vec2(800, 900));
	foothold7 = (new Foothold(math::vec2(900, 1100)));
	foothold8 = new Foothold(math::vec2(1100, 1100));
	foothold9 = new Foothold(math::vec2(700, 1300));
	foothold10 = new Foothold(math::vec2(400, 1400));
	coin1 = new Coin(math::vec2(200, 650));
	coin2 = new Coin(math::vec2(400, 1450));
	coin3 = new Coin(math::vec2(700, 1100));
	foothold1->Load();
	foothold2->Load();
	foothold3->Load();
	foothold4->Load();
	foothold5->Load();
	foothold6->Load();
	foothold7->Load();
	foothold8->Load();
	foothold9->Load();
	foothold10->Load();
	coin1->Load();
	coin2->Load();
	coin3->Load();

	background.Add("assets/Mountains.png", 2);
	background.Add("assets/foreground.png", 1);
	background.Add("assets/clouds.png", 4);
	camera.SetPosition(math::vec2(0));
	camera.SetExtent(math::irect2{ math::ivec2(0), math::ivec2{background.Size().x - Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y+10000} });
}
void Mode3::Update(double dt)
{
	player->Update(dt);

	foothold1->Update(dt, player);
	foothold2->Update(dt, player);
	foothold3->Update(dt, player);
	foothold4->Update(dt, player);
	foothold5->Update(dt, player);
	foothold6->Update(dt, player);
	foothold7->Update(dt, player);
	foothold8->Update(dt, player);
	foothold9->Update(dt, player);
	foothold10->Update(dt, player);

	coin1->Update(dt,player);
	coin2->Update(dt, player);
	coin3->Update(dt, player);

	if (modeNext.IsKeyReleased()) 
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode3));
	}

	if (modeReload.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}

	score = coin1->isCollided + coin2->isCollided + coin3->isCollided;

	camera.Update(player->GetPosition());
}
void Mode3::Unload()
{
	delete player;
	delete foothold1;
	delete foothold2;
	delete foothold3;
	delete foothold4;
	delete foothold5;
	delete foothold6;
	delete foothold7;
	delete foothold8;
	delete foothold9;
	delete foothold10;
	delete coin1;
	delete coin2;
	delete coin3;
	score = 0;
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x87c9fbFF);
	background.Draw(camera);

	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	foothold1->Draw(cameraMatrix);
	foothold2->Draw(cameraMatrix);
	foothold3->Draw(cameraMatrix);
	foothold4->Draw(cameraMatrix);
	foothold5->Draw(cameraMatrix);
	foothold6->Draw(cameraMatrix);
	foothold7->Draw(cameraMatrix);
	foothold8->Draw(cameraMatrix);
	foothold9->Draw(cameraMatrix);
	foothold10->Draw(cameraMatrix);
	player->Draw(cameraMatrix);

	if (coin1->isCollided != true)
	{
		coin1->Draw(cameraMatrix);
	}
	
	if (coin2->isCollided != true)
	{
		coin2->Draw(cameraMatrix);
	}

	if (coin3->isCollided != true)
	{
		coin3->Draw(cameraMatrix);
	}

	doodle::draw_text("Score : "+std::to_string(score),10,10 );
}
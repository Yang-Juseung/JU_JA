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
	foothold11(new Foothold(math::vec2(600, 1600))),
	foothold12(new Foothold(math::vec2(200, 1850))),
	foothold13(new Foothold(math::vec2(1000, 2000))),
	foothold14(new Foothold(math::vec2(0, 2000))),
	foothold15(new Foothold(math::vec2(250, 2100))),
	foothold16(new Foothold(math::vec2(500, 2300))),
	foothold17(new Foothold(math::vec2(750, 2500))),
	foothold18(new Foothold(math::vec2(850, 2700))),
	foothold19(new Foothold(math::vec2(900, 2950))),
	foothold20(new Foothold(math::vec2(600, 3100))),
	foothold21(new Foothold(math::vec2(200, 3300))),
	foothold22(new Foothold(math::vec2(100, 3500))),
	foothold23(new Foothold(math::vec2(550, 3750))),
	camera(math::rect2{ math::vec2(0,Engine::GetWindow().GetSize().y * 0.2), math::vec2(Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y * 0.35) }),
	score(0),
	coin1(new Coin(math::vec2(200, 650))),
	coin2(new Coin(math::vec2(400, 1450))),
	coin3(new Coin(math::vec2(1000, 1800))),
	coin4(new Coin(math::vec2(900, 2600))),
	coin5(new Coin(math::vec2(50, 3600))),
	coin6(new Coin(math::vec2(1000, 3850)))
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
	foothold11 = (new Foothold(math::vec2(600, 1600)));
	foothold12 = (new Foothold(math::vec2(100, 1850)));
	foothold13 = (new Foothold(math::vec2(1000, 2000)));
	foothold14 = (new Foothold(math::vec2(0, 2000)));
	foothold15 = (new Foothold(math::vec2(250, 2100)));
	foothold16 = (new Foothold(math::vec2(500, 2300)));
	foothold17 = (new Foothold(math::vec2(750, 2500)));
	foothold18 = (new Foothold(math::vec2(850, 2700)));
	foothold19 = (new Foothold(math::vec2(900, 2950)));
	foothold20 = (new Foothold(math::vec2(600, 3100)));
	foothold21 = (new Foothold(math::vec2(200, 3300)));
	foothold22 = (new Foothold(math::vec2(100, 3500)));
	foothold23 = (new Foothold(math::vec2(550, 3750)));
	coin1 = new Coin(math::vec2(200, 650));
	coin2 = new Coin(math::vec2(400, 1450));
	coin3 = new Coin(math::vec2(1000, 1800));
	coin4 = new Coin(math::vec2(900, 2600));
	coin5 = new Coin(math::vec2(50, 3600));
	coin6 = new Coin(math::vec2(1000, 3850));
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
	foothold11->Load();
	foothold12->Load();
	foothold13->Load();
	foothold14->Load();
	foothold15->Load();
	foothold16->Load();
	foothold17->Load();
	foothold18->Load();
	foothold19->Load();
	foothold20->Load();
	foothold21->Load();
	foothold22->Load();
	foothold23->Load();
	coin1->Load();
	coin2->Load();
	coin3->Load();
	coin4->Load();
	coin5->Load();
	coin6->Load();

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
	foothold11->Update(dt, player);
	foothold12->Update(dt, player);
	foothold13->Update(dt, player);
	foothold14->Update(dt, player);
	foothold15->Update(dt, player);
	foothold16->Update(dt, player);
	foothold17->Update(dt, player);
	foothold18->Update(dt, player);
	foothold19->Update(dt, player);
	foothold20->Update(dt, player);
	foothold21->Update(dt, player);
	foothold22->Update(dt, player);
	foothold23->Update(dt, player);
	coin1->Update(dt,player);
	coin2->Update(dt, player);
	coin3->Update(dt, player);
	coin4->Update(dt, player);
	coin5->Update(dt, player);
	coin6->Update(dt, player);

	if (modeNext.IsKeyReleased()) 
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode3));
	}

	if (modeReload.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}

	score = coin1->isCollided + coin2->isCollided + coin3->isCollided + coin4->isCollided + coin5->isCollided + coin6->isCollided;

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
	delete foothold11;
	delete foothold12;
	delete foothold13;
	delete foothold14;
	delete foothold15;
	delete foothold16;
	delete foothold17;
	delete foothold18;
	delete foothold19;
	delete foothold20;
	delete foothold21;
	delete foothold22;
	delete foothold23;
	delete coin1;
	delete coin2;
	delete coin3;
	delete coin4;
	delete coin5;
	delete coin6;
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
	foothold11->Draw(cameraMatrix);
	foothold12->Draw(cameraMatrix);
	foothold13->Draw(cameraMatrix);
	foothold14->Draw(cameraMatrix);
	foothold15->Draw(cameraMatrix);
	foothold16->Draw(cameraMatrix);
	foothold17->Draw(cameraMatrix);
	foothold18->Draw(cameraMatrix);
	foothold19->Draw(cameraMatrix);
	foothold20->Draw(cameraMatrix);
	foothold21->Draw(cameraMatrix);
	foothold22->Draw(cameraMatrix);
	foothold23->Draw(cameraMatrix);
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
	
	if (coin4->isCollided != true)
	{
		coin4->Draw(cameraMatrix);
	}

	if (coin5->isCollided != true)
	{
		coin5->Draw(cameraMatrix);
	}

	if (coin6->isCollided != true)
	{
		coin6->Draw(cameraMatrix);
	}

	doodle::draw_text("Score : "+std::to_string(score),10,10 );
	if (score == 6)
	{
		doodle::draw_text("You collected all the coins!! You Win!!", 60, 60);
	}
}
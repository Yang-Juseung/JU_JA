/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Foothold.cpp
Project: CS230
Author: Jaeyeong An
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include "Foothold.h"
#include "Mode3.h"
#include "..\Engine\Engine.h"
#include "Paddle_Anims.h"

Foothold::Foothold(math::vec2 startPos)
	: initPosition(startPos),
	position(position)
	//currState(&stateLand)
{
}

void Foothold::Load()
{
	sprite.Load("assets/Paddle.spt");
	position = initPosition;
	//velocity = { 0,0 };
	//currState = &stateLand;
	//currState->Enter(this);
}

void Foothold::Update(double dt, Player* player)
{
	//currState->Update(this, dt);
	sprite.Update(dt);
	//position += velocity * dt;
	//currState->TestForExit(this);

	objectMatrix = math::TranslateMatrix(position);
	
	if (player->GetPosition().y <= position.y + 50 &&
		player->GetPosition().y >= position.y &&
		player->GetPosition().x > position.x - 50 &&
		player->GetPosition().x < position.x + 50  )
	{
		if (player->GetVelocity().y < 0)
		{
			player->SetPosition(math::vec2(player->GetPosition().x, position.y + 50));
			player->SetVelocity(math::vec2(player->GetVelocity().x, 0));
		}
		if (player->currState == &player->stateFalling)
		{
			player->ChangeState(&player->stateRunning);
		}
	}
	
}

void Foothold::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(objectMatrix * cameraMatrix);
}


math::vec2 Foothold::GetPosition()
{
	return position;
}
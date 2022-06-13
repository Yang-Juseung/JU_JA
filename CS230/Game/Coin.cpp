/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Coin.cpp
Project: CS230
Author: Jaeyeong An
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include "Coin.h"
#include "Mode3.h"
#include "..\Engine\Engine.h"
#include "Ball_Anims.h"
#include <doodle/drawing.hpp>

Coin::Coin(math::vec2 startPos)
	: initPosition(startPos),
	position(position)
{
}

void Coin::Load()
{
	sprite.Load("assets/Coin.spt");
	position = initPosition;
}

void Coin::Update(double dt, Player* player)
{
	sprite.Update(dt);

	objectMatrix = math::TranslateMatrix(position);

	if (player->GetPosition().y <= position.y + 50 &&
		player->GetPosition().y >= position.y - 50 &&
		player->GetPosition().x > position.x -  50 &&
		player->GetPosition().x < position.x +  50)
	{
		isCollided = true;
		coins++;
	}
}

void Coin::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(objectMatrix * cameraMatrix);
}


math::vec2 Coin::GetPosition()
{
	return position;
}


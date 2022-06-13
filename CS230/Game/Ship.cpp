/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Juseung Yang
Creation date: 3/26/2022
-----------------------------------------------------------------*/

#include "Ship.h"
#include "../Engine/Engine.h"

Ship::Ship(math::vec2 startPos)
	:rotateCounterKey(CS230::InputKey::Keyboard::A),
	rotateClockKey(CS230::InputKey::Keyboard::D),
	accelerateKey(CS230::InputKey::Keyboard::W),
	startPos(startPos)
{
}

void Ship::Load()
{
	sprite.Load("assets/Ship.png", { math::ivec2{50,41}, math::ivec2{35,0}, math::ivec2{65,0} } );
	flameLeft.Load("assets/flame.png", { math::ivec2{8,16} });
	flameRight.Load("assets/flame.png", { math::ivec2{8,16} });
	position = startPos;
}

void Ship::Update(double dt)
{

	if ( rotateCounterKey.IsKeyDown() )
	{
		currentRotation -= speed * dt;
	}

	if ( rotateClockKey.IsKeyDown() )
	{
		currentRotation += speed * dt;
	}

	if ( accelerateKey.IsKeyDown() )
	{
		math::vec2 shipVector = math::RotateMatrix(currentRotation) * math::vec2(0,accel*dt);
		velocity += shipVector;
	}

	velocity -= (velocity * Ship::drag * dt);

	//Log a debug message for the velocity "Velocity = " [velocity.x] "," [velocity.y] 
	Engine::GetLogger().LogDebug("Velocity = ["+ std::to_string(velocity.x)+"] , ["+ std::to_string(velocity.y)+"]");
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	TestForWrap();

	objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(currentRotation) * math::ScaleMatrix(math::vec2(0.75) );
}

void Ship::TestForWrap()
{
	if (position.x < 0 - sprite.GetTextureSize().x )
	{
		position.x = Engine::GetWindow().GetSize().x + sprite.GetTextureSize().x;
	}

	if (position.x > Engine::GetWindow().GetSize().x+ sprite.GetTextureSize().x)
	{
		position.x = 0 - sprite.GetTextureSize().x;
	}

	if (position.y < 0 - sprite.GetTextureSize().y)
	{
		position.y = Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y;
	}

	if (position.y > Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y)
	{
		position.y = 0 - sprite.GetTextureSize().y;
	}

}

void Ship::Draw()
{
	sprite.Draw(objectMatrix);
	flameLeft.Draw(objectMatrix * math::TranslateMatrix( -(sprite.GetHotSpot(0) - sprite.GetHotSpot(1) ) ) );
	flameRight.Draw(objectMatrix * math::TranslateMatrix( -(sprite.GetHotSpot(0) - sprite.GetHotSpot(2) ) ) );
}
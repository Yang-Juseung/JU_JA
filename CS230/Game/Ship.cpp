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
#include "../Engine/TransformMatrix.h"
#include "Flame_Anims.h"

Ship::Ship(math::vec2 startPos)
	:rotateCounterKey(CS230::InputKey::Keyboard::A),
	rotateClockKey(CS230::InputKey::Keyboard::D),
	accelerateKey(CS230::InputKey::Keyboard::W),
	startPos(startPos)
{
}

void Ship::Load()
{
	sprite.Load( "assets/Ship.spt" );
	flameLeft.Load( "assets/flame.spt" );
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	flameRight.Load( "assets/flame.spt" );
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	position = startPos;
}

void Ship::Update(double dt)
{
	flameLeft.Update(dt);
	flameRight.Update(dt);
	if ( rotateCounterKey.IsKeyDown() )
	{
		currentRotation += speed * dt;
	}

	if ( rotateClockKey.IsKeyDown() )
	{
		currentRotation -= speed * dt;
	}

	if ( accelerateKey.IsKeyDown() )
	{
		math::vec2 shipVector = math::RotateMatrix(currentRotation) * math::vec2(0,accel*dt);
		velocity += shipVector;
		if (isAccelerating == false)
		{
			flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			isAccelerating = true;
		}
	}
	else
	{
		if (isAccelerating == true)
		{
			flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			isAccelerating = false;
		}
	}

	velocity -= (velocity * Ship::drag * dt);

	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	TestForWrap();

	objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(currentRotation) * math::ScaleMatrix(math::vec2(0.75) );
}

void Ship::TestForWrap()
{
	if (position.x < 0 - sprite.GetFrameSize().x / 2.0)
	{
		position.x = Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0;
	}

	if (position.x > Engine::GetWindow().GetSize().x+ sprite.GetFrameSize().x / 2.0)
	{
		position.x = 0 - sprite.GetFrameSize().x / 2.0;
	}

	if (position.y < 0 - sprite.GetFrameSize().y / 2.0)
	{
		position.y = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0;
	}

	if (position.y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0)
	{
		position.y = 0 - sprite.GetFrameSize().y / 2.0;
	}

}

void Ship::Draw()
{
	sprite.Draw(objectMatrix);
	flameLeft.Draw(objectMatrix * math::TranslateMatrix(sprite.GetHotSpot(1)));
	flameRight.Draw(objectMatrix * math::TranslateMatrix(sprite.GetHotSpot(2)));
}
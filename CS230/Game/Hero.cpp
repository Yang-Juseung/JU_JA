/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Juseung Yang
Creation date: 3/26/2022
-----------------------------------------------------------------*/

#include "Hero.h"
#include "../Engine/Engine.h"
#include "Mode1.h"
#include "../Engine/Camera.h"

Hero::Hero(math::vec2 startPos, const CS230::Camera& camera)
	: moveLeftKey(CS230::InputKey::Keyboard::Left),
	moveRightKey(CS230::InputKey::Keyboard::Right),
	startPos(startPos),
	moveUpKey(CS230::InputKey::Keyboard::Up),
	isJumping(false),
	isRising(false),
	isFlipping(false),
	camera(camera),
	currState()
{
}

void Hero::Load()
{
	sprite.Load("assets/Hero.png",math::ivec2(56,14));
	position = startPos;
	isJumping = false;
	isRising = false;

	currState = &stateIdle;
	currState->Enter(this);

}

void Hero::Update(double dt)
{
	
	currState->Update(this, dt);
	position += velocity * dt;
	currState->TestForExit(this);
	

	if ( position.x > camera.GetPosition().x + Engine::GetWindow().GetSize().x - (Hero::sprite.GetTextureSize().x / 2))
	{
		position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - (Hero::sprite.GetTextureSize().x/2);
		velocity.x = 0;
	}

	if (position.x < camera.GetPosition().x + (Hero::sprite.GetTextureSize().x / 2))
	{
		position.x = camera.GetPosition().x + (Hero::sprite.GetTextureSize().x / 2);
		velocity.x = 0;
	}

	objectMatrix = math::TranslateMatrix(position);

	if (isFlipping)
	{
		objectMatrix *= math::ScaleMatrix(math::vec2(-1.0, 1.0) );
	}
}

void Hero::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(cameraMatrix * objectMatrix);
}


math::vec2 Hero::GetPosition()
{
	return position;
}

void Hero::ChangeState(State* newState) 
{
	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}

void Hero::State_Jumping::Enter(Hero* hero) 
{
	hero->velocity.y = Hero::jumpVelocity;   //Set the velocity.y
}
void Hero::State_Jumping::Update(Hero* hero, double dt) 
{
	hero->velocity.y -= Mode1::gravity * dt;  //Apply Gravity
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}
void Hero::State_Jumping::TestForExit(Hero* hero) 
{
	if (hero->moveUpKey.IsKeyDown() == false) 
	{  
		hero->velocity.y = 0;
	}
	if (hero->velocity.y <= 0) 
	{
		hero->ChangeState(&hero->stateFalling);
	}
}

//Idle
void Hero::State_Idle::Enter([[maybe_unused]]Hero* hero)
{

}

void Hero::State_Idle::Update([[maybe_unused]] Hero* hero, [[maybe_unused]] double dt)
{

}

void Hero::State_Idle::TestForExit(Hero* hero)
{
	if (hero->moveUpKey.IsKeyDown())
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->moveLeftKey.IsKeyDown() || hero->moveRightKey.IsKeyDown())
	{
		hero->ChangeState(&hero->stateRunning);
	}
	
}

//Running
void Hero::State_Running::Enter(Hero* hero)
{
	if (hero->moveLeftKey.IsKeyDown())
	{
		hero->isFlipping = true;
	}

	if (hero->moveRightKey.IsKeyDown())
	{
		hero->isFlipping = false;
	}
}

void Hero::State_Running::Update(Hero* hero, double dt)
{
	hero->UpdateXVelocity(dt);
}

void Hero::State_Running::TestForExit(Hero* hero)
{
	if (hero->moveUpKey.IsKeyDown())
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if(hero->velocity.x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	else
	{
		if (hero->moveLeftKey.IsKeyDown())
		{
			if (hero->velocity.x > 0)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
		}

		if (hero->moveRightKey.IsKeyDown())
		{
			if (hero->velocity.x < 0)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
		}
	}
}

//Skidding
void Hero::State_Skidding::Enter([[maybe_unused]] Hero* hero)
{ 
}

void Hero::State_Skidding::Update(Hero* hero, double dt)
{
	// drag + accel
	if (hero->velocity.x > 0)
	{
		hero->velocity.x -= hero->Xdrag * dt;
		hero->velocity.x -= hero->Xacceleration * dt;
	}
	else if (hero->velocity.x < 0)
	{
		hero->velocity.x += hero->Xdrag * dt;
		hero->velocity.x += hero->Xacceleration * dt;
	}
}

void Hero::State_Skidding::TestForExit(Hero* hero)
{
	if (hero->moveUpKey.IsKeyDown())
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->moveLeftKey.IsKeyDown() && hero->velocity.x <= 0)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if(hero->moveRightKey.IsKeyDown() && hero->velocity.x >= 0)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if(!hero->moveRightKey.IsKeyDown() && !hero->moveLeftKey.IsKeyDown())
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

//Falling
void Hero::State_Falling::Enter([[maybe_unused]] Hero* hero)
{
}

void Hero::State_Falling::Update(Hero* hero, double dt)
{
	hero->UpdateXVelocity(dt);
	hero->velocity.y -= Mode1::gravity * dt;
}

void Hero::State_Falling::TestForExit(Hero* hero)
{
	if (hero->position.y <= Mode1::floor)
	{
		hero->velocity.y = 0;
		hero->position.y = Mode1::floor;
		if (hero->velocity.x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown())
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else if(hero->velocity.x < 0)
		{
			if (hero->moveRightKey.IsKeyDown())
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else
		{
			hero->ChangeState(&hero->stateIdle);
		}
	}
}

void Hero::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown())
	{
		velocity.x -= Xacceleration * dt;

		if (velocity.x < -Xmaxvelocity)
		{
			velocity.x = -Xmaxvelocity;
		}
	}

	if (moveRightKey.IsKeyDown())
	{
		velocity.x += Xacceleration * dt;

		if (velocity.x > Xmaxvelocity)
		{
			velocity.x = Xmaxvelocity;
		}
	}

	if (!moveLeftKey.IsKeyDown() && !moveRightKey.IsKeyDown())
	{
		if (velocity.x < 0)
		{
			velocity.x += Xdrag * dt;

			if (velocity.x > 0)
			{
				velocity.x = 0;
			}
		}

		else if (velocity.x > 0)
		{
			velocity.x -= Xdrag * dt;

			if (velocity.x < 0)
			{
				velocity.x = 0;
			}
		}

	}
}


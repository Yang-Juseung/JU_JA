/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Juseung Yang
Creation date: 3/26/2022
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Camera.h"
#include "Mode1.h"
#include "Hero.h"
#include "Hero_Anims.h"

Hero::Hero(math::vec2 startPos, const CS230::Camera& camera)
	: moveLeftKey(CS230::InputKey::Keyboard::Left),
	moveRightKey(CS230::InputKey::Keyboard::Right),
	startPos(startPos),
	moveUpKey(CS230::InputKey::Keyboard::Up),
	isJumping(false),
	isRising(false),
	isFlipping(false),
	camera(camera),
	currState(&stateIdle)
{
}

void Hero::Load()
{
	sprite.Load("assets/Hero.spt");
	position = startPos;
	velocity = {0,0};
	isJumping = false;
	currState = &stateIdle;
	currState->Enter(this);
}

void Hero::Update(double dt)
{	
	currState->Update(this, dt);
	sprite.Update(dt);
	position += velocity * dt;
	currState->TestForExit(this);
	

	if ( position.x > camera.GetPosition().x + Engine::GetWindow().GetSize().x - (sprite.GetFrameSize().x / 2))
	{
		position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - (sprite.GetFrameSize().x /2);
		velocity.x = 0;
	}
	
	if (position.x < camera.GetPosition().x + (sprite.GetFrameSize().x / 2))
	{
		position.x = camera.GetPosition().x + (sprite.GetFrameSize().x / 2);
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

void Hero::State_Idle::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
}

void Hero::State_Idle::Update(Hero*, double) {}

void Hero::State_Idle::TestForExit(Hero* hero)
{
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->moveUpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Jumping::Enter(Hero* hero) 
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->velocity.y = Hero::jumpVelocity;   
}
void Hero::State_Jumping::Update(Hero* hero, double dt) 
{
	hero->velocity.y -= Mode1::gravity * dt; 
	hero->UpdateXVelocity(dt);  
}
void Hero::State_Jumping::TestForExit(Hero* hero) 
{
	if (hero->moveUpKey.IsKeyDown() == false) 
	{  
		hero->ChangeState(&hero->stateFalling);
		hero->velocity.y = 0;
	}
	else if (hero->velocity.y <= 0) 
	{
		hero->ChangeState(&hero->stateFalling);
	}
}

//Running
void Hero::State_Running::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->isFlipping = true;
	}
	if (hero->moveRightKey.IsKeyDown() == true)
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
	if (hero->moveLeftKey.IsKeyDown() == true && hero-> velocity.x > 0)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->moveRightKey.IsKeyDown() == true && hero->velocity.x < 0)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->velocity.x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->moveUpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

//Skidding
void Hero::State_Skidding::Enter(Hero* hero)
{ 
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}

void Hero::State_Skidding::Update(Hero* hero, double dt)
{
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
void Hero::State_Falling::Enter( Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
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


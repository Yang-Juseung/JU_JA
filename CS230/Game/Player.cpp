/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.cpp
Project: CS230
Author: Juseung Yang
Creation date: 3/26/2022
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Camera.h"
#include "Mode3.h"
#include "player.h"
#include "Player_Anime.h"

Player::Player(math::vec2 startPos, const CS230::Camera& camera)
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

void Player::Load()
{
	sprite.Load("assets/Player.spt");
	position = startPos;
	velocity = { 0,0 };
	isJumping = false;
	currState = &stateIdle;
	currState->Enter(this);
}

void Player::Update(double dt)
{
	currState->Update(this, dt);
	sprite.Update(dt);
	position += velocity * dt;
	currState->TestForExit(this);


	if (position.x > camera.GetPosition().x + Engine::GetWindow().GetSize().x - (sprite.GetFrameSize().x / 2))
	{
		position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - (sprite.GetFrameSize().x / 2);
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
		objectMatrix *= math::ScaleMatrix(math::vec2(-1.0, 1.0));
	}
}

void Player::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(cameraMatrix * objectMatrix);
}


math::vec2 Player::GetPosition()
{
	return position;
}

void Player::ChangeState(State* newState)
{
	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}

void Player::State_Idle::Enter(Player* Player)
{
	Player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Idle_Anim));
}

void Player::State_Idle::Update(Player* Player, double)
{
	Player->velocity.y = 0;
}

void Player::State_Idle::TestForExit(Player* Player)
{
	if (Player->moveLeftKey.IsKeyDown() == true)
	{
		Player->ChangeState(&Player->stateRunning);
	}
	if (Player->moveRightKey.IsKeyDown() == true)
	{
		Player->ChangeState(&Player->stateRunning);
	}
	if (Player->moveUpKey.IsKeyDown() == true)
	{
		Player->ChangeState(&Player->stateJumping);
	}

	/*if (Player->position.y > Mode3::floor && 
		Player->velocity.y < 0)
	{
		Player->ChangeState(&Player->stateFalling);
	}*/
}

void Player::State_Jumping::Enter(Player* Player)
{
	Player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Jump_Anim));
	Player->velocity.y = Player::jumpVelocity;
}
void Player::State_Jumping::Update(Player* Player, double dt)
{
	Player->velocity.y -= Mode3::gravity * dt;
	Player->UpdateXVelocity(dt);
}
void Player::State_Jumping::TestForExit(Player* Player)
{
	if (Player->moveUpKey.IsKeyDown() == false)
	{
		Player->ChangeState(&Player->stateFalling);
		Player->velocity.y = 0;
	}
	else if (Player->velocity.y <= 0)
	{
		Player->ChangeState(&Player->stateFalling);
	}
}

//Running
void Player::State_Running::Enter(Player* Player)
{
	Player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Run_Anim));
	if (Player->moveLeftKey.IsKeyDown() == true)
	{
		Player->isFlipping = true;
	}
	if (Player->moveRightKey.IsKeyDown() == true)
	{
		Player->isFlipping = false;
	}
}

void Player::State_Running::Update(Player* Player, double dt)
{
	Player->UpdateXVelocity(dt);
}

void Player::State_Running::TestForExit(Player* Player)
{
	if (Player->moveLeftKey.IsKeyDown() == true && Player->velocity.x > 0)
	{
		Player->ChangeState(&Player->stateSkidding);
	}
	if (Player->moveRightKey.IsKeyDown() == true && Player->velocity.x < 0)
	{
		Player->ChangeState(&Player->stateSkidding);
	}
	if (Player->velocity.x == 0)
	{
		Player->ChangeState(&Player->stateIdle);
	}
	if (Player->moveUpKey.IsKeyDown() == true)
	{
		Player->ChangeState(&Player->stateJumping);
	}
	if (Player->GetPosition().y > Mode3::floor)
	{
		Player->ChangeState(&Player->stateFalling);
	}
}

//Skidding
void Player::State_Skidding::Enter(Player* Player)
{
	Player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Fall_Anim));
}

void Player::State_Skidding::Update(Player* Player, double dt)
{
	if (Player->velocity.x > 0)
	{
		Player->velocity.x -= Player->Xdrag * dt;
		Player->velocity.x -= Player->Xacceleration * dt;
	}
	else if (Player->velocity.x < 0)
	{
		Player->velocity.x += Player->Xdrag * dt;
		Player->velocity.x += Player->Xacceleration * dt;
	}
}

void Player::State_Skidding::TestForExit(Player* Player)
{
	if (Player->moveUpKey.IsKeyDown())
	{
		Player->ChangeState(&Player->stateJumping);
	}
	else if (Player->moveLeftKey.IsKeyDown() && Player->velocity.x <= 0)
	{
		Player->ChangeState(&Player->stateRunning);
	}
	else if (Player->moveRightKey.IsKeyDown() && Player->velocity.x >= 0)
	{
		Player->ChangeState(&Player->stateRunning);
	}
	else if (!Player->moveRightKey.IsKeyDown() && !Player->moveLeftKey.IsKeyDown())
	{
		Player->ChangeState(&Player->stateRunning);
	}
	if (Player->GetPosition().y > Mode3::floor)
	{
		Player->ChangeState(&Player->stateFalling);
	}
}

//Falling
void Player::State_Falling::Enter(Player* Player)
{
	Player->sprite.PlayAnimation(static_cast<int>(Player_Anim::Player_Fall_Anim));
}

void Player::State_Falling::Update(Player* Player, double dt)
{
	Player->UpdateXVelocity(dt);
	Player->velocity.y -= Mode3::gravity * dt;
}

void Player::State_Falling::TestForExit(Player* Player)
{
	if (Player->position.y <= Mode3::floor)
	{
		Player->velocity.y = 0;
		Player->position.y = Mode3::floor;
		if (Player->velocity.x > 0)
		{
			if (Player->moveLeftKey.IsKeyDown())
			{
				Player->ChangeState(&Player->stateSkidding);
			}
			else
			{
				Player->ChangeState(&Player->stateRunning);
			}
		}
		else if (Player->velocity.x < 0)
		{
			if (Player->moveRightKey.IsKeyDown())
			{
				Player->ChangeState(&Player->stateSkidding);
			}
			else
			{
				Player->ChangeState(&Player->stateRunning);
			}
		}
		else
		{
			Player->ChangeState(&Player->stateIdle);
		}
	}
}

void Player::UpdateXVelocity(double dt)
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

void Player::SetPosition(math::vec2 targetPosition)
{
	position = targetPosition;
}

void Player::SetVelocity(math::vec2 targetVelocity)
{
	velocity = targetVelocity;
}

math::vec2 Player::GetVelocity()
{
	return velocity;
}
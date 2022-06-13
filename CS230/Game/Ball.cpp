/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Juseung Yang
Creation date: 3/29/2022
-----------------------------------------------------------------*/
#include "Ball.h"
#include "Mode1.h"
#include "..\Engine\Engine.h"

Ball::Ball(math::vec2 startPos)
	: initPosition(startPos),
	position(position),
	currState()
{
}

void Ball::Load()
{
	sprite.Load("assets/Ball.spt");
	position = initPosition;
	currState = &stateBounce;
	currState->Enter(this);
}

void Ball::Update(double dt)
{
	currState->Update(this, dt);
	position += velocity * dt;
	currState->TestForExit(this);

	if (position.y < Mode1::floor)
	{
		position.y = Mode1::floor;
		velocity.y = bounceVelocity;
	}

	objectMatrix = math::TranslateMatrix(position);
}

void Ball::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(objectMatrix * cameraMatrix);
}

//Bounce
void Ball::State_bounce::Enter(Ball* ball)
{
	ball->velocity = math::vec2(0, bounceVelocity);
}

void Ball::State_bounce::Update(Ball* ball, double dt)
{
	ball->velocity.y -= Mode1::gravity * dt;
}

void Ball::State_bounce::TestForExit(Ball* ball)
{
	if (ball->position.y <= Mode1::floor)
	{
		ball->ChangeState(&ball->stateLand);
	}
}

//Land
void Ball::State_land::Enter(Ball* ball)
{
	ball->velocity.y = 0;
	ball->position.y = Mode1::floor;
}

void Ball::State_land::Update(Ball* ball, double dt)
{
	ball->position.y += ball->velocity.y * dt;
}

void Ball::State_land::TestForExit(Ball* ball)
{
	ball->ChangeState(&ball->stateBounce);
}

void Ball::ChangeState(State* newState)
{
	//Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}
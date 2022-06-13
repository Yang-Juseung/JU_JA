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
#include "Ball_Anims.h"


Ball::Ball(math::vec2 startPos)
	: initPosition(startPos),
	position(position),
	currState(&stateLand)
{
}

void Ball::Load()
{
	sprite.Load("assets/Ball.spt");
	position = initPosition;
	velocity = { 0,0 };
	currState = &stateLand;
	currState->Enter(this);
}

void Ball::Update(double dt)
{
	currState->Update(this, dt);
	sprite.Update(dt);
	position += velocity * dt;
	currState->TestForExit(this);

	objectMatrix = math::TranslateMatrix(position);
}

void Ball::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(objectMatrix * cameraMatrix);
}

void Ball::ChangeState(State* newState)
{
	Engine::GetLogger().LogDebug("Ball Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}

//Bounce
void Ball::State_bounce::Enter(Ball* ball)
{
	ball->sprite.PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
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
		ball->position.y = Mode1::floor;
		ball->velocity.y = 0;
		ball->ChangeState(&ball->stateLand);
	}
}

//Land
void Ball::State_land::Enter(Ball* ball)
{
	ball->sprite.PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}

void Ball::State_land::Update([[maybe_unused]]Ball* ball, [[maybe_unused]] double dt)
{
}

void Ball::State_land::TestForExit(Ball* ball)
{
	if (ball->sprite.IsAnimationDone() == true)
	{
		ball->ChangeState(&ball->stateBounce);
	}
}
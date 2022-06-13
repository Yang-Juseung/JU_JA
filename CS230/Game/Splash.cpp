/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Juseung Yang
Creation date: 3/24/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Splash.h"

Splash::Splash() /*: modeNext(CS230::InputKey::Keyboard::Enter) */{}

void Splash::Load() 
{
	texture.Load("Assets/DigiPen_BLACK_1024px.png");
}

void Splash::Draw()
{
	Engine::GetWindow().Clear(0xFFFFFFFF);
	math::ivec2 SplashVec(Engine::GetWindow().GetSize() / 2 - texture.GetSize() / 2);
	texture.Draw(math::TranslateMatrix(SplashVec));
}

void Splash::Update(double dt) 
{

	NextTime += dt;
	if ( NextTime > 3.0 )
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode1));
	}
}
void Splash::Unload() 
{
}
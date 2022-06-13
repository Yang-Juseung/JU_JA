/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode1.h
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Juseung Yang
Creation date: 3/15/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Hero.h"
#include "Ball.h"
#include "..\Engine\Camera.h"
#include "Background.h"

namespace CS230
{
	class Camera;
}

class Mode1 : public CS230::GameState {
public:
	static constexpr double floor = 126.0f;

	Mode1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode 1"; }

	static constexpr double gravity = 2000;

private:
	CS230::InputKey modeNext;

	CS230::InputKey modeReload;

	Hero *hero;

	Ball* ball1;
	Ball* ball2;
	Ball* ball3;
	CS230::Camera camera;
	Background background;
};

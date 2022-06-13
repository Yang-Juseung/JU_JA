/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode3.h
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Juseung Yang, Jaeyeong An
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Player.h"
#include "..\Engine\Camera.h"
#include "Background.h"
#include "Foothold.h"

namespace CS230
{
	class Camera;
}

class Mode3 : public CS230::GameState {
public:
	static constexpr double floor = 126.0f;

	Mode3();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode 3"; }

	static constexpr double gravity = 2000;

private:
	CS230::InputKey modeNext;

	CS230::InputKey modeReload;

	Player* player;

	Foothold* foothold1;
	Foothold* foothold2;
	Foothold* foothold3;
	Foothold* foothold4;
	Foothold* foothold5;
	CS230::Camera camera;
	Background background;
};

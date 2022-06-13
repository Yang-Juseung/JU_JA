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
#include "Hero.h"
#include "Background.h"

class Game_end : public CS230::GameState {
public:
	Game_end();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Mode 3"; }
private:
	Background background;
	Hero* hero;
	CS230::InputKey modeNext;
	CS230::InputKey modeReload;
};

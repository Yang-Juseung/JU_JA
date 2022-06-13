/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode2.h
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Juseung Yang
Creation date: 3/15/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Ship.h"

class Mode2 : public CS230::GameState {
public:
	Mode2();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;


	std::string GetName() override { return "Mode 2"; }
private:
	CS230::InputKey modeNext;

	CS230::InputKey modeReload;

	Ship *ship;
};

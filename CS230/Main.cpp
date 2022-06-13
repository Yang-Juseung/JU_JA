	/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Project: CS230
Author: Juseung Yang
Creation date: 3/15/2022
-----------------------------------------------------------------*/
#include <stdexcept>	
#include <iostream>		

#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/Mode1.h"
#include "Game/Mode2.h"
#include "Game/Mode3.h"
#include "Game/Screens.h"
#include "Game/Gameover.h"


int main(void) 
{
	try 
	{
		Engine& engine = Engine::Instance();
		engine.Init("Week 6 - Juseung Yang");
		Splash splash;
		Mode1 mode1;
		Mode2 mode2;
		Mode3 mode3;
		Game_end over;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mode1);
		engine.GetGameStateManager().AddGameState(mode2);
		engine.GetGameStateManager().AddGameState(mode3);
		engine.GetGameStateManager().AddGameState(over);
		while (engine.HasGameEnded() == false) 
		{
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	}
	catch (std::exception& e) 
	{
		std::cerr << e.what() << "\n";
		return -1;
	}
}
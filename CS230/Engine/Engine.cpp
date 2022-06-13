/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.h
Purpose: This is the service provider for our games engine services
Project: CS230
Author: Juseung Yang
Creation date: 3/15/2022
-----------------------------------------------------------------*/

#include "Engine.h"

Engine::Engine() :
	frameCount(0), lastTick(std::chrono::system_clock::now()),averageFrameRate(0),
#ifdef _DEBUG				
	logger(CS230::Logger::Severity::Debug, true, lastTick)
#else 						
	logger(CS230::Logger::Severity::Event, false, lastTick)
#endif
{}

Engine::~Engine() {}


void Engine::Init(std::string windowName)
{
	window.Init(windowName);
	logger.LogEvent("Engine init");
	fpsCalcTime = lastTick;
};

void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
};

void Engine::Update()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();	

	if (dt > (1 / Engine::Target_FPS))
	{
		logger.LogVerbose("Engine Update");
		gameStateManager.Update(dt);
		input.Update();
		window.Update();
		frameCount++;
		
		if (frameCount > FPS_IntervalFrameCount)
		{
			//std::chrono::duration<double>(now - fpsCalcTime).count();
			averageFrameRate = frameCount/ std::chrono::duration<double>(now - fpsCalcTime).count();
			fpsCalcTime = now;
			frameCount = 0;
			logger.LogEvent("FPS:  " + std::to_string(averageFrameRate));
		}
		
		lastTick = now;
	}
	
};

bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();
};
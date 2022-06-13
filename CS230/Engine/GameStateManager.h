/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Project: CS230
Author: Juseung Yang
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include <vector>

namespace CS230 {
	class GameState;

	class GameStateManager {
	public:
		GameStateManager();
		void AddGameState(GameState& gameState);
		void Update(double dt);
		void SetNextState(int initState);
		void Shutdown();
		void ReloadState();
		bool HasGameEnded() { return state == State::EXIT; }

		
	private:
		enum class State {
			START,
			LOAD,
			UPDATE,
			UNLOAD,
			SHUTDOWN,
			EXIT,
			DEAD
		};

		std::vector<GameState*> gameStates;
		State state;
		GameState* currGameState;
		GameState* nextGameState;
	};
}

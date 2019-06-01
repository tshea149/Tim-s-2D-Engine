/* author: Tim */

#ifndef GAME_H
#define GAME_H

#include "WindowManager.h"
#include "RenderEngine.h"
#include "Controller.h"

enum GameState
{
	MAIN_MENU,
	PLAYING,
	GAME_EXIT
};

class Game
{
private:
	std::shared_ptr<WindowManager> const window_manager;
	//Controller* controller;					// not const, current controller can be changed

	GameState game_state;

	void runGameLoop();
	void handleInput();

public:
	Game(std::shared_ptr<WindowManager> const _window_manager) : window_manager(_window_manager) {};

	void start();
};


#endif // !GAME_H

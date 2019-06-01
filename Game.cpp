#include "Game.h"
#include "RenderEngine.h"

void Game::runGameLoop()
{
	while (GAME_EXIT != game_state)
	{
		
		// take user input
		handleInput();

		// update game logic
		// run entity manager?

		// update graphics
		// run render engine
		RenderEngine::getInstance()->update();
		window_manager->displayWindow();
	}
}

void Game::handleInput()
{
	// call function to get window event
	sf::Event e;
	if (false == window_manager->checkEvent(e))
		return;

	switch (e.type)
	{
	/* ----- KEYBOARD/MOUSE EVENTS ----- */
	case sf::Event::KeyPressed:				// fallthrough
	case sf::Event::KeyReleased:			// fallthrough
	case sf::Event::MouseButtonPressed:		// fallthrough
	case sf::Event::MouseButtonReleased:	// fallthrough
	case sf::Event::MouseWheelScrolled:
//		controller->handleInput();
		break;
	/* ----- END KEYBOARD/MOUSE EVENTS ----- */

	/* ----- JOYSTICK EVENTS ----- */
	//case sf::Event::JoystickConnected:
	//case sf::Event::JoystickDisconnected:
	/* ----- END JOYSTICK EVENTS ----- */

	/* ----- WINDOW EVENTS ----- */
	case sf::Event::Closed:

		// save the game? signal that the game is exiting?
		game_state = GameState::GAME_EXIT;
		break;
	//case sf::Event::Resized:
	//case sf::Event::GainedFocus:
	//case sf::Event::LostFocus:
	/* ----- END WINDOW EVENTS ----- */
	}
}

void Game::start()
{
	runGameLoop();
}

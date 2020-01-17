/* author: Tim */
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include <memory>

#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 768

class WindowManager
{
private:
	// declared singleton instance
	static std::weak_ptr<WindowManager> instance;

	sf::RenderWindow window;
	std::string window_title = "Duct Tape and Diesel";	
	
	WindowManager();

public:
	static std::shared_ptr<WindowManager> getInstance();

	sf::RenderWindow* getWindow();

	sf::Vector2u getWindowSize();
	
	// \ Checks pending window events and returns true if there is an event to handle. False if none.
	// \ Parameter e: reference of sf::Event object where the polled event is to be stored.
	bool checkEvent(sf::Event& e);

	void resizeWindow(sf::Vector2u size);
	void displayWindow();
	void clearWindow();
	void closeWindow();
};

#endif
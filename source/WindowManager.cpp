#include "WindowManager.h"

// defined singleton instance
std::weak_ptr<WindowManager> WindowManager::instance;

WindowManager::WindowManager()
{
	window.create(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 32), window_title, sf::Style::Default);
}

std::shared_ptr<WindowManager> WindowManager::getInstance()
{
	std::shared_ptr<WindowManager> p = instance.lock();
	if (p == nullptr)
	{
		p = std::shared_ptr<WindowManager>(new WindowManager());	// std::make_shared will not work here because constructor is private
		instance = p;
		return p;
	}

	else
		return p;
}

sf::RenderWindow* WindowManager::getWindow()
{
	return &window;
}

sf::Vector2u WindowManager::getWindowSize()
{
	return window.getSize();
}

bool WindowManager::checkEvent(sf::Event &e)
{
	return window.pollEvent(e);
}

void WindowManager::resizeWindow(sf::Vector2u size)
{
	window.setSize(size);
	// \ Updating the view will prevent stretching of the contents.
	window.setView(sf::View(sf::FloatRect(0, 0, size.x, size.y)));
}

void WindowManager::displayWindow()
{
	window.display();
}

void WindowManager::clearWindow()
{
	window.clear();
}

void WindowManager::closeWindow()
{
	window.close();
}

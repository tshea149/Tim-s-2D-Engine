/* Author: Tim */
#ifndef TESTRENDERENGINE_CPP
#define TESTRENDERENGINE_CPP

#include "TestRenderEngine.h"

#include "RenderEngine.h"
#include "WindowManager.h"
#include "RandomNumberGenerator.h"

#include <vector>

RenderComponentHandle TestRenderEngine::drawYellowSquare(sf::Vector2f location)
{
	RenderComponentHandle p = RenderEngine::getInstance()->createRenderComponent("textures/yellow_square.png", RenderLayer::C1, LayerPriority::LOW, true);
	p.access()->setLocation(location);
	return p;
}

RenderComponentHandle TestRenderEngine::drawRedSquare(sf::Vector2f location)
{
	RenderComponentHandle p = RenderEngine::getInstance()->createRenderComponent("textures/red_square.png", RenderLayer::BG1, LayerPriority::MED, true);
	p.access()->setLocation(location);
	return p;
}

RenderComponentHandle TestRenderEngine::drawBlueSquare(sf::Vector2f location)
{
	RenderComponentHandle p = RenderEngine::getInstance()->createRenderComponent("textures/blue_square.png", RenderLayer::BG1, LayerPriority::LOW, true);
	p.access()->setLocation(location);
	return p;
}

// creates num_squares or RENDER_COMPONEN_MAX (whichever is smaller) number of RenderComponents and draws them to the screen at random positions.
// returns a vector containing pointers to all created RenderComponenets
std::vector<RenderComponentHandle>  TestRenderEngine::randomSquaresTest(uint64_t seed, uint32_t num_squares)
{
	RandomNumberGenerator rng(seed);
	RenderComponentHandle p;
	std::vector<RenderComponentHandle> p_vec;

	for (size_t i = 0; i < num_squares; i++)
	{
		sf::Vector2f location(rng.getNumBetween(0, WindowManager::getInstance()->getWindowSize().x - 48), rng.getNumBetween(0, WindowManager::getInstance()->getWindowSize().y - 48));
		switch (rng.getNumBetween(0, 2))
		{
		case 0:
			p = TestRenderEngine::drawRedSquare(location);
			break;

		case 1:
			p = TestRenderEngine::drawBlueSquare(location);
			break;

		case 2:
			p =  TestRenderEngine::drawYellowSquare(location);
			break;
		}

		if (true == p.isValid())
			p_vec.push_back(p);
	}
	return p_vec;
}

void  TestRenderEngine::deallocateRenderComponents(std::vector<RenderComponentHandle> vec)
{
	for (std::vector<RenderComponentHandle>::iterator it = vec.begin(); it != vec.end(); ++it)
		it->destroy();
}

#endif


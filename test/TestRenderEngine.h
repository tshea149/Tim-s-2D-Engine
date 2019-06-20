/* Author: Tim */
#ifndef TESTRENDERENGINE_H
#define TESTRENDERENGINE_H

#include "RenderComponent.h"

namespace TestRenderEngine
{
	std::shared_ptr<RenderComponent> drawYellowSquare(sf::Vector2f location);
	std::shared_ptr<RenderComponent> drawRedSquare(sf::Vector2f location);
	std::shared_ptr<RenderComponent> drawBlueSquare(sf::Vector2f location);

	std::vector<std::shared_ptr<RenderComponent>> randomSquaresTest(uint64_t seed, uint32_t num_squares);
}

#endif
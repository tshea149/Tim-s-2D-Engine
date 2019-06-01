/* Author: Tim */
#ifndef TESTRENDERENGINE_H
#define TESTRENDERENGINE_H

#include "RenderComponent.h"

namespace TestRenderEngine
{
	RenderComponentHandle drawYellowSquare(sf::Vector2f location);
	RenderComponentHandle drawRedSquare(sf::Vector2f location);
	RenderComponentHandle drawBlueSquare(sf::Vector2f location);

	std::vector<RenderComponentHandle> randomSquaresTest(uint64_t seed, uint32_t num_squares);
	void deallocateRenderComponents(std::vector<RenderComponentHandle> vec);
}

#endif
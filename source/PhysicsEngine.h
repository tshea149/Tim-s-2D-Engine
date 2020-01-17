/* author: Tim */

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <memory>

class PhysicsEngine
{
private:

	static std::weak_ptr<PhysicsEngine> instance;
	static std::shared_ptr<PhysicsEngine> getInstance();

	// map of grid spaces and what entities exist in them
	// all physics components will have to check for collisions with nearby components
	//	\	start by checking which space(s) the component occupies
	//	\	a component would then need to know what spaces it occupies
	//	\		compute by checking where the corners of the bounding box lie?
	//	if cheking goes through all grid spaces and checks each physics component inside, how to prevent components that occupy more than one space together from double-colliding?
	//	//	because of this case it seems to make sense to go component by component rather than by grid spaces

	// best play is to use a map of grid spaces containing a list of their elements
	//	\	need to know the world size
	//	\ removing component requires removit it from the grid space map as well?
	//		\ is it worth keeping the buckets ordered for this purpose?

public:
};

#endif // !PHYSICSENGINE_H



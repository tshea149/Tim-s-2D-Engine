#include "PhysicsEngine.h"

std::weak_ptr<PhysicsEngine> PhysicsEngine::instance;

std::shared_ptr<PhysicsEngine> PhysicsEngine::getInstance()
{
	std::shared_ptr<PhysicsEngine> p = instance.lock();
	if (p == nullptr)
	{
		p = std::shared_ptr<PhysicsEngine>(new PhysicsEngine());	// std::make_shared will not work here because constructor is private
		instance = p;
		return p;
	}

	else
		return p;
}

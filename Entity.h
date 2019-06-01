/* author: Tim */

#ifndef ENTITY_H
#define ENTITY_H

// an Entity is any object that can exist within the game scene
//	\ an Entity can have various components, giving it properties
//  \ the properties are referred to, and accessed by handles
//	\ if an Entity does not have a handle, it will be assigned an invalid one.
class Entity
{
private:

public:
	Entity();


	//sf::Vector2f position;
	virtual void update() = 0;
};

#endif


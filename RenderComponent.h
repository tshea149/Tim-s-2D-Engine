/* author: Tim */
#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "Handle.h"

#include <memory>

// which layer the sprite is to be drawn to
enum RenderLayer
{
	BG1,
	BG2,
	BG3,
	C1,
	C2,
	C3,
	FG1,
	FG2,
	FG3,
	NUM_RENDER_LAYERS
};

// higher priority makes it less likely that another sprite on the same layer will be drawn over it
enum LayerPriority
{
	LOW,
	MED,
	HIGH,
	EXTREME,
	NUM_LAYER_PRIORITIES
};

// RenderComponents are stored sequentially in an array inside of the RenderEngine
// \	The RenderEngine handles logic for where in memory newly created RenderComponents should be placed.
// an entity with a RenderComponent will be able to be drawn to the screen
struct RenderComponent
{
private:
	friend class RenderEngine;			// allow RenderEngine access to private members

	RenderLayer layer;					// the layer the sprite will be drawn on
	LayerPriority layer_priority;		// higher priority = less chance the sprite will be drawn over by other sprites sharing the same layer
	
	//Handle entity_handle;
	std::shared_ptr<sf::Texture> p_texture;
	sf::Sprite sprite;
	bool visible;

	// private constructors so that only the RenderEngine can create RenderComponents
	RenderComponent() {};																															// default constructor used when RenderEngine creates the RenderComponent pool. isActive init to false so nonexistent render components are not considered in the sorting or drawing.
	RenderComponent(RenderLayer _layer, LayerPriority _layer_priority, bool _visible) : layer(_layer), layer_priority(_layer_priority), visible(_visible) {};

	// creation and deletion done only through RenderEngine using a RenderComponent pool
	void* operator new[](size_t) = delete;								// disable heap allocation
	void operator delete[](void*) = delete;

public:

	bool setTexture(std::string texture_filepath);
	void setLayer(RenderLayer layer);
	void setLayerPriority(LayerPriority layer_priority);
	void setVisibility(bool v);
	bool isVisible();

	// sets the sprite world position
	void setLocation(sf::Vector2f new_location);
};

struct RenderComponentHandle
{
private:
	// only RenderEngine can create RenderComponenHandles
	friend class RenderEngine;
	RenderComponentHandle(int _index) : index(_index) {};

	// index of the RenderComponent in the component_pool in the RenderEngine.
	// used to find the RenderComponent when the component_pool is resized.
	// signed so that negative value can be used to represent an invalid handle
	int index;

public:
	// default constructor creates invalid RenderComponentHandle
	RenderComponentHandle() : index(-1) {};

	RenderComponent* const access();
	bool isValid();
	void destroy();
};

#endif

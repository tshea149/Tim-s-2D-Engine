/* author: Tim */

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "RenderComponent.h"
#include "EngineSettings.h"

#include <array>
#include <vector>
#include <stack>
#include <string>
#include <memory>

// Responsible for creating, storing, and updating all RenderComponents.
// \ Responsible for the creation of RenderComponents because it stores them sequentially in memory.
// The RenderEngine renders to a window, it does not manage a window.
class RenderEngine
{
private:

	// declared singleton instance
	static std::weak_ptr<RenderEngine> instance;

	sf::RenderTarget* render_target;

	std::stack<uint32_t> available_component_indexes;
	// stores all render_components. Sort by component's layer then layer_priority to determine draw order.
	std::array<RenderComponent, RENDER_COMPONENT_POOL_SIZE> component_pool {} ;	// use of initializer to create array of RenderComponents because RenderComponent's constructor is private.
	std::vector<RenderComponent*> component_draw_order;

	// function object to use as custom deletor for weak_ptr<sf::Texture> in TextureCacheEntry
	// deletes the pointer to texture data and removes the corresponding TextureCacheEntry from the texture_cache
	struct RenderComponentDeleter
	{
		RenderComponentDeleter(RenderEngine* const _p_render_engine) : p_render_engine(_p_render_engine) {};
		void operator()(RenderComponent*);
		RenderEngine* const p_render_engine;
	};

	// constructor initializes available component index stack
	RenderEngine();

	void removeRenderComponent(RenderComponent* const p_rc);
	size_t computeComponentIndex(const RenderComponent* const p_rc);

	int RenderEngine::computeComponentValue(RenderComponent* render_component);
	void addComponentToDrawOrder(RenderComponent* p_rc);
	void insertComponentInDrawOrder(std::vector<RenderComponent*>::iterator it, RenderComponent* const p_rc, int comp_val);

	bool RenderEngine::forwardLinearComponentDrawRemoval(std::vector<RenderComponent*>::iterator const it, RenderComponent* const p_rc, int comp_val);
	bool RenderEngine::backwardsLinearComponentDrawRemoval(std::vector<RenderComponent*>::iterator const it, RenderComponent* const p_rc, int comp_val);
	bool RenderEngine::removeComponentFromDrawOrder(RenderComponent* const p_rc);

	void drawComponents();

public:
	RenderEngine(RenderEngine &) = delete;

	static std::shared_ptr<RenderEngine> getInstance();

	void setRenderTarget(sf::RenderTarget* target);
	
	// returns pointer to created component or nullptr if creation failed
	std::shared_ptr<RenderComponent> createRenderComponent(std::string texture_filepath, RenderLayer render_layer, LayerPriority layer_priority, bool isActive);

	// draws all active RenderComponents to the screen
	void update();
};

#endif // !RENDERENGINE_H
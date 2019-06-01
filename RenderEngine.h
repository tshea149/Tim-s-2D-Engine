/* author: Tim */

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "RenderComponent.h"

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
	sf::RenderTarget* render_target;

	std::stack<size_t> available_component_indexes;
	// stores all render_components. Sort by component's layer then layer_priority to determine draw order.
	std::vector<RenderComponent> component_pool;
	std::vector<RenderComponent*> component_draw_order;

	// constructor initializes available component index stack
	RenderEngine();

	int RenderEngine::computeComponentValue(RenderComponent* render_component);
	void addComponentToDrawOrder(RenderComponent* p_rc);
	void insertComponentInDrawOrder(std::vector<RenderComponent*>::iterator it, RenderComponent* p_rc, int comp_val);

	bool RenderEngine::forwardLinearComponentDrawRemoval(std::vector<RenderComponent*>::iterator const it, RenderComponent* p_rc, int comp_val);
	bool RenderEngine::backwardsLinearComponentDrawRemoval(std::vector<RenderComponent*>::iterator const it, RenderComponent* p_rc, int comp_val);
	bool RenderEngine::removeComponentFromDrawOrder(RenderComponent* p_rc);

	void RenderEngine::resizeComponentPool(size_t new_size);

	void drawComponents();

public:
	RenderEngine(RenderEngine &) = delete;

	static std::shared_ptr<RenderEngine> getInstance();

	void setRenderTarget(sf::RenderTarget* target);
	
	// returns pointer to created component or nullptr if creation failed
	RenderComponentHandle createRenderComponent(std::string texture_filepath, RenderLayer render_layer, LayerPriority layer_priority, bool isActive);

	bool removeRenderComponent(RenderComponentHandle& h_component);
	RenderComponent* const accessRenderComponent(RenderComponentHandle& h_component);

	// draws all active RenderComponents to the screen
	void update();
};

#endif // !RENDERENGINE_H
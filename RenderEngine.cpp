/* author: Tim */
#include "RenderEngine.h"
#include "AssetManager.h"
#include "EngineSettings.h"	// for RENDER_COMPONENT_MAX

#include <array>
#include <memory>

#include <SFML/Graphics/Texture.hpp>

#if _DEBUG
#include "Debug.h"
#endif

static std::weak_ptr<RenderEngine> instance;

RenderEngine::RenderEngine()
{
	// top of the stack should begin with 0 and go to RENDER_COMPONENT_MAX
	for (size_t i = RENDER_COMPONENT_MAX - 1; i != size_t(-1) ; --i)
		this->available_component_indexes.push(i);

	// important use of resize vs reserve here
	//	\ resize allocates space and populates the vector, important for the component_pool as we are indexing into it
	//	\ reserve allocates space but does not add values to the vector, important so that we do not draw indexes that we do not want
	component_pool.resize(RENDER_COMPONENT_RESERVE, RenderComponent());
	component_draw_order.reserve(RENDER_COMPONENT_RESERVE);
}

std::shared_ptr<RenderEngine> RenderEngine::getInstance()
{
	std::shared_ptr<RenderEngine> p = instance.lock();
	if (p == nullptr)
	{
		p = std::shared_ptr<RenderEngine>(new RenderEngine());	// std::make_shared will not work here because constructor is private
		instance = p;
		return p;
	}

	else
		return p;
}

void RenderEngine::update()
{
	drawComponents();
}

int RenderEngine::computeComponentValue(RenderComponent* render_component)
{
	return (100 * render_component->layer) + (render_component->layer_priority);
}

void RenderEngine::insertComponentInDrawOrder(std::vector<RenderComponent*>::iterator const it, RenderComponent* p_rc, int comp_val)
{
	// determine if inserted new_component_index goes before or after given iterator
	// if equal to given iterator, it should go after the last component_index that is not equal to it

	if (it == component_draw_order.end())
		component_draw_order.push_back(p_rc);

	else if (comp_val < computeComponentValue(*it))
		component_draw_order.insert(it, p_rc);

	else if (comp_val > computeComponentValue(*it))
		component_draw_order.insert(it + 1, p_rc);

	else // equal. Insert new_component_index after the last equal component_index
		insertComponentInDrawOrder(it + 1, p_rc, comp_val);
}

// inserts the given index (representing a RenderComponent in the pool) into the draw order
// draw order is sorted by RenderLayer ascending, and by LayerPriority ascending in the event of a RenderLayer tie
void RenderEngine::addComponentToDrawOrder(RenderComponent* p_rc)
{
	// using integer indexes instead of iterators because of out of bounds errors with iterators, when the operation should be performed anyways. Staying in bounds of the array is assured by the while loop condition

	// using a computed property to compare to other components in the pool, as the order is determined by two different values (layer and layer_priority, where layer takes priority)
	int comp_val = computeComponentValue(p_rc);

	// use signed int to index to allow for negatives (for case such as end index in empty vector or vector of 1 element)
	int begin = 0;
	int end = component_draw_order.size() - 1;
	while (end >= begin)
	{
		size_t middle = (begin + end) / 2;
		int m_comp_val = computeComponentValue(component_draw_order[middle]);
		//int m_comp_val = computeComponentValue(*(it_middle));
		// compare value of middle component_index to new component_index
		// \ if new_component_index is greater, it belongs somewhere between the middle and end
		// \ the reverse is true if new_component_index is less
		// \ if equal, insert in-place
		
		if (comp_val > m_comp_val)
			begin = middle + 1;

		else if (comp_val < m_comp_val)
			end = middle - 1;

		else // comp_val == m_comp_val
		{
			insertComponentInDrawOrder(component_draw_order.begin() + middle, p_rc, comp_val);
			return;
		}
	}

	insertComponentInDrawOrder(component_draw_order.begin() + begin, p_rc, comp_val);
	return;
}

void RenderEngine::drawComponents()
{
	//// component_draw_order should always be less than or equal to the size of the component_pool
	for (std::vector<RenderComponent*>::iterator iter = component_draw_order.begin(); iter != component_draw_order.end(); ++iter)
		if ((*iter)->isVisible())
			render_target->draw((*iter)->sprite);
}

void RenderEngine::setRenderTarget(sf::RenderTarget* render_target)
{
	this->render_target = render_target;
}

// when component_pool is resized, the component_draw_order vector needs to have all pointers updated to point to the new RenderComponent memory locations
// if the component_draw_order held indexes instead of pointers, this would be unnecessary.
// \ however, resizing the component pool should be a rare occurance
void RenderEngine::resizeComponentPool(size_t new_size)
{
	// store the beginning address of the component_pool before it gets moved. Will be used in computing new pointers.
	RenderComponent* old_cp_begin = &component_pool[0];

	// perform component_pool resize operation. This will move the vector in memory, making all RenderComponent* in component_draw_order invalid
	component_pool.resize(new_size, RenderComponent());

	// iterate over draw order, convert existing invalid address into new valid address
	// \ compute index using pointer - pointer of element 0
	//  \ use index to get new pointer from component_pool
	for (std::vector<RenderComponent*>::iterator iter = component_draw_order.begin(); iter != component_draw_order.end(); ++iter)
	{
		// index = (pointer to RenderComponent (stored in component_draw_order)) - (pointer to first RenderComponent in component_pool)
		size_t index = *iter - old_cp_begin;

		// replace invalid pointer with new valid pointer
		*iter = &component_pool[index];
	}
}

RenderComponentHandle RenderEngine::createRenderComponent(std::string texture_filepath, RenderLayer render_layer, LayerPriority layer_priority, bool isVisible)
{
	// check if there is space for a RenderComponent
	if (available_component_indexes.empty())
	{
		#if _DEBUG
			Debug::log("Ran out of space for a new RenderComponent");
		#endif
			return RenderComponentHandle();	// default constructor for RenderComponentHandle is invalid
	}	

	// get first available component index and remove from stack
	size_t index = available_component_indexes.top();

	if (index + 1 > component_pool.size())	// max index is size - 1, have to add 1 to account for that in this comparison
		resizeComponentPool(component_pool.size() * 2);

	// RenderComponent ready to be created
	component_pool[index] = RenderComponent(render_layer, layer_priority, isVisible);

	// load and set texture, handle load failure
	if (false == component_pool[index].setTexture(texture_filepath))
	{
		#if _DEBUG
			Debug::log("Loading texture failed when creating RenderComponent");
		#endif
		return RenderComponentHandle();	// texture load failed
	}

	available_component_indexes.pop();	

	// new component added, insert into draw order
	addComponentToDrawOrder(&component_pool[index]);

	return RenderComponentHandle(index);
}

// \ param it : search starting location (vector iterator)
// \ param index : index of RenderComponent to remove in component_pool
// \ param comp_cal : computed value from computeComponentValue() for comparing to other RenderComponents to search for index. component_draw_order is sorted according to this value
bool RenderEngine::forwardLinearComponentDrawRemoval(std::vector<RenderComponent*>::iterator const it, RenderComponent* p_rc, int comp_val)
{
	if (it == component_draw_order.end())
		return false;

	// check if pointer stored in component_draw_order matches the pointer of the RenderComponent given by the requested index
	else if (p_rc == (*it))
	{
		// found matching index of RenderComponent to remove
		component_draw_order.erase(it);
		return true;
	}

	// verify that the search does not move to a part of the array where the target RenderComponent* will never be
	else if (comp_val != computeComponentValue(*it))
		return false;

	// advance forward
	else
		return forwardLinearComponentDrawRemoval(it + 1, p_rc, comp_val);
}

bool RenderEngine::backwardsLinearComponentDrawRemoval(std::vector<RenderComponent*>::iterator const it, RenderComponent* p_rc, int comp_val)
{
	// check if pointer stored in component_draw_order matches the pointer of the RenderComponent given by the requested index
	if (p_rc == (*it))
	{
		// found matching index of RenderComponent to remove
		component_draw_order.erase(it);
		return true;
	}

	else if (it == component_draw_order.begin())
		return false;

	// verify that the search does not move to a part of the array where the target RenderComponent* will never be
	else if (comp_val != computeComponentValue(*it))
		return false;

	// advance backwards
	else
		return backwardsLinearComponentDrawRemoval(it - 1, p_rc, comp_val);
}

// rc_index is the index of the RenderComponent in component_pool
bool RenderEngine::removeComponentFromDrawOrder(RenderComponent* p_rc)
{
	// binary search for component based on computeComponentValue()
	// if found componentValue, must search for matching index, as multiple unique indexes can have the same component value
	// \ first attempt linear search on forward partition. if not found, attempt linear search on backwards partition

	// using a computed property to compare to other components in the pool, as the order is determined by two different values (layer and layer_priority, where layer takes priority)
	int comp_val = computeComponentValue(p_rc);

	// use signed int to index to allow for negatives (for case such as end index in empty vector or vector of 1 element)
	int begin = 0;
	int end = component_draw_order.size() - 1;
	while (end >= begin)
	{
		size_t middle = (begin + end) / 2;
		int m_comp_val = computeComponentValue(component_draw_order[middle]);
		//int m_comp_val = computeComponentValue(*(it_middle));
		// compare value of middle component_index to new component_index
		// \ if new_component_index is greater, it belongs somewhere between the middle and end
		// \ the reverse is true if new_component_index is less
		// \ if equal, insert in-place
		
		if (comp_val > m_comp_val)
			begin = middle + 1;

		else if (comp_val < m_comp_val)
			end = middle - 1;

		else // comp_val == m_comp_val
		{
			// component pointer to remove is either before or after this index
			if (false == forwardLinearComponentDrawRemoval(component_draw_order.begin() + middle, p_rc, comp_val))
				return backwardsLinearComponentDrawRemoval(component_draw_order.begin() + middle, p_rc, comp_val);
			else
				return true;
		}
	}

	return false;
}

bool RenderEngine::removeRenderComponent(RenderComponentHandle& h_component)
{
	// check validity of handle
	if (h_component.index < 0)
		return false;

	// remove from component_draw_order and invalidate handle
	if (true == removeComponentFromDrawOrder(&component_pool[h_component.index]))
	{
		// delete the texture managed by p_texture. The texture will only be removed from the texture cache if the reference count reaches 0
		component_pool[h_component.index].p_texture.reset();

		// mark index as available again
		available_component_indexes.push(h_component.index);

		// invalidate the given handle
		h_component.index = -1;
		return true;
	}
	else
		return false;	
}

RenderComponent* const RenderEngine::accessRenderComponent(RenderComponentHandle& h_component)
{
	if (h_component.index < 0)
		return nullptr;

	else
		return &component_pool[h_component.index];
}

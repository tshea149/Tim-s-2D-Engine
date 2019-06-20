/* author: Tim */

#include "HandleManager.h"
#include <stack>

HandleManager::HandleManager()
{
	for (uint16_t i = MAX_HANDLES - 1; i != UINT16_MAX; i--)
		index_stack.push(i);
}

// creates an entry in the h_table if there is space
// returns an invalid handle if there is no available space in the table
Handle HandleManager::makeHandle(uint16_t object_index, HandleType _type, uint16_t* h_e_index)
{
	if (index_stack.empty())
	{
		#if _DEBUG
			Debug::log("Could not create handle, handle pool full");
		#endif // DEBUG

		return Handle(); // default Handle constructor is invalid Handle
	}

	uint16_t h_table_index = index_stack.top();
	index_stack.pop();
		
	h_table[h_table_index].object_index = object_index;
	// no need to increment counter, it should be incremented when a pointer is invalidated instead
	h_table[h_table_index].type = _type;

	// inform the object of its HandleEntry location so that the HandleEntry can be accessed when the object is moved
	*h_e_index = h_table_index;

	return Handle(h_table_index, h_table[h_table_index].counter, _type);
}

const void* const HandleManager::access(Handle handle)
{
	// this will also check for invalid handle, as an invalid handle will never be present in the HandleManager
	if (handle.type != h_table[handle.index].type)
		return nullptr;

	if (handle.counter != h_table[handle.index].counter)
		return nullptr;
		
	return h_table[handle.index].data;
}

void HandleManager::objectMoved(uint16_t h_index, uint16_t object_index)
{
	h_table[h_index].object_index = object_index;
}

void HandleManager::objectRemoved(uint16_t h_index)
{
	index_stack.push(h_index);	// get newly available space for a handle
	h_table[h_index].counter++;	// incrementing will invalidate the handle
}
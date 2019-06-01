///* author: Tim */
//#ifndef HANDLEMANAGER_H
//#define HANDLEMANAGER_H
//
//#include "Handle.h"
//#include <stack>
//
//// index 65535 (16 bit int max) is reserved for INVALID_HANDLE value
//#define MAX_HANDLES 65534 // 
//
//#if _DEBUG
//#include "Debug.h"
//static_assert (MAX_HANDLES < INVALID_HANDLE_INDEX, "Error: more handles than 16 bit handles can index");
//#endif
//
//// the HandleManager serves as a table to verify handles and translate them to their associated pointer
//class HandleManager
//{
//private:
//	struct HandleEntry
//	{
//	private:
//		// Disabled creation on heap
//		void* operator new(size_t) = delete;
//		void* operator new[](size_t) = delete;
//		void operator delete(void*) = delete;
//		void operator delete[](void*) = delete;
//
//		//friend class HandleManager;		// only the HandleManager can create HandleEntries
//	public:
//		uint16_t object_index;	// 16 bit index of the object relative to whichever data structure it is stored in
//		uint8_t counter;		// checks validity of handle
//		HandleType type;		// data type the handle is associated with
//		void* data;				// raw pointer to the data associated with the handle
//	};
//
//	HandleEntry h_table[MAX_HANDLES];		// table for validating Handles and translating to object indexes of their respective containers
//	std::stack<uint16_t> index_stack;		// holds available free spaces in the table
//	
//	// anything that manages an objects location need to be a friend of the HandleManager, so that they can create Handles to objects
//	friend class RenderEngine;
//
//	// creates and returns a handle to an object
//	//	\ creates a HandleEntry in the h_table
//	//	\ Parameter object_index is the index of the created object relative to its container. It is not the index of the handle into the handle manager.
//	//	\ Parameter h_e_container is an entry in the table holding the objects HandleEntry index.
//	//		\ This index is managed by whatever class manages the object that is having a handle to it created.
//	//		\ This is needed so that when an object is moved or removed, the HandleEntry can be modified in O(1) time.
//	// returns InvalidHandle if there is no space left in the h_table
//	Handle makeHandle(uint16_t object_index, HandleType _type, uint16_t* const h_e_index);
//
//	void objectMoved(uint16_t h_index, uint16_t object_index);
//	void objectRemoved(uint16_t h_index);
//
//public:
//	HandleManager();
//
//	// given a handle, returns constant pointer to the data associated with the handle. 
//	//	\ If handle is invalid, returns nullptr.
//	const void* const access(Handle handle);
//};
//
//#endif // !HANDLEMANAGER_H
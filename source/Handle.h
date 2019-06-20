///* author: Tim */
//
//#ifndef HANDLE_H
//#define HANDLE_H
//
//#include <stdint.h>
//
//// A Handle is essentially a wrapper around an array index.
////	\ It is used as an index into the HandleManager to look up the object it references.
//
////	\ Two powerful properties of the handle:
////		\ 1: The object that a handle references can be moved in memory, but the handle to it will still be valid.
////		\ 2: It is possilble to check if a handle is invalid (points to data that has been deleted). This solves the dangling pointer problem.
//
//// An invalid handle could still be accessed in the event where an expired handle is used to access the table, and the entry has the same counter and type.
//// \ The counter is used instead of a boolean to help mitigate the chance of this happening.
//// \ For this to happen, the counter would have to overflow. If this problem ever occurs, it may be worth increasing the size of the counter field.
//
//// A Handle is created only when an object referenced by a handle is created. They can be copied, making it possible to have multiple handles to the same object.
//
//enum HandleType : uint8_t
//{
//	InvalidHandle,
//	EntityHandle,
//	PhysicsComponentHandle,
//	RenderComponentHandle,
//	AIComponentHandle
//};
//
//#define INVALID_HANDLE_INDEX 65535 // invalid handle value is max value a 16 bit int can hold
//
//struct Handle
//{
//private:
//	// new/delete operators are deleted so that handles cannot be created via new
//	//	\ handles are 32 bits and should be passed via copy. Copying a 32 bit int on 32 bit architecture is a fast operation.
//	void* operator new(size_t) = delete;
//	void* operator new[](size_t) = delete;
//	void operator delete(void*) = delete;
//	void operator delete[](void*) = delete;
//
//	friend class HandleManager;		// HandleManager needs access to private members. Only it can create valid handles.
//	explicit Handle(uint16_t _index, uint8_t _counter, HandleType _type) : index(_index), counter(_counter), type(_type) {};
//
//	// All data is const because a Handle is a key into the HandleManager, and should never be changed.
//	uint16_t index;			// 16 bits index into handle manager
//	uint8_t counter;		// used to check validity of handle
//	HandleType type;		// data type the handle is associated with
//
//public:
//	// Default Handle constructor creates an invalid Handle.
//	Handle() : index(INVALID_HANDLE_INDEX), counter(0), type(HandleType::InvalidHandle) {};
//
//	HandleType getType() const;
//
//	bool operator ==(const Handle h);
//};
//
//#endif // !HANDLE_H
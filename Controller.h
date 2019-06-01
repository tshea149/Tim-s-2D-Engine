/* author: Tim */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Entity.h"
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Event.hpp"
#include <vector>

// an entity with a ControllerComponent will have its behavior controlled by the player via keyboard/mouse/joypad inputs
//	\ only one ControllerComponent is ever active at a time.
//	\ It is not the controller's job to map keys, but they job of whatever created it.

//typedef void (Entity::*entity_func_ptr)();
//
//// Abstract base class for all controllers.
//class Controller
//{
//public:
//	virtual void handleInput() = 0;
//};
//
//class EntityKeyboardMouseController : Controller
//{
//private:
//	//Handle entity_handle;
//
//	// Keys/mouse_btns are placed into a vector when pressed and removed when released. Every tick the keys/btns in this set will call their respective functions in their respective lookup tables.
//	//	\ The order of the vectors will be in order of least recently pressed.
//	//		\ Keys/btns that have been pressed more recently will have their associated functions called first. The vector will be iterated in reverse order.
//	std::vector<sf::Keyboard::Key> held_keys;
//	std::vector<sf::Mouse::Button> held_mouse_buttons;
//
//	entity_func_ptr key_press_table[sf::Keyboard::KeyCount]			{ nullptr };		// functions to call on the entity when specified key is pressed
//	entity_func_ptr key_release_table[sf::Keyboard::KeyCount]		{ nullptr };		// functions to call on the entity when specified key is released
//	entity_func_ptr key_held_table[sf::Keyboard::KeyCount]			{ nullptr };		// functions to call on the entity while specified key is held
//
//	entity_func_ptr mouse_press_table[sf::Mouse::ButtonCount]		{ nullptr };		// functions to call on the entity when specified mouse button is pressed
//	entity_func_ptr mouse_release_table[sf::Mouse::ButtonCount]		{ nullptr };		// functions to call on the entity when specified mouse button is released
//	entity_func_ptr mouse_held_table[sf::Mouse::ButtonCount]		{ nullptr };		// functions to call on the entity when specified mouse button is held
//
//	void addHeldKey(sf::Keyboard::Key key);		// Adds a key to the vector of keys currently held down. If the key's function pointer is nullptr, the key will not be added.
//	void removeHeldKey(sf::Keyboard::Key key);	
//
//	void addHeldButton(sf::Mouse::Button btn);		// Adds a key to the vector of keys currently held down. If the key's function pointer is nullptr, the key will not be added.
//	void removeHeldButton(sf::Mouse::Button btn);
//
//public:
//	EntityKeyboardMouseController() {};
//	//EntityKeyboardMouseController(Handle _entity_handle) : entity_handle(_entity_handle) {};
//
//	void assignEntity(Handle entity_handle);
//
//	void assignKeyPress(sf::Keyboard::Key key, entity_func_ptr func);
//	void assignKeyRelease(sf::Keyboard::Key key, entity_func_ptr func);
//	void assignKeyHeld(sf::Keyboard::Key key, entity_func_ptr func);
//
//	void assignMousePress(sf::Mouse::Button btn, entity_func_ptr func);
//	void assignMouseRelease(sf::Mouse::Button btn, entity_func_ptr func);
//	void assignMouseHeld(sf::Mouse::Button btn, entity_func_ptr func);
//
//	void handleInput(sf::Event input_event);									// calls function associated with input event, also iterates over held keys/buttons
//};

#endif // !CONTROLLER_H

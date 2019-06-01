#include "Controller.h"
#include "HandleManager.h"

#if _DEBUG
#include "Debug.h"
#endif

////extern HandleManager* handle_manager;
//
////void EntityKeyboardMouseController::assignEntity(Handle _entity_handle)
////{
////	entity_handle = _entity_handle;
////}
//
//void EntityKeyboardMouseController::assignKeyPress(sf::Keyboard::Key key, entity_func_ptr func) { key_press_table[key] = func; }
//void EntityKeyboardMouseController::assignKeyRelease(sf::Keyboard::Key key, entity_func_ptr func) { key_release_table[key] = func; }
//void EntityKeyboardMouseController::assignKeyHeld(sf::Keyboard::Key key, entity_func_ptr func) { key_held_table[key] = func; }
//
//void EntityKeyboardMouseController::assignMousePress(sf::Mouse::Button btn, entity_func_ptr func) { mouse_press_table[btn] = func; }
//void EntityKeyboardMouseController::assignMouseRelease(sf::Mouse::Button btn, entity_func_ptr func) { mouse_release_table[btn] = func; }
//void EntityKeyboardMouseController::assignMouseHeld(sf::Mouse::Button btn, entity_func_ptr func) { mouse_held_table[btn] = func; }
//
//void EntityKeyboardMouseController::addHeldKey(sf::Keyboard::Key key)
//{	
//	held_keys.push_back(key);
//}
//
//void EntityKeyboardMouseController::removeHeldKey(sf::Keyboard::Key key)
//{
//	for (size_t i = 0 ; i != held_keys.size() - 1; ++i)
//	{
//		if (held_keys[i] == key)
//			held_keys.erase(held_keys.begin() + i);
//	}
//}
//
//void EntityKeyboardMouseController::addHeldButton(sf::Mouse::Button btn)
//{
//	held_mouse_buttons.push_back(btn);
//}
//
//void EntityKeyboardMouseController::removeHeldButton(sf::Mouse::Button btn)
//{
//	for (size_t i = 0; i < held_mouse_buttons.size(); ++i)
//	{
//		if (held_mouse_buttons[i] == btn)
//			held_mouse_buttons.erase(held_mouse_buttons.begin() + i);
//	}
//}
//
//void EntityKeyboardMouseController::handleInput(sf::Event input_event)
//{
//	entity_func_ptr func = nullptr;
//	switch (input_event.type)
//	{
//	// keyboard events
//	case sf::Event::KeyPressed:
//		func = key_press_table[input_event.key.code];
//		addHeldKey(input_event.key.code);
//		break;
//
//	case sf::Event::KeyReleased:
//		func = key_release_table[input_event.key.code];
//		removeHeldKey(input_event.key.code);
//		break;
//
//	// mouse events
//	case sf::Event::MouseButtonPressed:
//		func = mouse_press_table[input_event.mouseButton.button];
//		addHeldButton(input_event.mouseButton.button);
//		break;
//
//	case sf::Event::MouseButtonReleased:
//		func = mouse_release_table[input_event.mouseButton.button];
//		removeHeldButton(input_event.mouseButton.button);
//		break;
//	}
//
//	Entity* entity = (Entity*)handle_manager->access(entity_handle);	// access entity
//	if (entity == nullptr)
//	{
//		#if _DEBUG
//		Debug::log("Entity assigned to current EntityController was nullptr.");
//		#endif // DEBUG
//		return;
//	}
//
//	(entity->*func)();	// call press/release function
//
//	// call all held key functions
//	for (size_t i = held_keys.size() - 1; i != 0; ++i)
//	{
//		func = key_held_table[held_keys[i]];
//		(entity->*func)();	// call function
//	}
//
//	// call all held button functions
//	for (size_t i = held_mouse_buttons.size() - 1; i != 0; ++i)
//	{
//		func = mouse_held_table[held_keys[i]];
//		(entity->*func)();	// call function
//	}
//}

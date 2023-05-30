#include "InputSystem.h"

static InputSystem* inputSingleton = nullptr;

InputSystem * InputSystem::getInstance()
{
	if (inputSingleton == nullptr)
	{
		inputSingleton = new InputSystem();
		return inputSingleton;
	}
	else
	{
		return inputSingleton;
	}

	return nullptr;
}

void InputSystem::init()
{
}

void InputSystem::release()
{
	delete this;
}

void InputSystem::addListener(InputListener * listener)
{
	listenersSet.insert(listener);
}

void InputSystem::removeListener(InputListener * listener)
{
	auto it = listenersSet.find(listener);  // Find iterator for element
	if (it != listenersSet.end()) {
		it = listenersSet.erase(it);  // Erase element and update iterator
	}
	//listenersSet.erase(listener);
}

void InputSystem::update()
{

	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (current_mouse_pos.x != old_mouse_pos.x || current_mouse_pos.y != old_mouse_pos.y)
	{
		// the mouse was moved
		std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

		while (it != listenersSet.end() && *it)
		{
			// notify listeners
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}

	old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y); //update last read position of the mouse



	if (::GetKeyboardState(keysState))
	{
		for (unsigned int i = 0; i < 256; ++i)
		{
			if (keysState[i] & 0x80)
			{ // KEY DOWN

				std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

				while (it != listenersSet.end() && *it)
				{
					(*it)->keyDown(i);
					++it;
				}
			}
			else
			{ //KEY UP

				if (keysState[i] != lastKeysState[i])
				{
					std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

					while (it != listenersSet.end() && *it)
					{
						(*it)->keyUp(i);
						++it;
					}
				}
				
			}
		}

		// store latest state
		::memcpy(lastKeysState, keysState, sizeof(unsigned char)*256);
	}
}

void InputSystem::handleLeftMouseDown()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

	while (it != listenersSet.end() && *it)
	{
		
		(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
		

		++it;
	}

	old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y); //update last read position of the mouse
}

void InputSystem::handleLeftMouseUp()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

	while (it != listenersSet.end() && *it)
	{

		(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));


		++it;
	}

	old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y); //update last read position of the mouse
}

void InputSystem::handleRightMouseDown()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

	while (it != listenersSet.end() && *it)
	{

		(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));


		++it;
	}

	old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y); //update last read position of the mouse
}

void InputSystem::handleRightMouseUp()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	std::unordered_set<InputListener*>::iterator it = listenersSet.begin();

	while (it != listenersSet.end() && *it)
	{

		(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));


		++it;
	}

	old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y); //update last read position of the mouse
}

void InputSystem::setCursorPosition(const Point & pos)
{
	::SetCursorPos(pos.x, pos.y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

InputSystem::InputSystem()
{
	// Initialize firs ever read position of the mouse
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);
	old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

}

InputSystem::~InputSystem()
{
}

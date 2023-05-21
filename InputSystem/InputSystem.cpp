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
}

void InputSystem::addListener(InputListener * listener)
{
	listenerMap.insert(std::make_pair<InputListener*, InputListener*>(std::forward<InputListener*>(listener), std::forward<InputListener*>(listener)));
}

void InputSystem::removeListener(InputListener * listener)
{
	std::map<InputListener*, InputListener*>::iterator it = listenerMap.find(listener);
	if (it != listenerMap.end())
	{
		listenerMap.erase(it);
	}

}

void InputSystem::update()
{
	if (::GetKeyboardState(keysState))
	{
		for (unsigned int i = 0; i < 256; ++i)
		{
			if (keysState[i] & 0x80)
			{ // KEY DOWN

				std::map<InputListener*, InputListener*>::iterator it = listenerMap.begin();

				while (it != listenerMap.end())
				{
					it->second->keyDown(i);
					++it;
				}
			}
			else
			{ //KEY UP

				if (keysState[i] != lastKeysState[i])
				{
					std::map<InputListener*, InputListener*>::iterator it = listenerMap.begin();

					while (it != listenerMap.end())
					{
						it->second->keyUp(i);
						++it;
					}
				}
				
			}
		}

		// store latest state
		::memcpy(lastKeysState, keysState, sizeof(unsigned char)*256);
	}
}

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

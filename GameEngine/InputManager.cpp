#include "InputManager.h"
#include <SDL.h>
#include <iostream>
#include "GameLoop.h"
using namespace std;
namespace GameEngine
{
	InputManager::InputManager() {}
	SDL_Event InputManager::getEvent()
	{
		return eve;
	}

	bool InputManager::KeyUp(const char* key)
	{
		return !keyState[key];
	}

	bool InputManager::OneClick(const char* key)
	{
		if (inputM.KeyUp(key))
		{
			return false;
			cout << "falseSwitched" << endl;
		}

		else
		{
			return true;
			cout << "trueSwitched" << endl;
		}
	}

	void InputManager::UpdateKeyStates(const char* key)
	{
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		SDL_Keycode kCode = SDL_GetKeyFromName(key);
		SDL_Scancode scan = SDL_GetScancodeFromKey(kCode);	
		if (scan != 0)
		{
			if (keyboardState[scan])
			{
				keyState[key] = true;
			}

			else
			{
				keyState[key] = false;
			}
		}
	}

	Position InputManager::getMousePosition()
	{
		return mousePosition;
	}

	void InputManager::Update(vector<SDL_Event> eve)
	{

	//	this->eve = eve;
		//
		//cout << "mousePos" << ":" << mousePosition.getX() << ":" << mousePosition.getY() << endl;
		//cout<<MouseButton()<<endl;
		//MouseButton();
		
		SDL_PumpEvents();
		MouseButton();
		for (SDL_Event e : eve)
		{
			mousePosition = Position(e.button.x, e.button.y);
			cout << "mousePos" << ":" << mousePosition.getX() << ":" << mousePosition.getY() << endl;
		}
		for (auto i = inputs.begin(); i != inputs.end(); i++)
		{
		
			UpdateKeyStates(i->first);
//			if (keyState[i->first] != NULL)
	//		{
			
				
			for (Input* input : i->second)
			{
				if (keyState[i->first] == true)
				{
					input->CallFunction();
				}

				if (input->getSwitchState())
				{
					//cout << "switchState" << endl;
					input->Update();
				}
			}

		//	}
		}
	}

	void InputManager::empty()
	{
		for (auto i = keyState.begin(); i != keyState.end(); i++)
		{
			i->second = false;
		}
	}
	std::vector<const char*> mouseButtons;
	string InputManager::MouseButton()
	{
		//cout << "MouseButton Function" << endl;
		char* s = "";
		int x, y;
		//SDL_PumpEvents();
		//int mouseId = SDL_BUTTON(SDL_GetMouseState(&x, &y));
		//switch (mouseId)
		//{
		if (SDL_GetMouseState(&x, &y) &  SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			s = "mouseLeft";
			mouseButtons.push_back(s);
			keyState[s] = true;
		}

		else if (SDL_GetMouseState(&x, &y) &  SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			s = "mouseRight";
			mouseButtons.push_back(s);
			keyState[s] = true;
		}

		else if (SDL_GetMouseState(&x, &y) &  SDL_BUTTON(SDL_BUTTON_MIDDLE))
		{
			s = "mouseMiddle";
			mouseButtons.push_back(s);
			keyState[s] = true;
		}

		else
		{
			for (const char* s : mouseButtons)
			{
				keyState[s] = false;
			}

			mouseButtons.clear();
		}
		mousePosition = Position(x, y);
		cout <<  s << endl;
		/*	break;
		case SDL_BUTTON_RIGHT:
			s = "mouseRight";
			keyState[s] = true;
			mouseButtons.push_back(s);
			break;
		case SDL_BUTTON_MIDDLE:
			s = "mouseMiddle";
			keyState[s] = true;
			mouseButtons.push_back(s);
			break;
		//}*/
		return s;
	}

	InputManager::~InputManager()
	{
		
	}

	InputManager inputM;
}

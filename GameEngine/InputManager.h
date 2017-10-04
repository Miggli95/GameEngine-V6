#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <map>
#include <SDL.h>
#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>
#include "Position.h"
#include "Input.h"
namespace GameEngine
{
	extern std::string keyPressed;
	extern bool IsDown;//= false;
	typedef std::function<void()> Callback;
	class InputManager
	{
	public:
		
		InputManager();
		SDL_Event getEvent();
		bool KeyUp(const char * key);
		void UpdateKeyStates(const char* key);
		Position getMousePosition();
		void Update(std::vector<SDL_Event> eve);
		void empty();
		bool OneClick(const char* key);
		//template <typename Object, typename FUNC>
		
		std::string MouseButton();
		template <typename Object, typename FUNC>
		void addFunction(Object* object, const char* key,FUNC func,bool switchState = false)
		{
			
			std::vector<Input*> functionList;
			Callback function = std::bind(func, object);
			//input->setFunction(key, function);
			Input* input = new Input(key, function,switchState);
			if (&inputs[key] != NULL)
			{
				inputs[key].push_back(input);
			}
			else
			{
				functionList.push_back(input);
				inputs.insert(std::make_pair(key, functionList));
				keyState.insert(std::make_pair(key, false));
			}
			
			//inputList.insert(std::make_pair((void*&)(function), input));
		}
		/*template <typename Object, typename FUNC>
		const char* getInput(Object* object, FUNC func)
		{
			Callback function = std::bind(func,object);
		    for (auto i = inputList.begin(); i != inputList.end(); i++)
			{
				std::cout << i->second->getKey() << endl;
			}
			std::cout << inputList.size() << endl;
			/*const char* key = "";
			if(inputList[&function]!=NULL)
				if (inputList[&function]->getKey() != NULL)
				key = inputList[&function]->getKey();
			//cout << key << endl;
			return inputList[(void*&)(function)]->getKey();
		}*/

		~InputManager();
	private:
		SDL_Event eve;
		Position mousePosition;
		std::unordered_map<const char*, std::vector<Input*>> inputs;
		std::unordered_map<void*, Input*> inputList;
		std::unordered_map<const char*, bool> keyState;
	};
	extern InputManager inputM;
}
#endif


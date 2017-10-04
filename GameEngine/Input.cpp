#include "Input.h"
#include <iostream>
#include "InputManager.h"
using namespace std;
namespace GameEngine
{
	Input::Input(const char* key, Input::Callback func,bool switchState) :function(func), key(key),switchState(switchState) { std::cout << Input::key << std::endl; }
	
	void Input::CallFunction()
	{
		if (switchState)
		{
			cout << "state"<<state << endl;
			if (!state)
			{
				function();
				state = true;
			}

		}
		else
		{
			function();
		}
	}

	void Input::Update()
	{
		bool temp;
		if (inputM.KeyUp(key))
		{
			temp = false;
			//cout << "falseSwitched" << endl;
		}

		else
		{
			temp = true;
			//cout << "trueSwitched" << endl;
		}
		state = temp;
	}

	bool Input::getSwitchState()
	{
		return switchState;
	}

	const char* Input::getKey()
	{
		return key;
	}

	Input::~Input()
	{
	}
}

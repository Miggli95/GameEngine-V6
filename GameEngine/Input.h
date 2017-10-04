#ifndef INPUT_H
#define INPUT_H
#include <functional>

namespace GameEngine
{
	class Input
	{
	public:
		
		void CallFunction();
		typedef std::function<void()> Callback;
		//template <typename Object, typename FUNC>
		Input(const char* key, Callback func,bool switchState);
		Input() {}
		const char* getKey();
		/*void setFunction(const char* key, Callback func)
		{
			function = func;
			//std::vector<Callback> functionList;
			/*function = std::bind(func, object);
			if (&inputs[key] != NULL)
			{
				inputs[key].push_back(function);
			}
			else
			{
				functionList.push_back(function);
				inputs.insert(std::make_pair(key, functionList));
				keyState.insert(std::make_pair(key, false));
			}
		}*/
		void Update();
		bool getSwitchState();
		~Input();

	private:
		Callback function;
		const char* key;
		bool switchState;
		bool state;
	};
}
#endif


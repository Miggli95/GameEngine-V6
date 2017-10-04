#ifndef INVENTORY_H
#define INVENTORY_H
#include "UIItem.h"
#include "Item.h"
#include <unordered_map>
#include <vector>

namespace GameEngine
{
	class Inventory : public Entity
	{
	public:
		Inventory(Position* position);
		void Click();
		void State();
		void SwitchVisibilty();
		void setVisible(bool visible);
		void Update(SDL_Event eve, int fps, bool newInput);
		void AddItem(UIItem* item);
		UIItem* getSelectedItem();
		void Draw();
		~Inventory();


	private:
		bool visible = true;
		bool switched = false;
		SDL_Surface* background;
		Sprite* backgroundSprite;
		bool backgroundSet = false;
		//std::unordered_map<UIItem*, Item*> inventory;
		UIItem* selectedItem;
		std::vector<UIItem*> inventory;
	};
}

#endif


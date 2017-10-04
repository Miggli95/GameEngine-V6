#include "Inventory.h"
#include "InputManager.h"
#include "System.h"
using namespace std;
namespace GameEngine
{
	typedef _List_iterator < _List_val <_List_simple_types < pair<UIItem* const , Item*>>>> iter;
	Inventory::Inventory(Position* position):Entity(position)
	{
		inputM.addFunction(this, "mouseLeft", &Inventory::Click);
		inputM.addFunction(this, "V", &Inventory::SwitchVisibilty,true);
		 //SDL_PIXELFORMAT_RGBA32);  
		//background = new SDL_Surface();
		
		/*SDL_PixelFormat* format = SDL_GetWindowSurface(sys.getWin())->format;

		background = SDL_CreateRGBSurface(NULL, 10, 10,
			format->BitsPerPixel,format->Rmask, format->Gmask, format->Bmask, format->Amask);
		backgroundSprite = new Sprite(background, *getPosition());
		//Uint32 color = SDL_MapRGBA(backgroundSprite->format(), 100, 100, 100, 255);
		
		backgroundSprite->FillSurface(NULL);*/
	}

	UIItem* Inventory::getSelectedItem()
	{
		return selectedItem;
	}

	void Inventory::Click()
	{
		if (visible)
		{
			for (UIItem* item : inventory)
			{
				if (item->Clicked())
				{
					item->OnClickEvent();
					selectedItem = item;
				}
			}
		}
	}

	void Inventory::State()
	{
		if (inputM.KeyUp("V"))
		{
			switched = false;
			cout << "falseSwitched" << endl;
		}

		else
		{
			switched = true;
			cout << "trueSwitched" << endl;
		}
	}

	void Inventory::Update(SDL_Event eve, int fps,bool newInput)
	{
		/*if (!backgroundSet)
		{
			float difX = 0;
			float difY = 0;
			float difPosX = 0;
			float difPosY = 0;
			for (UIItem* item : inventory)
			{
				if (item->getPosition()->getX()  - item->getSprite()->getWidth() < getPosition()->getX()-difPosX)
				{
					difPosX =  getPosition()->getX() - item->getSprite()->getWidth();

				}

				else if(item->getPosition()->getX() + item->getSprite()->getWidth() > getPosition()->getX()+backgroundSprite->getWidth())
				{
					difX = (getPosition()->getX() + backgroundSprite->getWidth()) - (item->getPosition()->getX() + item->getSprite()->getWidth());
					
				}

				if (item->getPosition()->getY() - item->getSprite()->getHeight() < getPosition()->getY() - difPosX)
				{
					difPosY = getPosition()->getY() - item->getSprite()->getHeight();

				}

				else if (item->getPosition()->getY() + item->getSprite()->getHeight() > getPosition()->getY() + backgroundSprite->getHeight())
				{
					difY = (getPosition()->getY() + backgroundSprite->getHeight()) - (item->getPosition()->getY() + item->getSprite()->getHeight());

				}
				
			}

			if (difX != 0 || difY != 0)
			{
				backgroundSprite->ExtendSurface(difX, difY);
				//Uint32 color = SDL_MapRGBA(backgroundSprite->format(), 100, 100, 100, 255);
				backgroundSprite->FillSurface(NULL);
			}

			if (difPosX != 0 || difPosY != 0)
			{
				getPosition()->setX(getPosition()->getX() + difPosX);
				getPosition()->setY(getPosition()->getY() + difPosY);
			}
		}*/
		//const char* key =  inputM.getInput(this, &Inventory::SwitchVisibilty);
		//cout << "key: stuff "<< key << endl;
		//switched = inputM.OneClick(key);
	}

	void Inventory::SwitchVisibilty()
	{
		//if (!switched)
		//{
			visible = !visible;
			switched = true;
		//}
	}

	Inventory::~Inventory()
	{
	}

	void Inventory::AddItem(UIItem* item)
	{
		inventory.push_back(item);
		backgroundSet = false;
	}

	void Inventory::Draw()
	{
		/*for (iter i = inventory.begin(); i != inventory.end(); i++)
		{
			i->first->Draw();
		}*/
		if (visible)
		{
			//backgroundSprite->Draw(getPosition());
			for (UIItem* item : inventory)
			{
				item->Draw();
			}
		}
	}
}

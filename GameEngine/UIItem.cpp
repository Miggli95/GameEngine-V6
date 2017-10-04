#include "UIItem.h"
#include "InputManager.h"

using namespace std;
namespace GameEngine
{
	UIItem::UIItem(const char* iconPath, Position* position, bool interactable, SDL_Rect* collisionRect) : NonAnimatedObjects(position, iconPath, TagUI), interactable(interactable)
	{
		UIItem::collisionRect = setCollisionRect(collisionRect, getSprite());
		//inputM.addFunction(this, "mouseLeft", &UIItem::OnClickEvent);
	}

	SDL_Rect UIItem::setCollisionRect(SDL_Rect* col, Sprite* icon)
	{
		if (col == NULL)
		{
			if (icon != NULL)
			{
				return icon->GetBounds();
			}
		}

		else
		{
			return *col;
		}
	}

	/*void UIItem::Update(SDL_Event eve, int fps, bool newInput)
	{
		if (interactable)
		{
			if (Clicked())
			{
				cout << "UIItem clicked" << endl;
			}
		}
	}*/

	bool UIItem::Clicked()
	{
		Position pos = inputM.getMousePosition();
		SDL_Point p = SDL_Point{ (int)pos.getX(),(int)pos.getY() };
		//cout << "mousePos" << ":" << pos.getX() << ":" << pos.getY() << endl;
		return SDL_PointInRect(&p, &collisionRect);
	}

	void UIItem::OnClickEvent()
	{
		if (Clicked())
		{
			cout << "Clicked" << endl;
		}
	}

	UIItem::~UIItem()
	{
		delete icon;
	}
}

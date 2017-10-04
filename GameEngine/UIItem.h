#ifndef  UIITEM_H
#define UIITEM_H
#include "Sprite.h"
#include "Position.h"
#include "Entity.h"
#include "NonAnimatedObjects.h"
namespace GameEngine
{
	class UIItem : public NonAnimatedObjects
	{
		
	public:
		static const int TagUI = 5;
		UIItem(const char* iconPath, Position* position, bool interactable = true, SDL_Rect* collisionRect = NULL);
		SDL_Rect setCollisionRect(SDL_Rect * col, Sprite * icon);
		bool Clicked();
		void OnClickEvent();
		//void Update(SDL_Event eve, int fps, bool newInput = false);
		~UIItem();

	private:
		bool interactable;
		SDL_Rect collisionRect;
		Sprite* icon;
	};
}
#endif


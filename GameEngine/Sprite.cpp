#include "Sprite.h"
#include "System.h"
#include "Position.h"
#include <iostream>

using namespace std;
namespace GameEngine
{
	Sprite::Sprite(const char* texturePath,Position pos,bool streamable) :  position(pos)
	{
		
		SDL_Surface* loadedSurf = IMG_Load(texturePath);
		if (loadedSurf == NULL)
		{
			cout << "Unable to load image" << endl;	
		}


		else
		{
			cout << "Surface" << ":"<< position.getX() << ":" << position.getY()<<endl;
			surf = SDL_ConvertSurfaceFormat(loadedSurf, SDL_PIXELFORMAT_RGBA8888, 0);
			texture = SDL_CreateTexture(sys.getRen(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, surf->w, surf->h);//SDL_CreateTextureFromSurface(sys.getRen(), surf);
			
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
			SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_BLEND);
			setColorKey(transparent);
			pixelWidth = (surf->pitch / 4);
			pixelHeight = surf->h;
			pixelCount = pixelWidth * pixelHeight;
			width = surf->w;
			height = surf->h;
			transparent = SDL_MapRGBA(format(), 100, 100, 100, 0);
			Done(true);
		}
	}

	Sprite::Sprite(SDL_Surface* loadedSurf, Position pos) :position(pos)
	{
		if (loadedSurf != NULL)
		{
			surf = SDL_ConvertSurfaceFormat(loadedSurf, SDL_PIXELFORMAT_RGBA8888, 0);
			texture = SDL_CreateTexture(sys.getRen(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, surf->w, surf->h);//SDL_CreateTextureFromSurface(sys.getRen(), surf);
			
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
			SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_BLEND);
			setColorKey(transparent);
			pixelWidth = (surf->pitch / 4);
			pixelHeight = surf->h;
			pixelCount = pixelWidth * pixelHeight;
			width = surf->w;
			height = surf->h;
			transparent = SDL_MapRGBA(format(), 100, 100, 100, 0);
			Done(true);
		}

		else
		{
			cout << "loadedSurf NULL" << endl;
		}
	}

	void Sprite::ExtendSurface(float xSize, float ySize)
	{
		if (surf != NULL)
		{
			int w = surf->w + xSize;
			int h = surf->h + ySize;
			SDL_Surface* biggerSurf = SDL_CreateRGBSurface(surf->flags, w, h,
				format()->BitsPerPixel, format()->Rmask, format()->Gmask, format()->Bmask, format()->Amask);
			Uint32 color = SDL_MapRGBA(format(), 100, 100, 100, 255);
			SDL_FillRect(biggerSurf, NULL, TRANSPARENT());
			SDL_Rect offset = SDL_Rect{ w / 2,h / 2,0,0 };
			SDL_BlitSurface(surf, NULL, biggerSurf, &offset);
			SDL_FreeSurface(surf);
			width = w;
			height = h;
			surf = biggerSurf;

			SDL_DestroyTexture(texture);
			texture = SDL_CreateTexture(sys.getRen(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, surf->w, surf->h);
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
			Done(true);
		}
	}

	void Sprite::ExtendSurface(float size)
	{
		if (surf != NULL)
		{
			int w = surf->w*size;
			int h = surf->h*size;
			SDL_Surface* biggerSurf = SDL_CreateRGBSurface(surf->flags, w, h, 
				format()->BitsPerPixel, format()->Rmask, format()->Gmask, format()->Bmask, format()->Amask);	
			Uint32 color = SDL_MapRGBA(format(),100, 100, 100, 255);
			SDL_FillRect(biggerSurf,NULL, TRANSPARENT());
			SDL_Rect offset = SDL_Rect{ w/2,h/2,0,0 };
			SDL_BlitSurface(surf, NULL, biggerSurf, &offset);
			SDL_FreeSurface(surf);
			width = w;
			height = h;
			surf = biggerSurf;
			SDL_DestroyTexture(texture);
			texture = SDL_CreateTexture(sys.getRen(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, surf->w, surf->h);
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
			Done(true);

		}
	}

	void Sprite::setColorKey(const Uint32 colorKey)
	{
		SDL_SetColorKey(surf,true, colorKey);
	}

	void Sprite::setColorKey(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		Uint32 colorKey = SDL_MapRGBA(surf->format, r, g, b, a);
		setColorKey(colorKey);
	}

	Uint32 Sprite::Color(Uint8 color [4])
	{
		Uint32 formattedColor = SDL_MapRGBA(surf->format,color[0],color[1],color[2],color[3]);
		return formattedColor;
	}

	void Sprite::FillSurface(Uint32 color)
	{
		Uint32 colorC = SDL_MapRGBA(format(), 100, 100, 100, 255);
		SDL_FillRect(surf, NULL, colorC);
	}

	void Sprite::ChangePixel(int x, int y, Uint32 color)
	{
		Uint8 r, g, b, a;
		if (surf != NULL)
		{
			//SDL_LockSurface(surf);
			//change

			if (getPixel(x, y) != color && WithinBounds(x, y))
			{
				setPixel(x, y, color);
			}

			//SDL_UnlockSurface(surf);
		}

		else
		{
			cout << "SDL_Surface == null" << endl;
		}
	}

	void Sprite::Done(bool done)
	{
		if (done == true)
		{
			SDL_UpdateTexture(texture, NULL, surf->pixels, surf->pitch);
				/*
			SDL_Texture* newTexture = SDL_CreateTextureFromSurface(sys.getRen(), surf);

			SDL_DestroyTexture(texture);
			texture = NULL;
			texture = newTexture;
			newTexture = NULL;*/
			
		}
	}

	bool Sprite::WithinBounds(int x, int y)
	{
		if (x>getFrameBounds().w + getFrameBounds().x)
		{
			return false;
		}
		else if (x<getFrameBounds().x)
		{
			return false;
		}
		if (y > getFrameBounds().h + getFrameBounds().y)
		{
			return false;
		}
		else if (y < getFrameBounds().y)
		{
			return false;
		}

		return true;
	}

	Uint32 Sprite::getPixel(int x, int y)
	{
		if (!WithinBounds(x,y))
		{
			return NULL;
		}

		int bytesPerPixel = surf->format->BytesPerPixel;
		//p is the address to the pixel we want to retrieve
		Uint8 *p = (Uint8 *)surf->pixels + y*surf->pitch + x * bytesPerPixel;
		Uint32 pixel = 0;
		//SDL_LockSurface(surf);
		switch (bytesPerPixel)
			{
			case 1:
				pixel = *p;
				break;
			case 2:
				pixel = *(Uint16*)p;
				break;
			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					pixel = p[0] << 16 | p[1] << 8 | p[2];
				else
				{
					pixel = p[0] | p[1] << 8 | p[2] << 16;
				}
				break;

			case 4:
				pixel = *(Uint32 *)p;
				break;
			}
		//SDL_UnlockSurface(surf);
		return pixel;
	}

	void Sprite::setPixel(int x, int y, Uint32 pixel)
	{
		int bytesPerPixel = surf->format->BytesPerPixel;
		//p is the address to the pixel we want to set
		Uint8 *p = (Uint8 *)surf->pixels + y * surf->pitch + x * bytesPerPixel;
		switch (bytesPerPixel)
		{
		case 1:
			*p = pixel;
			break;
		case 2:
			*(Uint16 *)p = pixel;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			}

			else
			{
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;

		}
	}

	SDL_Rect Sprite::GetBounds()
	{

		Position origin = Position(getFrameBounds().w / 2, getFrameBounds().h / 2);
		SDL_Rect bounds;
		bounds.x = (Sint16)(getPosition().getX() - origin.getX());
		bounds.y = (Sint16)(getPosition().getY() - origin.getY());
		bounds.w = (Sint16)(getFrameBounds().w);
		bounds.h = (Sint16)(getFrameBounds().h);
		return bounds;
	}

	void Sprite::Draw(Position* pos)
	{
		SDL_RenderCopyEx(sys.getRen(), texture, &getFrameBounds(), &GetBounds(), rotation, NULL, flipMode);
	}

	int Sprite::getAlpha(int x, int y)
	{
		Uint8 r, g, b, a;
		Uint32 pixel = getPixel(x, y);
		if (pixel != NULL)
		{
			Uint32 alpha = pixel & surf->format->Amask;
			alpha = alpha >> surf->format->Ashift;
			alpha = alpha << surf->format->Aloss;
			return (int)alpha;
		}
		else
		{
			return NULL;
		}
	}

	Sprite::~Sprite()
	{
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surf);
	}
}

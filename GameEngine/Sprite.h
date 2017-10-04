#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <SDL_image.h>
#include "Position.h"
namespace GameEngine
{
	class Sprite
	{
	public:
		static Sprite* getInstance(const char* texturePath,Position pos, bool streamable)
		{
			return new Sprite(texturePath,pos, streamable);
		}

		void ChangePixel(int x, int y, Uint32 color);
		int getPixelCount() { return pixelCount; }
		int getPixelWidth() { return pixelWidth; }
		int getPixelHeight() { return pixelHeight; }
		int getWidth() { return width; }
		int getHeight() { return height; }
		void Done(bool done);
		bool WithinBounds(int x, int y);
		SDL_PixelFormat* format() { return surf->format; }
		void setColorKey(Uint32 colorKey);
		void setColorKey(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		Uint32 Color(Uint8 color[4]);
		void FillSurface(Uint32 color);
		const Uint32 TRANSPARENT() { return transparent; }
		virtual void Update(int fps) {}
		virtual void Idle(int fps) {}
		virtual bool PlayedThrough() { return true; }
		virtual void Draw(Position* pos);
		virtual SDL_Rect getFrameBounds() { return SDL_Rect{ 0,0,0,0 }; }
		SDL_Texture* getTexture() { return texture; }
		void setTexture(SDL_Texture* tex) {texture = tex; }
		Uint32 getPixel(int x, int y);
		int getAlpha(int x, int y);
		void Rotate(float angle) { rotation = angle; }
		~Sprite();
		SDL_Rect GetBounds();
		void setFlipMode(SDL_RendererFlip flipM) { flipMode = flipM; }
		void ExtendSurface(float size);
		void ExtendSurface(float xSize, float ySize);
		Position getPosition() { return position; }
		void setPosition(Position pos) { position = pos; }
		Sprite(SDL_Surface* surf, Position pos);
	protected:
		Sprite(const char* texturePath,Position pos,bool streamable);
		void CopyPixels();
	private:
		SDL_RendererFlip flipMode = SDL_FLIP_NONE;
		Position position;
		SDL_Surface* surf;
		SDL_Texture* texture;
		float width, height;
		int pixelCount;
		int pixelWidth;
		int pixelHeight;
		Uint32 transparent;
		SDL_Rect frameBounds;
		float rotation = 0; 
		void Sprite::setPixel(int x, int y, Uint32 pixel);
		void* mPixels;
		int mPitch;
	};
}
#endif


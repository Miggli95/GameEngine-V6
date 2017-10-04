#include "Position.h"
#include <iostream>
#include "GameLoop.h"
using namespace std;
namespace GameEngine
{
	Position::Position(float x, float y) :x(x), y(y) {}
	float Position::getX(){ return x; }
	float Position::getY() { return y; }
	float Position::setX(float x) { return Position::x = x; }
	float Position::setY(float y) { return Position::y = y; }
	Position* Position::setVelocity(Position & pos, float speed)
	{
		pos *= speed*10;
		pos *= game.getDeltaTime();
		*this += pos;
		return &pos;
	}

	Position* Position::InvertVelocity(Position & pos, float speed)
	{
		pos *= -speed;
		*this += pos;
		return &pos;
	}

	Position & Position::operator+(Position * pos)
	{
		*this += *pos;
		return *this;
	}

	Position & Position::operator-(Position & pos)
	{
		*this -= pos;
		return *this;
	}
	const Position & Position::operator+=(Position & pos)
	{
		float x = getX();
		float x2 = pos.getX();
		x += x2;
		setX(x);
		float y = getY();
		float y2 = pos.getY();
		y += y2;
		setY(y);
		return *this;
	}
	const Position & Position::operator-=(Position & pos)
	{
		float x = getX();
		float x2 = pos.getX();
		x -= x2;
		setX(x);
		float y = getY();
		float y2 = pos.getY();
		y -= y2;
		setY(y);
		return *this;
	}
	const Position& Position::operator*=(const float f)
	{
		float x = f*getX();
		float y = f*getY();
		setX(x);
		setY(y);
		return *this;
	}

	Position::~Position()
	{
	}
}

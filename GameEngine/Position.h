#ifndef POSITION_H
#define POSITION_H
namespace GameEngine
{
	class Position
	{
	public:
		Position(float x = 0, float y = 0);
		float getX();
		float getY();
		float setX(float x);
		float setY(float y);
		Position* setVelocity(Position& pos, float speed = 1);
		Position * InvertVelocity(Position & pos, float speed = 1);
		Position & operator+(Position* pos);
		Position & operator-(Position& pos);
		const Position & operator*=(const float f);
		Position::~Position();
	private:
		float x, y;
		const Position& operator+=(Position& pos);
		const Position& operator-=(Position& pos);
	};
}
#endif

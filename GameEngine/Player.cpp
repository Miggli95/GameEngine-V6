#include "Player.h"
#include <map>
#include <iostream>
#include "System.h"
#include "GameLoop.h"
#include "TurnManager.h"
#include "Physics.h"
using namespace std;
namespace GameEngine
{
	
	Player::Player(Position* position, const char* texturePath, int frames, int rows,
		std::string up, std::string down, std::string left,
		std::string right) : Alive(position, texturePath, frames, rows, PixelCollider::TAGPLAYER)
	{
		turnM.addPlayer();
		playerId = turnM.getPlayerID();
		playerNumber = turnM.getPlayerID();
		//cout << "ID"<<playerId<<endl;
		Position* temp = getPosition();
		getSprite()->setColorKey(255, 0, 255);
		inputM.addFunction(this, "W", &Player::Up);
		inputM.addFunction(this, "S", &Player::Down);
		inputM.addFunction(this, "A", &Player::Left);
		inputM.addFunction(this, "D", &Player::Right);
		inputM.addFunction(this, "mouseRight", &Player::Teraform);
		inputM.addFunction(this, "Space", &Player::Jump, true);
		inputM.addFunction(this, "mouseLeft", &Player::Shoot);
		inputM.addFunction(this, "R", &Player::Reload);
		weapon = new Weapon(getPosition(), "bazooka.png", this);
	}

	int Player::getPlayerHealth()
	{
		return playerHealth;
	}

	void Player::ChangeID(int ID)
	{
		playerId = ID;
	}

	void Player::Damage(float damage)
	{
		playerHealth -= damage;
	}

	void Player::Update(SDL_Event eve, int fps, bool newInput)
	{
		Alive::Update(eve, fps);
		turnM.IncreaseChangeTimer(10);
	}

	void Player::Teraform()
	{
		if (myTurn() && weapon->Reloaded() && getPixelCollider()->isGrounded())
		{
			weapon->Shoot(true);
			turnM.setChangePlayer(true);
		}
	}

	float angle;
	void Player::Reload()
	{
		if (myTurn())
		{
			weapon->Reload();
		}
	}

	void Player::Jump()
	{
		if (myTurn())
		{
			if (getPixelCollider()->isGrounded())
			{
				float jumpHeight = 0;
				Position origin = Position(getSprite()->getFrameBounds().w / 2, getSprite()->getFrameBounds().h / 2);
				Sprite* s = getSprite();
				int x = getPosition()->getX() - origin.getX();
				int y = getPosition()->getY() - origin.getY();
				int w = s->getFrameBounds().w;
				int h = s->getFrameBounds().h;
			
				//SDL_RenderFillRect(sys.getRen(), &topCollider);
				for (int i = 0; i < 10; i++)
				{
					float tempJumpHeight = jumpHeight + 100;
					topCollider = SDL_Rect{ (int)x,(int)(y - tempJumpHeight),w,40 };
					//cout << "topCollider" << topCollider.y << endl;
					if (!physics.CollidingWithTerrain(topCollider))
					{
						jumpHeight = tempJumpHeight;
						getPixelCollider()->setVelocity(Position(0, -100));
					}

					else
					{
						break;
					}
				}
				SDL_RenderFillRect(sys.getRen(), &topCollider);

				cout << "jumpHeight" << jumpHeight<< endl;
				
			}
		}
	}

	int Player::getID()
	{
		return playerId;
	}

	int Player::getPlayerNumber()
	{
		return playerNumber;
	}

	bool Player::myTurn()
	{
		return turnM.getCurrentPlayer() == playerId && turnM.getChangePlayer() == false;
	}

	void Player::Up()
	{
		if(myTurn())
			weapon->AimUp();
	}

	void Player::Shoot()
	{
		//cout << "shoot" << endl;
		if (myTurn() && weapon->Reloaded()  && getPixelCollider()->isGrounded())
		{
			weapon->Shoot();
			turnM.setChangePlayer(true);
		}
	}

	void Player::Down()
	{
		if (myTurn())
			weapon->AimDown();
	}

	void Player::Left()
	{
		if (myTurn())
		{
			getSprite()->setFlipMode(SDL_FLIP_NONE);
			getSprite()->Rotate(angle);
			getSprite()->Update(7);
			weapon->Flip(false);
			getPixelCollider()->setVelocity(Position(-2, 0));
		}
	}
	void Player::Right()
	{
		if (myTurn())
		{
			getSprite()->setFlipMode(SDL_FLIP_HORIZONTAL);
			getSprite()->Rotate(angle);
			getSprite()->Update(7);
			weapon->Flip(true);
			getPosition()->setVelocity(Position(2, 0));
		}
	}

	Player::~Player()
	{
		//cout << "PlayerDestructor" << endl;
	}
}

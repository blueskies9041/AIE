#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Sprite.h"
#include <map>
using std::string;

enum PLAYER_STATE
{
	WARP,
	RUN,
	IDLE
};

class Player : public Sprite
{

	public:

		Player();
		~Player();
		void Draw();
		void Input();
		bool CheckBoxCollision(Sprite &a_roSprite); //Needs to be redone, maybe to circle collision instead

	private:

		PLAYER_STATE m_State;

};

#endif
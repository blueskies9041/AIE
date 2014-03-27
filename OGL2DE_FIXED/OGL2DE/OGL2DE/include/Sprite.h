#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Quad.h"
#include <vector>

enum ANIMATION_TYPE
{
	ONCE,
	LOOP,
	REVERSE
};

/* Animation Structure */

struct Animation
{
	std::vector< glm::vec2> m_FrameData; //Texture coordinates expressed as Normalized Device Coordinates
	float m_fElapsedTime; //Time since last animation occured
	int m_iNumFrames; //Max Frame Count
	int m_iCurrentFrame;
	ANIMATION_TYPE m_TYPE; //For later use in determining animation behavior
};

/* 
	Sprite Class

	Base class to be inherited from by specific sprite types, manages animations and game relevant numerical values (position, velocity, scale etc...).

*/

class Sprite : public Quad
{
	public:

		Sprite( const char* a_TexFilepath, int a_iWidth, int a_iHeight, int a_iFrameWidth, int a_iFrameHeight, GLFWwindow * a_opWindow);
		~Sprite();
		void Draw();
		void Play(Animation &a_roAnimation);
		glm::vec3 m_v3Position;

	protected:

		GLFWwindow * m_oGameWindow;
		std::vector<Animation> m_Animations;
		glm::vec3 m_v3Speed;
		glm::vec2 m_v2Scale;
		glm::vec4 m_v4SpriteColor;
};

#endif
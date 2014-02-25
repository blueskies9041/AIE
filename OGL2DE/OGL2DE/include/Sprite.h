#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Quad.h"

class CSprite : public CQuad
{
	public:

		CSprite( const char* a_TexFilepath, int a_iWidth, int a_iHeight, int a_iTexWidth, int a_iTexHeight, int a_iFrameWidth, int a_iFrameHeight, GLFWwindow * a_opWindow);
		~CSprite();

		void Draw();
		void Input();
		void Cleanup();
	
		bool CheckBoxCollision(CSprite &a_roSprite);

	protected:

		GLFWwindow * m_oGameWindow;

		glm::vec3 m_v3Position;
		glm::vec3 m_v3Speed;
		glm::vec2 m_v2Scale;
		glm::vec4 m_v4SpriteColor;

		int m_iMatrixLocation;
		int m_iTextureLocation;
		int m_iProjectionLocation;
		int m_iViewLocation;

};

#endif
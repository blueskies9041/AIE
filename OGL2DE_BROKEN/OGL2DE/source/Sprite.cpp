#include "Sprite.h"
#include <iostream>

using std::cout;
using Sam::g_iWindowWidth;
using Sam::g_iWindowHeight;

Sprite::Sprite( const char* a_TexFilepath, int a_iWidth, int a_iHeight, int a_iTexWidth, int a_iTexHeight,int a_iFrameWidth, int a_iFrameHeight, GLFWwindow * a_opWindow)
	: Quad(a_TexFilepath, a_iWidth, a_iHeight, a_iTexWidth, a_iTexHeight, a_iFrameWidth, a_iFrameHeight)
{
	m_oGameWindow = a_opWindow; // Pass in the App Window for glfw stuff
	LoadVertShader("resources/shaders/basic.vert");
	LoadFragShader("resources/shaders/basic.frag");
	LinkShaders();

	LoadTexture(a_TexFilepath);

	m_v3Position = glm::vec3(g_iWindowWidth / 2, g_iWindowHeight / 2, 0.0f);
	m_v3Speed = glm::vec3(0.0f, 0.0f, 0.0f);
	m_v2Scale = glm::vec2((float)a_iWidth, (float)a_iHeight);
	m_v4SpriteColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	
	m_aoVertices[0].Color = m_v4SpriteColor;
	m_aoVertices[1].Color = m_v4SpriteColor;
	m_aoVertices[2].Color = m_v4SpriteColor;
	m_aoVertices[3].Color = m_v4SpriteColor;

}

Sprite::~Sprite()
{
}

void Sprite::Draw()
{
	m_Model[0][0] = m_v2Scale.x;
	m_Model[1][1] = m_v2Scale.y;
	m_Model[3][0] = m_v3Position.x;
	m_Model[3][1] = m_v3Position.y;
	m_Model[3][2] = m_v3Position.z;

	glm::mat4 MVP = g_Projection  * m_Model;
	glUniformMatrix4fv( m_glMatrixID,
						1,
						GL_FALSE,
						glm::value_ptr(MVP)); //have to use glm::value_ptr with glm

	Quad::Draw();

}

void Sprite::Play(Animation &a_roAnimation)
{
	static double dFrameLimit = 1.0 / 15.0;

	a_roAnimation.m_fElapsedTime += g_fDeltaTime;

	if(a_roAnimation.m_fElapsedTime >= dFrameLimit)
	{
		a_roAnimation.m_fElapsedTime = 0.0f;
		SetUVOffset(a_roAnimation.m_FrameData[a_roAnimation.m_iCurrentFrame]);
		a_roAnimation.m_iCurrentFrame++;

		if(a_roAnimation.m_iCurrentFrame >= a_roAnimation.m_iNumFrames)
			a_roAnimation.m_iCurrentFrame = 0;
	}
}


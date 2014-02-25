#include "Sprite.h"

CSprite::CSprite( const char* a_TexFilepath, int a_iWidth, int a_iHeight, int a_iTexWidth, int a_iTexHeight,int a_iFrameWidth, int a_iFrameHeight, GLFWwindow * a_opWindow)
	: CQuad(a_TexFilepath, a_iWidth, a_iHeight, a_iTexWidth, a_iTexHeight, a_iFrameWidth, a_iFrameHeight)
{
	m_oGameWindow = a_opWindow; // Pass in the App Window for glfw stuff

	m_v3Position = glm::vec3(iWindowWidth / 2, iWindowHeight / 2, 0.0f);
	m_v3Speed = glm::vec3(0.0f, 0.0f, 0.0f);
	m_v2Scale = glm::vec2((float)a_iWidth, (float)a_iHeight);
	m_v4SpriteColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	m_Model[0][0] = m_v2Scale.x;
	m_Model[1][1] = m_v2Scale.y;
	m_Model[3][0] = m_v3Position.x;
	m_Model[3][1] = m_v3Position.y;
	m_Model[3][2] = m_v3Position.z;	
}

CSprite::~CSprite(){
}

void CSprite::Draw() {

	//Input();
	m_Model[0][0] = m_v2Scale.x;
	m_Model[1][1] = m_v2Scale.y;
	m_Model[3][0] = m_v3Position.x;
	m_Model[3][1] = m_v3Position.y;
	m_Model[3][2] = m_v3Position.z;

	Update();

}



void CSprite::Input() {

	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	//m_v3Speed = glm::vec3(0.0f, 0.0f, 0.0f);

	if (GLFW_PRESS == glfwGetKey(m_oGameWindow, GLFW_KEY_W))
		m_v3Speed.y -= 1.0f;
		
    if (GLFW_PRESS == glfwGetKey(m_oGameWindow, GLFW_KEY_A))
        m_v3Speed.x -= 1.0f;

    if (GLFW_PRESS == glfwGetKey(m_oGameWindow, GLFW_KEY_S))
		m_v3Speed.y += 1.0f;

    if (GLFW_PRESS == glfwGetKey(m_oGameWindow, GLFW_KEY_D))
        m_v3Speed.x += 1.0f;

	m_v3Position += (m_v3Speed * deltaTime );
}

bool CSprite::CheckBoxCollision(CSprite &a_roSprite) {

	glm::vec3 v3Source = m_v3Position;
	glm::vec3 v3Target = a_roSprite.m_v3Position;

	return (abs(v3Source.x - v3Target.x) * 2) <  (m_v2Scale.x + a_roSprite.m_v2Scale.x)
		&& (abs(v3Source.y - v3Target.y) * 2) <  (m_v2Scale.y + a_roSprite.m_v2Scale.y);
}

void CSprite::Cleanup() {
	glDeleteTextures(1, &m_glTexture);
	glDeleteShader(m_glShaderProgram);
	glDeleteBuffers(1, &m_glVBO);
	glDeleteBuffers(1, &m_glEBO);
	glDeleteVertexArrays(1, &m_glVAO);
}


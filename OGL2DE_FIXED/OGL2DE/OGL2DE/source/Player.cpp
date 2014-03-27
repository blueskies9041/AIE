#include "Player.h"
#include "Window.h"

Player::Player() : Sprite( "resources/graphics/ZeroSpriteSheet.png", 150, 150, 75, 75, Window::GetInstance().GetContext())
{

	m_oGameWindow = Window::GetInstance().GetContext();

	Animation * Jump = new Animation;
	Jump->m_fElapsedTime = 0.0f;
	Jump->m_iNumFrames = 10;
	Jump->m_iCurrentFrame = 0;
	for(int i = 0; i < Jump->m_iNumFrames; ++i)
		Jump->m_FrameData.push_back(glm::vec2( m_v2FrameDimensionsNorm.x * i, m_v2FrameDimensionsNorm.y));

	m_Animations.push_back(*Jump);

	Animation * Run = new Animation;
	Run->m_fElapsedTime = 0.0f;
	Run->m_iNumFrames = 8;
	Run->m_iCurrentFrame = 0;
	for(int i = 0; i < Run->m_iNumFrames; ++i)
		Run->m_FrameData.push_back(glm::vec2( (m_v2FrameDimensionsNorm.x * 3) + (m_v2FrameDimensionsNorm.x * i) , m_v2FrameDimensionsNorm.y * 2));

	m_Animations.push_back(*Run);

	Animation * Idle = new Animation;
	Idle->m_fElapsedTime = 0.0f;
	Idle->m_iNumFrames = 1;
	Idle->m_iCurrentFrame = 0;
	for(int i = 0; i < Idle->m_iNumFrames; ++i)
		Idle->m_FrameData.push_back(glm::vec2( (m_v2FrameDimensionsNorm.x * 8) + (m_v2FrameDimensionsNorm.x * i), 0.0f));

	m_Animations.push_back(*Idle);


	delete Jump;
	delete Run;
	delete Idle;
	//Animation Warp;
	//m_Animations.push_back(Warp);

}

Player::~Player()
{

}

void Player::Draw()
{
	Sprite::Draw();
}

void Player::Input() 
{
	m_v3Speed = glm::vec3(0.0f, 0.0f, 0.0f);
	//this->Play(m_Animations[0]);

	//if (GLFW_PRESS == glfwGetKey(m_oGameWindow, GLFW_KEY_W))
	//{	
		this->Play(m_Animations[0]);
		m_v3Speed.y -= 2.0f;// * g_fDeltaTime * 60.0f ;
	//}
		
    if (GLFW_PRESS == glfwGetKey(Window::GetInstance().GetContext(), GLFW_KEY_A))
	{
		this->Play(m_Animations[1]);
        m_v3Speed.x -= 2.0f * g_fDeltaTime * 60.0f;
	}

    if (GLFW_PRESS == glfwGetKey(m_oGameWindow, GLFW_KEY_S))
	{
		m_v3Speed.y += 2.0f * g_fDeltaTime * 60.0f;
	}

    if (GLFW_PRESS == glfwGetKey(m_oGameWindow, GLFW_KEY_D))
	{
		this->Play(m_Animations[1]);
        m_v3Speed.x += 2.0f * g_fDeltaTime * 60.0f;
	}
	else if( m_v3Speed.x == 0.0f && m_v3Speed.y == 0.0f)
		this->Play(m_Animations[0]);

	m_v3Position += m_v3Speed;
}

bool Player::CheckBoxCollision(Sprite &a_roSprite) 
{

	//glm::vec3 v3Source = m_v3Position;
	//glm::vec3 v3Target = a_roSprite.m_v3Position;

	//return (abs(v3Source.x - v3Target.x) * 2) <  (m_v2Scale.x + a_roSprite.m_v2Scale.x)
	//	&& (abs(v3Source.y - v3Target.y) * 2) <  (m_v2Scale.y + a_roSprite.m_v2Scale.y);

	return 1;
}
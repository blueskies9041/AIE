#include "Particle.h"

CParticleSystem::CParticleSystem(long a_fNumParticles, long a_fNumForces, glm::vec3 a_v3Forces[],
								ParticleType a_ParticleType, glm::vec3 a_v3Velocity, 
								int a_iLifeTime, int a_iSize ,GLFWwindow* a_poWindow) 
{
	m_oGameWindow = a_poWindow;
	m_v3Velocity = a_v3Velocity;
	m_v3TotalForce = glm::vec3(0,.05,0);
	m_iSize = a_iSize;
	m_fNumParticles = a_fNumParticles;
	m_iLifeTime = a_iLifeTime;
	m_oEmitter = CSprite("resources/textures/test.bmp", m_iSize, m_iSize, 512, 368, glm::vec4(0,0,1,1), m_oGameWindow);
	m_ParticleType = a_ParticleType;
	InitParticles();
}

CParticleSystem::~CParticleSystem() {
<<<<<<< HEAD
	delete m_aParticles;
=======

>>>>>>> 06afab9635102afa2ff53f180455ef53524a405e
}

void CParticleSystem::InitParticles() {

	m_aParticles = new SParticle[m_fNumParticles];
<<<<<<< HEAD
	  
	for(int i = 0; i < m_fNumParticles; ++i) {

		m_aParticles[i].m_fAge = 0.0f;
		m_aParticles[i].m_fLifeTime = RandRange( 0 , 3);
=======

	for(int i = 0; i < m_fNumParticles; ++i) {

		m_aParticles[i].m_fAge = 0.0f;
		m_aParticles[i].m_fLifeTime = RandRange( m_iLifeTime + 120, 130);
>>>>>>> 06afab9635102afa2ff53f180455ef53524a405e

		m_aParticles[i].m_poSprite = CSprite("resources/textures/particle.bmp",
						12,
						12,
						RandRange( m_oEmitter.m_v3Position.x, m_oEmitter.m_v3Position.x + m_oEmitter.m_iHeight),
						RandRange( m_oEmitter.m_v3Position.y, m_oEmitter.m_v3Position.y - m_oEmitter.m_iWidth),
						glm::vec4(0,1,0,1),
						m_oGameWindow);

		m_aParticles[i].m_poSprite.m_v3Speed.x = RandRange(-2, 2);
		m_aParticles[i].m_poSprite.m_v3Speed.y = RandRange(-2, 2);
	
	}

}

void CParticleSystem::ModifyForce(long a_fNumForces, glm::vec3 a_av3Forces[]) {

	for(int i = 0; i < a_fNumForces; ++i) {

		m_v3TotalForce.x += a_av3Forces[i].x;
		m_v3TotalForce.y -= a_av3Forces[i].y;

	}
}

void CParticleSystem::Update() {

	for(int i = 0 ; i < m_fNumParticles; ++i) {

		m_aParticles[i].m_poSprite.Input();
		m_aParticles[i].m_poSprite.Draw();

		if(m_aParticles[i].m_fAge >= 0) {
			m_aParticles[i].m_poSprite.m_v3Speed.x += m_v3TotalForce.x;
			m_aParticles[i].m_poSprite.m_v3Speed.y += m_v3TotalForce.y;
			m_aParticles[i].m_poSprite.Draw();
			m_aParticles[i].m_fAge += 1.0f;
		}
	}


}


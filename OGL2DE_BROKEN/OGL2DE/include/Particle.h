#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Misc.h"
#include "Sprite.h"
#include <vector>

enum ParticleType {
	Create,
	Update
};

struct SParticle {
	
	CSprite m_poSprite;
    float       m_fAge;
    float       m_fLifeTime;
 
};

typedef std::vector<SParticle> ParticleBuffer;

class CParticleSystem {

protected:

	GLFWwindow* m_oGameWindow;
	CSprite m_oEmitter;
	SParticle * m_aParticles;
	long m_fNumParticles;
	glm::vec3 m_v3Velocity;
	glm::vec3 m_v3TotalForce;
	int m_iLifeTime;
	int m_iSize;
	ParticleType m_ParticleType;

public:

	CParticleSystem(long a_fNumParticles, long a_fNumForces, glm::vec3 a_v3Forces[],
					ParticleType a_ParticleType, glm::vec3 a_v3Velocity, 
					int a_iLifeTime, int a_iSize ,GLFWwindow* a_poWindow);
	~CParticleSystem();
	void InitParticles();
	void ModifyForce(long a_fNumForces, glm::vec3 a_av3Forces[]);
	void Update();

};

#endif
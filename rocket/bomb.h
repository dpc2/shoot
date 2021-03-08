/*
 *
 *
 */

#ifndef __EXPLOSION_H_INCLUDED__
#define __EXPLOSION_H_INCLUDED__

#include "particle.h"
#include "h.h"

const Vector PARTICLE_VELOCITY(0.0f, 2.0f, 0.0f);
const Vector VELOCITY_VARIATION(4.0f, 4.0f, 4.0f);
const Vector PARTICLE_ACCELERATION(0.0f, -5.0f, 0.0f);
const float PARTICLE_SIZE = 5.0f;
const float SIZE_VARIATION = 2.0f;



class Bomb : public Particle
{
public:
	Bomb(int maxParticles, Vector origin, float spread, GLuint texture);
	void Update(float elapsedTime);
	void Render();
	bool IsDead()
	{
		return m_numParticles <= 0;
	}

protected:
	void InitializeParticle(int index);
	float m_spread;
	GLuint m_texture;
};

#endif // __EXPLOSION_H_INCLUDED__

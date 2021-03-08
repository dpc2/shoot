/*
 *
 */

#include "particle.h"

Particle::Particle(int maxParticles, Vector origin)
{
	m_maxParticles = maxParticles;
	m_origin = origin;
	m_particleList = nullptr;
}
int Particle::Emit(int numParticles)
{
	while(numParticles && m_numParticles < m_maxParticles)
	{
		InitializeParticle(m_numParticles++);
		--numParticles;
	}
	return numParticles;
}
void Particle::InitializeSystem()
{
	if(m_particleList)
	{
		delete[] m_particleList;
		m_particleList = nullptr;
	}
	m_particleList = new particle_t[m_maxParticles];
	m_numParticles = 0;
	m_accumulatedTime = 0.0f;
}
void Particle::KillSystem()
{
	if(m_particleList)
	{
		delete[] m_particleList;
		m_particleList = nullptr;
	}
	m_numParticles = 0;
}


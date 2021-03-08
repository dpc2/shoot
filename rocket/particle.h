/*
 *
 */

#ifndef __PARTICLES_H_INCLUDED__
#define __PARTICLES_H_INCLUDED__

#include "vector.h"

struct particle_t
{
	Vector m_pos;           // current position of the particle
	Vector m_prevPos;        // last position of the particle
	Vector m_velocity;        // direction and speed
	Vector m_acceleration;        // acceleration

	float m_energy;           // determines how long the particle is alive

	float m_size;             // size of particle
	float m_sizeDelta;        // amount to change the size over time

	float m_weight;           // determines how gravity affects the particle
	float m_weightDelta;        // change over time

	float m_color[4];         // current color of the particle
	float m_colorDelta[4];        // how the color changes with time
};

class Particle
{
public:
	Particle(int maxParticles, Vector origin);
	virtual ~Particle()
	{
	}
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
	virtual int Emit(int numParticles);
	virtual void InitializeSystem();
	virtual void KillSystem();

protected:
	virtual void InitializeParticle(int index) = 0;
	particle_t *m_particleList;        // particles for this emitter
	int m_maxParticles;        // maximum number of particles in total
	int m_numParticles;        // indicies of all free particles
	Vector m_origin;           // center of the particle system

	float m_accumulatedTime;        // used to track how long since the last particle was emitted
	Vector m_force;            // force (gravity, wind, etc.) acting on the particle system
};

#endif // __PARTICLES_H_INCLUDED__

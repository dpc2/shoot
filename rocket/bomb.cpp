/*
 *
 *
 */

#include "bomb.h"

static float FRAND()		// returns a number ranging from -1.0 to 1.0
{
	return ((float) rand() - (float) rand()) / RAND_MAX;
}

Bomb::Bomb(int numParticles, Vector origin, float spread, GLuint texture)
		: Particle(numParticles, origin)
{
	m_texture = texture;
	m_spread = spread;
	srand(time(0));
	Particle::InitializeSystem();
	Emit(numParticles);
}

void Bomb::InitializeParticle(int index)
{
	// start the particle at the sky at a random location in the emission zone
	m_particleList[index].m_pos.x = m_origin.x + FRAND() * m_spread;
	m_particleList[index].m_pos.y = m_origin.y + FRAND() * m_spread;
	m_particleList[index].m_pos.z = m_origin.z + FRAND() * m_spread;

	// set the size of the particle
	m_particleList[index].m_size = PARTICLE_SIZE + FRAND() * SIZE_VARIATION;

	// give the particle a random velocity
	m_particleList[index].m_velocity.x = PARTICLE_VELOCITY.x + FRAND() * VELOCITY_VARIATION.x;
	m_particleList[index].m_velocity.y = PARTICLE_VELOCITY.y + FRAND() * VELOCITY_VARIATION.y;
	m_particleList[index].m_velocity.z = PARTICLE_VELOCITY.z + FRAND() * VELOCITY_VARIATION.z;

	m_particleList[index].m_acceleration = PARTICLE_ACCELERATION;

	m_particleList[index].m_color[0] = 1.0;
	m_particleList[index].m_color[1] = 0.5 + FRAND() * 0.5;
	m_particleList[index].m_color[2] = 0.0;
	m_particleList[index].m_color[3] = 1.0;

	m_particleList[index].m_energy = 1.5 + FRAND() / 2.0;

	m_particleList[index].m_colorDelta[0] = 0.0;
	m_particleList[index].m_colorDelta[1] = -(m_particleList[index].m_color[1] / 2.0) / m_particleList[index].m_energy;
	m_particleList[index].m_colorDelta[2] = 0.0;
	m_particleList[index].m_colorDelta[3] = -1.0 / m_particleList[index].m_energy;

	m_particleList[index].m_sizeDelta = -m_particleList[index].m_size / m_particleList[index].m_energy;

}        // end Bomb::InitializeParticle

/*****************************************************************************
 Bomb::Update

 Update the existing particles, killing them and creating new ones as needed
 *****************************************************************************/
void Bomb::Update(float elapsedTime)
{
	for(int i = 0; i < m_numParticles;)
	{
		// update the particle's position based on the elapsed time and velocity
		m_particleList[i].m_pos = m_particleList[i].m_pos + m_particleList[i].m_velocity * elapsedTime;
		m_particleList[i].m_velocity = m_particleList[i].m_velocity + m_particleList[i].m_acceleration * elapsedTime;

		m_particleList[i].m_energy -= elapsedTime;
		m_particleList[i].m_size += m_particleList[i].m_sizeDelta * elapsedTime;

		m_particleList[i].m_color[3] += m_particleList[i].m_colorDelta[3] * elapsedTime;
		m_particleList[i].m_color[1] += m_particleList[i].m_colorDelta[1] * elapsedTime;

		// if the particle has hit the ground plane, kill it
		if(m_particleList[i].m_energy <= 0.0)
		{
			// move the last particle to the current positon, and decrease the count
			m_particleList[i] = m_particleList[--m_numParticles];
		}
		else
		{
			++i;
		}
	}
}

/*****************************************************************************
 Bomb::Render()

 Draw the snowflake particles as textured quads
 *****************************************************************************/
void Bomb::Render()
{
	float viewMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);

	Vector right(viewMatrix[0], viewMatrix[4], viewMatrix[8]);
	Vector up(viewMatrix[1], viewMatrix[5], viewMatrix[9]);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	GLfloat size;
	Vector pos;
	Vector v;

	glBegin(GL_QUADS);
	for(int i = 0; i < m_numParticles; ++i)
	{
		size = m_particleList[i].m_size / 2;
		pos = m_particleList[i].m_pos;
		glColor4fv(m_particleList[i].m_color);
		glTexCoord2f(0.0, 0.0);

		v = Vector(pos + (right + up) * -size);
		glVertex3f(v.x, v.y, v.z);

		glTexCoord2f(1.0, 0.0);
		v = Vector(pos + (right - up) * size);
		glVertex3f(v.x, v.y, v.z);

		glTexCoord2f(1.0, 1.0);
		v = Vector(pos + (right + up) * size);
		glVertex3f(v.x, v.y, v.z);

		glTexCoord2f(0.0, 1.0);
		v = Vector(pos + (up - right) * size);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}        // end Bomb::Update


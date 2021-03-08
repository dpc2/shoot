/*
 Author: Kevin Hawkins
 Date: 4/2/2001
 */

#ifndef __GUI_H
#define __GUI_H

#include "font.h"
#include "h.h"
#include "texture.h"

class CGUI
{
private:
	int ms_left;
	int enemiesLeft;

	CFont *font;
	CFont *crosshair;
	CFont *endText;

public:
	CGUI();
	~CGUI();

	void set_seconds_left(int timeLeft);
	void SetEnemiesLeft(int eLeft);
	void Draw();
	void Animate(float deltaTime);

	void DrawWinner();
	void DrawLoser();
};

#endif

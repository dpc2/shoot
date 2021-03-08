/*
 *
 */

#include "gui.h"

CGUI::CGUI()
{
	ms_left = 0;
	font = new CFont((char*)"Arial", 16);
	crosshair = new CFont((char*)"Courier New", 28);
	endText = new CFont((char*)"Arial", 40);
}
CGUI::~CGUI()
{
	font->ClearFont();
	crosshair->ClearFont();
	endText->ClearFont();
	delete font;
	delete crosshair;
	delete endText;
}
void CGUI::set_seconds_left(int timeLeft)
{
	// timeLeft is in seconds
	ms_left = timeLeft;
}
void CGUI::SetEnemiesLeft(int eLeft)
{
	enemiesLeft = eLeft;
}
void CGUI::DrawWinner()
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	endText->SetPos3D(-0.25, 0.15, -0.1);
	endText->SetRGBA(0.3, 1.0, 0.3, 0.8);
	endText->Print("YOU WIN!");

	endText->SetPos3D(-0.5, -0.2, -0.1);
	endText->SetRGBA(1.0, 1.0, 1.0, 0.8);
	endText->Print("Press the ESC key to exit");

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void CGUI::DrawLoser()
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	endText->SetPos3D(-0.25, 0.15, -0.1);
	endText->SetRGBA(1.0, 0.3, 0.3, 0.8);
	endText->Print("YOU LOSE!");

	endText->SetPos3D(-0.5, -0.2, -0.1);
	endText->SetRGBA(1.0, 1.0, 1.0, 0.8);
	endText->Print("Press the ESC key to exit");

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void CGUI::Draw()
{
	glDisable(GL_TEXTURE_2D);
	font->SetPos3D(2.5, 2.9, -5.0);
	font->SetRGB(0.2, 0.0, 1.0);

	if(ms_left < 10 * 1000)
	{
		font->Print("Time: %dms", ms_left);
	}

	font->SetPos3D(2.5, 2.7, -5.0);
	font->Print("Enemies: %d", enemiesLeft);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	crosshair->SetRGBA(1.0, 0.1, 0.1, 0.7);
	crosshair->SetPos3D(-0.03, -0.03, -5.0);
	crosshair->Print("+");

	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}


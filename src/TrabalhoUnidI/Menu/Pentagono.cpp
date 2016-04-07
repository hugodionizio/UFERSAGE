/*
 * Pentagono.cpp
 *
 *  Created on: 17/03/2016
 *      Author: hugo
 */

#include "Menu.h"

// Função que desenha um quadrado
void DesenhaPentagonoQuestaoMenu(void) {
	glBegin (GL_POLYGON);
	glVertex2f(-14, -20.0);
	glVertex2f(-20, 6);
	glVertex2f(0.0, 20);
	glVertex2f(20, 6);
	glVertex2f(14, -20);
	glEnd();
}

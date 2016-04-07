/*
 * Quadrado.cpp
 *
 *  Created on: 17/03/2016
 *      Author: hugo
 */

#include "Menu.h"

// Função que desenha um quadrado
void DesenhaQuadradoQuestaoMenu(void) {
	glBegin (GL_QUADS);
	glVertex2f(-25.0f, -25.0f);
	glVertex2f(-25.0f, 25.0f);
	glVertex2f(25.0f, 25.0f);
	glVertex2f(25.0f, -25.0f);
	glEnd();
}

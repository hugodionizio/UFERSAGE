/*
 * Hexagono.cpp
 *
 *  Created on: 17/03/2016
 *      Author: hugo
 */

#include "Menu.h"

// Função que desenha um quadrado
void DesenhaHexagonoQuestaoMenu(void) {
	glBegin (GL_POLYGON);
	glVertex2f(-20, -13.0);
	glVertex2f(-20, 13);
	glVertex2f(0.0, 27);
	glVertex2f(20, 13);
	glVertex2f(20, -13.0);
	glVertex2f(0.0, -27.0);
	glEnd();
}

/*
 * Triangulo.cpp
 *
 *  Created on: 17/03/2016
 *      Author: hugo
 */

#include "Menu.h"

// Função que desenha um triângulo
void DesenhaTrianguloQuestaoMenu(void) {
	glBegin(GL_TRIANGLES);
	glVertex2f(-25.0f, -25.0f);
	glVertex2f(0.0f, 25.0f);
	glVertex2f(25.0f, -25.0f);
	glEnd();
}

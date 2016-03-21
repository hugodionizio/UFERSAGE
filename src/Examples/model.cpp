/*
 * model.cpp
 *
 *  Created on: 21/03/2016
 *      Author: hugo
 */

#include "whateverYouNeed.h"
#include <iostream>

void draw_triangle() {
	std::cout << "Model..." << std::endl;
}

int mainModel(int argc, char **argv) {
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	draw_triangle(); /* solid lines */

	glEnable(GL_LINE_STIPPLE); /* dashed lines */
	glLineStipple(1, 0xF0F0);
	glLoadIdentity();
	glTranslatef(-20.0, 0.0, 0.0);
	draw_triangle();

	glLineStipple(1, 0xF00F); /*long dashed lines */
	glLoadIdentity();
	glScalef(1.5, 0.5, 1.0);
	draw_triangle();

	glLineStipple(1, 0x8888); /* dotted lines */
	glLoadIdentity();
	glRotatef(90.0, 0.0, 0.0, 1.0);
	draw_triangle();
	glDisable(GL_LINE_STIPPLE);

	return 0;
}

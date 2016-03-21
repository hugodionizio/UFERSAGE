/*
 * varray.cpp
 *
 *  Created on: 20/03/2016
 *      Author: hugo
 */

#include "whateverYouNeed.h"

int mainVarray(int argc, char **argv) {
	static GLint vertices[] = { 25, 25, 100, 325, 175, 25, 175, 325, 250, 25, 325,
			325 };

	static GLfloat colors[] = { 1.0, 0.2, 0.2, 0.2, 0.2, 1.0, 0.8, 1.0, 0.2, 0.75,
			0.75, 0.75, 0.35, 0.35, 0.35, 0.5, 0.5, 0.5 };

	glEnableClientState (GL_COLOR_ARRAY);
	glEnableClientState (GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(2, GL_INT, 0, vertices);

	return 0;
}

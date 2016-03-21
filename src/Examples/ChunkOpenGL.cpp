/*
 * ChunkOpenGL.cpp
 *
 *  Created on: 20/03/2016
 *      Author: hugo
 */

#include "whateverYouNeed.h"

void InitializeAWindowPlease() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 350);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Chunk of OpenGL Code");
}

void UpdateTheWindowAndCheckForEvents() {

}

int mainChunkOpenGL(int argc, char** argv) {
	glutInit(&argc, argv);
	InitializeAWindowPlease();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glBegin(GL_POLYGON);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);
	glEnd();

	glFlush();
	UpdateTheWindowAndCheckForEvents();

	return 0;
}


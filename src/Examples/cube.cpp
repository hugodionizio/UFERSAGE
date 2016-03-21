/*
 * cube.cpp
 *
 *  Created on: 21/03/2016
 *      Author: hugo
 */

#include "whateverYouNeed.h"

void initCube(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}

void displayCube(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();	/* clear the matrix */
		/* viewing transformation */
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(1.0, 2.0, 1.0);	/* modeling transformation */
	glutWireCube(1.0);
	glFlush();
}

void reshapeCube(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode (GL_MODELVIEW);
}

int mainCube(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initCube();
	glutDisplayFunc(displayCube);
	glutReshapeFunc(reshapeCube);
	glutMainLoop();

	return 0;
}

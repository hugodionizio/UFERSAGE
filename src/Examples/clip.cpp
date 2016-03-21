/*
 * clip.cpp
 *
 *  Created on: 21/03/2016
 *      Author: hugo
 */

#include "whateverYouNeed.h"

void initClip(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void displayClip(void) {
	GLdouble eqn[4] = { 0.0, 1.0, 0.0, 0.0 };
	GLdouble eqn2[4] = { 1.0, 0.0, 0.0, 0.0 };

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);

	/*	 clip lower half -- y < 0	*/
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	/*	clip left half -- x < 0	*/
	glClipPlane(GL_CLIP_PLANE1, eqn2);
	glEnable(GL_CLIP_PLANE1);

	glRotatef(90.0, 1.0, 0.0, 0.0);
	glutWireSphere(1.0, 20, 16);
	glPopMatrix();
	glFlush();
}

void reshapeClip(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

int mainClip(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initClip();
	glutDisplayFunc(displayClip);
	glutReshapeFunc(reshapeClip);
	glutMainLoop();

	return 0;
}


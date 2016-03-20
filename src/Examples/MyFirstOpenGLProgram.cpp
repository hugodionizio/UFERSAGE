/*
 * MyFirstOpenGLProgram.cpp
 *
 *  Created on: 03/02/2016
 *      Author: hugo
 */

#ifdef WIN
# include <windows.h>  // For MS Windows
# include <gl\gl.h>
# include <gl\glu.h>
# include <gl\glut.h>
# include <gl\glui.h>
# else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>
#endif

void init01(void);
void display02(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glBegin (GL_TRIANGLES);
	glVertex3f(0.0f, 1.0f, -10.0f);
	glVertex3f(-1.0f, -1.0f, -10.0f);
	glVertex3f(1.0f, -1.0f, -10.0f);
	glEnd();
	glutSwapBuffers();
}

int MyFirstOpenGLProgam(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("My First Glut/OpenGL Program");
	init01();
	glutDisplayFunc(display02);
	glutMainLoop();
	return 0;
}

void init01(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat) 250 / (GLfloat) 250, 0.1f, 100.0f);
}

/*
 * Transformacoes.cpp
 *
 *  Created on: 17/03/2016
 *      Author: hugo
 */

/*
 *  3. Implementar uma aplicação em que o usuário
 *  pode aplicar escala, transladar e rotacionar um
 *  objeto utilizando o teclado.
 */

#include <GL/glew.h>
#include <GL/freeglut_std.h>
#include <GL/glu.h>

// Variáveis globais
static int spin = 0;
GLfloat win_questao_transformacoes, rQuestaoTransformacoes,
		gQuestaoTransformacoes, bQuestaoTransformacoes;
GLint view_w_questao_transformacoes, view_h_questao_transformacoes,
		primitivaQuestaoTransformacoes;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void initTransformacoes(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

/*  Here is where the light position is reset after the modeling
 *  transformation (glRotated) is called.  This places the
 *  light at a new position in world coordinates.  The cube
 *  represents the position of the light.
 */
void displayTransformacoes(void) {
	GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glRotated((GLdouble) spin, 1.0, 0.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	glutWireCube(0.1);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glutSolidTorus(0.275, 0.85, 8, 15);
	glPopMatrix();
	glFlush();
}

void reshapeTransformacoes(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouseTransformacoes(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			spin = (spin + 30) % 360;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}

void keyboardTransformacoes(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

// Função callback chamada para gerenciar eventos do teclado
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciaisQuestaoTransformacoes(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		spin = (spin + 30) % 360;
	}
	if (key == GLUT_KEY_DOWN) {
		spin = (spin - 30) % 360;
	}
	glutPostRedisplay();
}

int mainTransformacoes(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initTransformacoes();
	glutDisplayFunc(displayTransformacoes);
	glutReshapeFunc(reshapeTransformacoes);
	glutMouseFunc(mouseTransformacoes);
	glutKeyboardFunc(keyboardTransformacoes);
	glutSpecialFunc(TeclasEspeciaisQuestaoTransformacoes);
	glutMainLoop();
	return 0;
}

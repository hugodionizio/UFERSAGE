#include <GL/freeglut.h>
#include <GL/gl.h>

#include <ctime>
#include <iostream>
using namespace std;

void displayExemploCallbacks() {

	// Geração de uma cor aleatória
	float r = rand() / (RAND_MAX + 0.0);
	float g = rand() / (RAND_MAX + 0.0);
	float b = rand() / (RAND_MAX + 0.0);
	glClear (GL_COLOR_BUFFER_BIT);

	// Atribuição ao fundo como negativo da cor aleatória
	glClearColor(1 - r, 1 - g, 1 - b, 0.0);

	glColor3f(r, g, b); // Pinta o objeto com a cor gerada
	glutWireTeapot(0.3);
//	glutSolidTeapot(0.3);
//	glutSolidSphere(0.3, 30, 30);
//	glutWireSphere(0.3, 30,30);

	glFlush();
}

// Ref: https://www.opengl.org/resources/libraries/glut/spec3/node49.html
void keyboardExemploCallbacks(unsigned char k, int x, int y) {
	cout << "A tecla apertada foi " << k << endl;
}

//Ref: http://www.opengl.org/documentation/specs/glut/spec3/node50.html
void mouseExemploCallbacks(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		cout << "Clicado para baixo " << endl;
		glutPostRedisplay();
	}
	if (state == GLUT_UP)
		cout << "Clicado para cima " << endl;

	cout << "coordenadas = (" << x << "," << y << ")" << endl;
}

int mainExemploCallbacks(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL - First window demo");

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	srand(time(NULL));

	glutDisplayFunc(displayExemploCallbacks);
	glutKeyboardFunc(keyboardExemploCallbacks);
	glutMouseFunc(mouseExemploCallbacks);
	glutMainLoop();
	return 0;
}

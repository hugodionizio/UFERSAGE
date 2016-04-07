// TeaPot3D.c - Isabel H. Manssour
// Um programa OpenGL que exemplifica a visualiza��o 
// de objetos 3D.
// Este c�digo est� baseado nos exemplos dispon�veis no livro 
// "OpenGL SuperBible", 2nd Edition, de Richard S. e Wright Jr.

#ifdef WINDOWS
# include <windows.h>
# include <gl/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

GLfloat angleTeaPot3D, fAspectTeaPot3D;

// Fun��o callback chamada para fazer o desenho
void DesenhaTeaPot3D(void) {
	glClear (GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 1.0f);

	// Desenha o teapot com a cor corrente (wire-frame)
	glutWireTeapot(50.0f);

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Inicializa par�metros de rendering
void InicializaTeaPot3D(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	angleTeaPot3D = 45;
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacaoTeaPot3D(void) {
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode (GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
	gluPerspective(angleTeaPot3D, fAspectTeaPot3D, 0.5, 500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode (GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
	gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanelaTeaPot3D(GLsizei w, GLsizei h) {
	// Para previnir uma divis�o por zero
	if (h == 0)
		h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspectTeaPot3D = (GLfloat) w / (GLfloat) h;

	EspecificaParametrosVisualizacaoTeaPot3D();
}

// Fun��o callback chamada para gerenciar eventos do mouse
void GerenciaMouseTeaPot3D(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angleTeaPot3D >= 10)
				angleTeaPot3D -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angleTeaPot3D <= 130)
				angleTeaPot3D += 5;
		}
	EspecificaParametrosVisualizacaoTeaPot3D();
	glutPostRedisplay();
}

// Programa Principal
int mainTeaPot3D(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(350, 300);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(DesenhaTeaPot3D);
	glutReshapeFunc(AlteraTamanhoJanelaTeaPot3D);
	glutMouseFunc(GerenciaMouseTeaPot3D);
	InicializaTeaPot3D();
	glutMainLoop();
}

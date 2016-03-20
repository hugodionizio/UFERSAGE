// Quadrado.cpp - Isabel H. Manssour
// Um programa OpenGL simples que desenha um 
// quadrado em  uma janela GLUT.
// Este c�digo est� baseado no GLRect.c, exemplo 
// dispon�vel no livro "OpenGL SuperBible", 
// 2nd Edition, de Richard S. e Wright Jr.

#ifdef WINDOWS
# include <windows.h>
# include <gl/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

// Fun��o callback chamada para fazer o desenho
void DesenhaQuadrado(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualiza��o com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT);

	// Especifica que a cor corrente � vermelha
	//         R     G     B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Desenha um quadrado preenchido com a cor corrente
	glBegin(GL_QUADS);
		glVertex2i(100, 150);
		glVertex2i(100, 100);
		// Especifica que a cor corrente � azul
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(150, 100);
		glVertex2i(150, 150);
	glEnd();

	// Executa os comandos OpenGL
	glFlush();
}

// Inicializa par�metros de rendering
void InicializaQuadrado(void) {
	// Define a cor de fundo da janela de visualiza��o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanelaExemplo(GLsizei w, GLsizei h) {
	// Evita a divisao por zero
	if (h == 0)
		h = 1;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (left, right, bottom, top)
	if (w <= h)
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f * h / w);
	else
		gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f);
}

// Programa Principal 
int mainQuadrado(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 350);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Quadrado");
	glutDisplayFunc(DesenhaQuadrado);
	glutReshapeFunc(AlteraTamanhoJanelaExemplo);
	InicializaQuadrado();
	glutMainLoop();
}

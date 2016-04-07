// PrimeiroPrograma.cpp - Isabel H. Manssour
// Um programa OpenGL simples que abre uma janela GLUT
// Este código está baseado no Simple.c, exemplo 
// disponível no livro "OpenGL SuperBible", 
// 2nd Edition, de Richard S. e Wright Jr.

#ifdef WINDOWS
# include <windows.h>
# include <gl/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

// Função callback chamada para fazer o desenho
void DesenhaPrimeiroPrograma(void) {
	//Limpa a janela de visualização com a cor de fundo especificada 
	glClear (GL_COLOR_BUFFER_BIT);

	//Executa os comandos OpenGL 
	glFlush();
}

// Inicializa parâmetros de rendering
void InicializaPrimeiroPrograma(void) {
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Programa Principal 
int mainPrimeiroPrograma(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Primeiro Programa");
	glutDisplayFunc(DesenhaPrimeiroPrograma);
	InicializaPrimeiroPrograma();
	glutMainLoop();
}

/*
 * LinhaBresenham.cpp
 *
 *  Created on: 16/03/2016
 *      Author: hugo
 */

/*
 * a) Rasterização de linhas dados os pontos inicial e final
 *	- Algoritmo de Bresenham
 */

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define LARGURA_JANELA 250
#define ALTURA_JANELA 250
#define XMAXIMO (LARGURA_JANELA/2)
#define YMAXIMO	(ALTURA_JANELA/2)

using namespace std;

void displayLinhaBresenham(void) {
	float x0 = 1, y0 = 1, x1 = 120, y1 = 50, x, y, m;

	x0 = x0 / XMAXIMO;
	y0 = y0 / YMAXIMO;
	x1 = x1 / XMAXIMO;
	y1 = y1 / YMAXIMO;
	m = (y1 - y0) / (x1 - x0);

	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * a) Rasterização de linhas dados os pontos inicial e final
	 *	- Algoritmo de Bresenham
	 */
	cout << "Algoritmo do Ponto Médio ou Midpoint de Bresenham da Reta (azul):"
			<< endl;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 1.0);
	// 1. Receba os dois vértices do segmento de reta \
			e armazene o vértice mais à esquerda como sendo \
			o ponto (x0, y0)
	// 3. Calcule as constantes delta(x), delta(y), \
			2*delta(y) - 2*delta(x), e obtenha o parâmetro \
			de decisão inicial p0 = 2*delta(y) - 2*delta(x)
	float dx = x1 - x0;
	float dy = y1 - y0;
	float d = 2 * dy - dx;
	float incrE = 2 * dy;
	float incrNE = 2 * (dy - dx);
	x = x0;
	y = y0;

	// 2. Pinta pixel (x0, y0)
	glVertex3f(x, y, 0.0);
	// cout << x << ", " << y << endl;

	// 5. Repita o passo 4*delta(x) vezes
	while (x < x1) {
		// 4. Para cada xk ao longo da reta, começando com \
					k = 0, faça o seguinte teste: \
					- Se pk < 0, Pinta pixel(xk+1, yk) e \
					p(k+1) = pk + 2*delta(y) \
					- Caso contrário, Pinta pixel(xk + 1, yk + 1) e \
					p(k+1) = 2*delta(y)- 2*delta(x)
		if (d <= 0) {
			d += incrE;
			x += (0.4f / XMAXIMO);
		} else {
			d += incrNE;
			x += (0.4f / XMAXIMO);
			y += (0.4f / YMAXIMO);
		}
		glVertex3f(x, y, 0.0);
		// cout << x << ", " << y << endl;
	}
	glEnd();
	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void initLinhaBresenham(void) {
	/* selecionar cor de limpeza (fundo)
	 *
	 */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* Inicializar valores de visualização
	 *
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

/*
 * Declarar tamanho de janela inicial, posição, e modo de tela
 * (buffer simples e RGBA). Abrir janela com "Linha de Bresenham"
 * nesta barra de título. Chamar rotinas de inicialização.
 * Registrar função de chamada de retorno para gráficos na tela.
 * Entrar como laço principal e eventos d processo.
 */
int mainLinhaBresenham(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Linha de Bresenham");
	initLinhaBresenham();
	glutDisplayFunc(displayLinhaBresenham);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}

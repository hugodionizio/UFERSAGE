/*
 * CirculoBresenham.cpp
 *
 *  Created on: 16/03/2016
 *      Author: hugo
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include <iostream>
using namespace std;

#define LARGURA_JANELA 250
#define ALTURA_JANELA 250
#define XMAXIMO (LARGURA_JANELA/2)
#define YMAXIMO	(ALTURA_JANELA/2)

void PontosCirculo(float x, float y, float z) {
	glVertex3f(x, y, z);
	glVertex3f(y, x, z);
	glVertex3f(y, -x, z);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);
	glVertex3f(-y, -x, z);
	glVertex3f(-y, x, z);
	glVertex3f(-x, y, z);
}

void displayCirculoBresenham(void) {
	float i = 0;
	float R = 1;
	/*
	 * Limpar todos os pixels
	 */
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	 * b) Rasterização de cículos, dado o raio de entrada.
	 * - Utilizando o algoritmo de Bresenham.
	 */
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 1.0, 0.0);
	// 1. Receba o valor do raio r e as coordenadas do centro (xc, yc)\
		e obtenha o primeiro ponto de um círculo centrado na origem: \
		(x0, y0) = (0, r)
	// 2. Calcule o valor do parâmetro de decisão inicial: \
		p0 = (5/4) - r
	// 3. Para cada posição xk, começando com k = 0, faça: \
		* Se pk < 0, pinta pixel(x[k+1], y[k]) e \
			p[k+1] = p[k] = p[k] + 2x[k+1] + 1 \
		* Caso contrário, pinta pixel(x[k]+1, y[k]-1) e \
			p[k+1] = p[k] + 2x[k+1] + 1 - 2y[k+1] \
		* Onde 2x[k+1] = 2x[k] + 2 e 2y[k+1] = 2y[k] - 2
	// 4. Determine os 8 demais pontos de simetria
	// 5. Mova cada ponto calculado para caminho circular centrado \
		em (xc, yc): \
		x = x + xc; y = y + yc
	// 6. Repita os passos 3 ao 5 até x >= y
	float x = 0;
	float y = R;
	float d = 1 - R;
	float deltaE = 3.0/YMAXIMO;
	float deltaSE = -2 * R + 5.0/(100*XMAXIMO);
	PontosCirculo(x, y, 0);
	cout << x << ", " << y << endl;

	while (y >= x) {
		if (d <= 0) {	/* Selecione E */
			d += deltaE;
			deltaE += 2.0/(10*YMAXIMO);
			deltaSE += 2.0/(10*XMAXIMO);
		}
		else {
			d += deltaSE;	/* Selecione SE */
			deltaE += 2.0/(10*YMAXIMO);
			deltaSE += 4.0/(10*XMAXIMO);
			y-=1.0/(10*YMAXIMO);
		}
		x+=1.0/(10*XMAXIMO);
		PontosCirculo(x, y, 0);
		cout << x << ", " << y << endl;
	}
	glEnd();

	/*
	 * Sem pausa!
	 * Iniciar processo com rotinas OpenGL de buffer
	 */
	glutSwapBuffers();
}

void initCirculoBresenham(void) {
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
 * (buffer simples e RGBA). Abrir janela com "hello"
 * nesta barra de título. Chamar rotinas de inicialização.
 * Registrar função de chamada de retorno para gráficos na tela.
 * Entrar como laço principal e eventos d processo.
 */
int mainCirculoBresenham(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Midpoint Circle ou Círculo com Algoritmo de Bresenham");
	initCirculoBresenham();
	glutDisplayFunc(displayCirculoBresenham);
	glutMainLoop();
	return 0; /* ISO C requer "main" para retornar int */
}

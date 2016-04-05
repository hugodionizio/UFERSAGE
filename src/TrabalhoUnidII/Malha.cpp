/*
 * Malha.c
 *
 *  Created on: Mar 30, 2016
 *      Author: hugo
 */

#include <GL/glew.h>
#include <GL/glui.h>

#include <iostream>

using namespace std;

#include "../Examples/examples.h"

enum TrabalhoII {
	MALHA_PLY = NUM_EXAMPLES + 1, NUM_QUESTOES
};

struct Vertice {
	float x;
	float y;
	float z;
};

struct Face {
	Vertice v1;
	Vertice v2;
	Vertice v3;
};

struct Malha {
	Face *f;
};

void criarMalha(Malha *m, float v1x, float v1y, float v2x, float v2y, float v3x, float v3y) {
	// Ignorar eixo z
	m->f = new Face[1];
	m->f->v1.x = v1x;
	m->f->v1.y = v1y;

	m->f->v2.x = v2x;
	m->f->v2.y = v2y;

	m->f->v3.x = v3x;
	m->f->v3.y = v3y;

	cout << "Malha criada." << endl;
}

int mainMalha (int argc, char **argv) {
	// Malha 3D
	Malha m1;

	// Ler malha de um arquivo
	cout << "Lendo malha de arquivo .ply..." << endl;

	// Gravar/atualizar/substituir malha em um arquivo
	cout << "Gravando malha em arquivo .ply..." << endl;

	criarMalha(&m1, 0, 0, 0, 0, 0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 350);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Malha");
//	glutDisplayFunc(DesenhaQuadradoInterativo);
//	glutReshapeFunc(AlteraTamanhoJanela);
//	glutKeyboardFunc(alteraCorObjetoTeclado);
//	glutMouseFunc(testeBotaoMouse);
//	Inicializa();
	glutMainLoop();

	return (0);
}

/*
 * Malha.c
 *
 *  Created on: Mar 30, 2016
 *      Author: hugo
 */

#define ARQUIVO_TESTE "ant.ply"

#include <GL/glew.h>
#include <GL/glui.h>

// Diretivas
#include <fstream> // Para a classe de arquivos
#include <iostream>
#include <cstring>

using namespace std;

#include "TrabalhoUnidII.h"

/*	Create checkerboard texture	*/
#define	checkImageWidth 64
#define	checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

struct Vertice {
	float x;
	float y;
	float z;
}*vert;

struct Face {
	Vertice v1;
	Vertice v2;
	Vertice v3;

	int numVertices;
	int *v;
}*face;

struct Malha {
	int numPalavras;
	int numCaracteres;
	int numLinhas;
	int fim_cabecalho;
	int numVertices;
	int numFaces;
	Vertice *v;
	Face *f;
} malhaPly;

float x = 0.0, y = 0.0;

#ifdef LINUX
FGAPI int FGAPIENTRY Wind;
#endif

// Malha 3D
Malha m1;
Face f1;

void criarMalha(Malha *m, float v1x, float v1y, float v2x, float v2y, float v3x,
		float v3y) {
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

void makeMalhaImage(void) {
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte) c;
			checkImage[i][j][1] = (GLubyte) c;
			checkImage[i][j][2] = (GLubyte) c;
			checkImage[i][j][3] = (GLubyte) 255;
		}
	}
}

void inicializarMalha(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void desenharMalha(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity(); /* clear the matrix */
	/* viewing transformation */
	gluLookAt(1.0, -1.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(0.18, 0.18, 0.18); /* modeling transformation */

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < malhaPly.numFaces; ++i) {
		for (int j = 0; j < 3; ++j) {
//			desenhaCubo();
			glVertex3f(malhaPly.v[malhaPly.f[i].v[j]].x, malhaPly.v[malhaPly.f[i].v[j]].y, malhaPly.v[malhaPly.f[i].v[j]].z);
		}
	}
	glEnd();

	glFlush();
}

void redesenharMalha(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void tecladoMalha(unsigned char key, int x, int y) {
	ofstream fout("Malha.ply", ios::binary);

	float k = 0.01;

	switch (key) {
	case 'a':

		cout << x << endl;
		x = 1.0f;

		f1.v1.x = x;

		cout << "Incrementado malha em arquivo .ply..." << endl;
		fout.write(reinterpret_cast<char *>(&f1), sizeof(Face));

		cout << x << endl;
		cout << y << endl;
		cout << f1.v1.x << endl;
		cout << f1.v1.y << endl;
		cout << f1.v2.x << endl;
		cout << f1.v2.y << endl;
		cout << f1.v3.x << endl;
		cout << f1.v3.y << endl;

		cout << "Incrementado." << endl;

		break;
	case 'b':
		x = 0.0f;

		f1.v1.x = x;

		cout << "Decrementando malha em arquivo .ply..." << endl;
		fout.write(reinterpret_cast<char *>(&f1), sizeof(Face));

		cout << x << endl;
		cout << y << endl;
		cout << f1.v1.x << endl;
		cout << f1.v1.y << endl;
		cout << f1.v2.x << endl;
		cout << f1.v2.y << endl;
		cout << f1.v3.x << endl;
		cout << f1.v3.y << endl;

		cout << "Decrementado." << endl;

		break;
	case 27:
#ifdef LINUX
		glutDestroyWindow(Wind);
#endif
		exit(EXIT_SUCCESS);
		break;
	}
	glutPostRedisplay();
}

enum AtributoPly {
	NONE, VERTEX, FACE
};

enum VerticeCor {
	XCOOR = 1, YCOOR, ZCOOR
};

void lerArquivo(char *nomeArquivo) {
	const int MAX = 80;

	// Variáveis
	int comecouPalavra = 0, numPalavras = 0, numLinhas = 0, numCaracteres = 0;
	char buff[MAX];
	int fim_cabecalho = -1;
	int atributoPly = NONE;
	int numVertices = 0, numFaces = 0, numVertPorFace = 0;
	int verticeCoor = NONE, faceVertice = NONE;
	int linhaAtual;

	ifstream finPly(nomeArquivo); // Cria arquivo para leitura em modo texto

	// Seção de Comandos
	while (!finPly.eof()) { // Enquanto não terminou o arquivo
		finPly.getline(buff, MAX);
		char * pch;
		pch = strtok(buff, " ,\r\n");
		while (pch != NULL) {
			numPalavras++;
//			cout << pch << endl;
			if (strcmp(pch, "end_header") == 0) {
				fim_cabecalho = numLinhas;
				verticeCoor = XCOOR;

			} else if (strcmp(pch, "vertex") == 0) {
				atributoPly = VERTEX;
			} else if (strcmp(pch, "face") == 0) {
				atributoPly = FACE;
			} else if (atributoPly == VERTEX) {
				numVertices = atoi(pch);
				vert = new Vertice[numVertices];
				atributoPly = NONE;
			} else if (atributoPly == FACE) {
				numFaces = atoi(pch);
				atributoPly = NONE;
				face = new Face[numFaces];
			} else if (fim_cabecalho > 0 // Lista e grava vértices na lista de vértices
			&& numLinhas < numVertices + fim_cabecalho + 1) {
				if (strcmp(pch, "\r") != 0) {
					if (verticeCoor == XCOOR) {
						vert[numLinhas - fim_cabecalho - 1].x = atof(pch);
						if (numLinhas - fim_cabecalho < 10)
							cout << "P("
									<< vert[numLinhas - fim_cabecalho - 1].x;
						verticeCoor = YCOOR;
					} else if (verticeCoor == YCOOR) {
						vert[numLinhas - fim_cabecalho - 1].y = atof(pch);
						if (numLinhas - fim_cabecalho < 10)
							cout << ", "
									<< vert[numLinhas - fim_cabecalho - 1].y;
						verticeCoor = ZCOOR;
					} else if (verticeCoor == ZCOOR) {
						vert[numLinhas - fim_cabecalho - 1].z = atof(pch);
						if (numLinhas - fim_cabecalho < 10)
							cout << ", "
									<< vert[numLinhas - fim_cabecalho - 1].z
									<< ")" << endl;
						verticeCoor = XCOOR;
					}
				}
			} else if (fim_cabecalho > 0 // Lista e grava faces na lista de faces
			&& numLinhas < numFaces + numVertices + fim_cabecalho + 1) {
				if (strcmp(pch, "\r") != 0) {
					if (numLinhas == numVertices + fim_cabecalho + 1
							&& numVertPorFace == 0) {
						numVertPorFace = atoi(pch);
						for (int var = 0; var < numFaces; ++var) {
							face[var].v = new int[numVertPorFace];
						}
						faceVertice = 1;
					} else if (faceVertice <= numVertPorFace
							&& faceVertice > 0) {
						face[numLinhas - (numVertices + fim_cabecalho) - 1].numVertices =
								numVertPorFace;
						face[numLinhas - (numVertices + fim_cabecalho) - 1].v[faceVertice
								- 1] = atoi(pch);

						if (numLinhas - fim_cabecalho - numVertices <= 10) {
							if (linhaAtual != numLinhas) {
								cout << "F("
										<< numLinhas - fim_cabecalho
												- numVertices << ") = (";
								linhaAtual = numLinhas;
							}
							cout
									<< face[numLinhas
											- (numVertices + fim_cabecalho) - 1].v[faceVertice
											- 1];
							if (faceVertice + 1 <= numVertPorFace)
								cout << ", ";
							else
								cout << ")" << endl;
						}

						if (faceVertice + 1 <= numVertPorFace)
							faceVertice++;
						else
							faceVertice = 0;
					} else if (strcmp(pch, "\r") != 0)
						faceVertice++;
				}
			}
			numCaracteres += strlen(pch);
//			if (numLinhas < 10)
//				cout << "(" << strlen(pch) << " caracteres) " << pch << endl;
			pch = strtok(NULL, " ");
		}

		numLinhas++;
	}

	malhaPly.numLinhas = numLinhas;
	malhaPly.numCaracteres = numCaracteres;
	malhaPly.numPalavras = numPalavras;
	malhaPly.fim_cabecalho = fim_cabecalho;
	malhaPly.numVertices = numVertices;
	malhaPly.numFaces = numFaces;
	malhaPly.v = vert;
	malhaPly.f = face;

	cout << "Testando lista de vértices..." << endl;
	for (int var = 0; var < malhaPly.numVertices; ++var) {
		cout << "V(" << var << ") = (" << vert[var].x << ", " << vert[var].y
				<< ", " << vert[var].z << ")" << endl;
		if (var == 4)
			var = malhaPly.numVertices - 5;
	}

	cout << "Testando lista de faces..." << endl;
	for (int var = 0; var < malhaPly.numFaces; ++var) {
		cout << "F(" << var << ") = (" << face[var].v[0] << ", "
				<< face[var].v[1] << ", " << face[var].v[2] << ")" << endl;
		if (var == 4)
			var = malhaPly.numFaces - 5;
	}

	cout << "O número de palavras do arquivo é: " << malhaPly.numPalavras
			<< endl;
	cout << "O número de caracteres do arquivo é: " << malhaPly.numCaracteres
			<< endl;
	cout << "O número de linhas do arquivo é: " << malhaPly.numLinhas << endl;

	cout << "O fim do cabeçalho está na " << (malhaPly.fim_cabecalho + 1)
			<< "ª linha." << endl;
	cout << "O número de vértices do objeto é: " << malhaPly.numVertices
			<< endl;
	cout << "O número de faces do objeto é: " << malhaPly.numFaces << endl;

	cout << "O primeiro vértice da primeira face é: V1F1("
			<< malhaPly.v[malhaPly.f[0].v[0]].x << ", "
			<< malhaPly.v[malhaPly.f[0].v[0]].y << ", "
			<< malhaPly.v[malhaPly.f[0].v[0]].z << ")" << endl;

	cout << "O último vértice da primeira face é: VNF1("
			<< malhaPly.v[malhaPly.f[0].v[malhaPly.f->numVertices - 1]].x
			<< ", "
			<< malhaPly.v[malhaPly.f[0].v[malhaPly.f->numVertices - 1]].y
			<< ", "
			<< malhaPly.v[malhaPly.f[0].v[malhaPly.f->numVertices - 1]].z << ")"
			<< endl;

	cout << "O primeiro vértice da última face é: V1FN("
			<< malhaPly.v[malhaPly.f[malhaPly.numFaces - 1].v[0]].x << ", "
			<< malhaPly.v[malhaPly.f[malhaPly.numFaces - 1].v[0]].y << ", "
			<< malhaPly.v[malhaPly.f[malhaPly.numFaces - 1].v[0]].z << ")"
			<< endl;

	cout << "O último vértice da última face é: VNFN("
			<< malhaPly.v[malhaPly.f[malhaPly.numFaces - 1].v[malhaPly.f->numVertices
					- 1]].x << ", "
			<< malhaPly.v[malhaPly.f[malhaPly.numFaces - 1].v[malhaPly.f->numVertices
					- 1]].y << ", "
			<< malhaPly.v[malhaPly.f[malhaPly.numFaces - 1].v[malhaPly.f->numVertices
					- 1]].z << ")" << endl;

}

int mainMalha(int argc, char **argv) {
	char *nomeArquivo;
	if (argc > 2)
		nomeArquivo = argv[2];
	else
		nomeArquivo = (char *) ARQUIVO_TESTE;

	lerArquivo(nomeArquivo);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
#ifdef LINUX
	Wind = glutCreateWindow("Malha Ply");
#else
	glutCreateWindow("Malha Ply");
#endif
	inicializarMalha();
	glutDisplayFunc(desenharMalha);
	glutReshapeFunc(redesenharMalha);
//	glutKeyboardFunc(tecladoMalha);
	glutMainLoop();

	return 0;
}

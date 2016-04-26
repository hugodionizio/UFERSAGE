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
#include <cstdlib>
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

#ifdef __linux__
FGAPI int FGAPIENTRY Wind;
#endif

// Malha 3D
Malha m1;
Face f1;

GLfloat angleMalha, fAspectMalha;
GLdouble obsX = 0, obsY = 0, obsZ = 200;
static int spinMalha = 0;
float RMalha, GMalha, BMalha;

void criarMalha(Malha *m, float v1x, float v1y, float v2x, float v2y, float v3x,
		float v3y) {
	m->f->v = new int[3];
	vert = new Vertice[3];

	// Ignorar eixo z
	m->f = new Face[1];
	vert[0].x = v1x;
	vert[0].y = v1y;

	vert[1].x = v2x;
	vert[1].y = v2y;

	vert[2].x = v3x;
	vert[2].y = v3y;

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
	GLfloat luzDifusa[4] = { 0.7, 0.7, 0.7, 1.0 };		 // "cor"
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };		 // "brilho"
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLint especMaterial = 60;

	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Habilita o modelo de colorização de Gouraud
	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	angleMalha = 45;
}

void desenharMalha(void) {
	GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glRotated((GLdouble) spinMalha, 1.0, 0.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
//	glColor3f(1.0, 1.0, 1.0);

	//glLoadIdentity(); /* clear the matrix */
	/* viewing transformation */
	//gluLookAt(1.0, -1.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// ??
	//glScalef(0.18, 0.18, 0.18); /* modeling transformation */

	for (int i = 0; i < malhaPly.numFaces; ++i) {
		//glBegin(GL_LINE_LOOP);
		glBegin(GL_TRIANGLES);
//		glColor3f(1.0, 1.0, 1.0);
		for (int j = 0; j < 3; ++j) {
			glVertex3f(malhaPly.v[malhaPly.f[i].v[j]].x,
					malhaPly.v[malhaPly.f[i].v[j]].y,
					malhaPly.v[malhaPly.f[i].v[j]].z);
		}
		glEnd();
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glutSolidTorus(0.275, 0.85, 8, 15);
	glPopMatrix();
	//glFlush();
	glutSwapBuffers();
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacaoMalha(void) {
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angleMalha, fAspectMalha, 0.4, 500);

	// ??
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);
//	gluLookAt(1.0, -1.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void redesenharMalha(GLsizei w, GLsizei h) {
	// Para previnir uma divisão por zero
	if (h == 0)
		h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	// Calcula a correção de aspecto
	fAspectMalha = (GLfloat) w / (GLfloat) h;

	EspecificaParametrosVisualizacaoMalha();
}

void tecladoMalha(unsigned char key, int x, int y) {
	ofstream fout("Malha.ply", ios::binary);

	float k = 0.01;

	switch (key) {
	case 'a':

		cout << x << endl;
		x = 1.0f;

		vert[0].x = x;

		cout << "Incrementado malha em arquivo .ply..." << endl;
		fout.write(reinterpret_cast<char *>(&f1), sizeof(Face));

		cout << x << endl;
		cout << y << endl;
//		cout << f1.v1.x << endl;
//		cout << f1.v1.y << endl;
//		cout << f1.v2.x << endl;
//		cout << f1.v2.y << endl;
//		cout << f1.v3.x << endl;
//		cout << f1.v3.y << endl;

		cout << "Incrementado." << endl;

		break;
	case 'b':
		x = 0.0f;

		vert[0].x = x;

		cout << "Decrementando malha em arquivo .ply..." << endl;
		fout.write(reinterpret_cast<char *>(&f1), sizeof(Face));

		cout << x << endl;
		cout << y << endl;
//		cout << f1.v1.x << endl;
//		cout << f1.v1.y << endl;
//		cout << f1.v2.x << endl;
//		cout << f1.v2.y << endl;
//		cout << f1.v3.x << endl;
//		cout << f1.v3.y << endl;

		cout << "Decrementado." << endl;

		break;
	case 27:
#ifdef __linux__
		glutDestroyWindow(Wind);
#endif
		exit(EXIT_SUCCESS);
		break;
	}
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclado
void GerenciaTeclado(unsigned char key, int x, int y) {
	switch (key) {
	case 'R':
	case 'r':	// muda a cor corrente para vermelho
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case 'G':
	case 'g':	// muda a cor corrente para verde
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case 'B':
	case 'b':	// muda a cor corrente para azul
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case 'C':
	case 'c': //muda a cor do objeto para ciano
		glColor3f(0.0f, 1.0f, 1.0f);
		break;
	case 'M':
	case 'm':
		glColor3f(1.0f, 0.0f, 1.0f);
		break;

	case '+':
		spinMalha = (spinMalha + 30) % 360;
		break;

	case '-':
		spinMalha = (spinMalha - 30) % 360;
		break;

//	case '':
//		glColor3f(RMalha, GMalha, BMalha);
	}
	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		obsX -= 10;
		break;
	case GLUT_KEY_RIGHT:
		obsX += 10;
		break;
	case GLUT_KEY_UP:
		obsY += 10;
		break;
	case GLUT_KEY_DOWN:
		obsY -= 10;
		break;

	case GLUT_KEY_HOME:
		obsZ += 10;
		break;
	case GLUT_KEY_END:
		obsZ -= 10;
		break;
	}
	glLoadIdentity();
	gluLookAt(obsX, obsY, obsZ, 0, 0, 0, 0, 1, 0);
	glutPostRedisplay();
}

void GerenciaMouseMalha(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angleMalha >= 10)
				angleMalha -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angleMalha <= 130)
				angleMalha += 5;
		}
	EspecificaParametrosVisualizacaoMalha();
	glutPostRedisplay();
}

enum AtributoPly {
	NONE, VERTEX, FACE
};

enum VerticeCoor {
	XCOOR = 1, YCOOR, ZCOOR
};

void imprimirVertice(int numLinhas, int fim_cabecalho, int verticeCoor) {
	if (numLinhas - fim_cabecalho < 10)
		if (verticeCoor == XCOOR)
			cout << "P(" << vert[numLinhas - fim_cabecalho - 1].x << ", ";
		else if (verticeCoor == YCOOR)
			cout << vert[numLinhas - fim_cabecalho - 1].y << ", ";
		else if (verticeCoor == ZCOOR)
			cout << vert[numLinhas - fim_cabecalho - 1].x << ")" << endl;
}

void imprimirFace(int numLinhas, int fim_cabecalho, int linhaAtual,
		int numVertices, int faceVertice, int numVertPorFace) {
	if (numLinhas - fim_cabecalho - numVertices <= 10) {
		if (linhaAtual != numLinhas) {
			cout << "F(" << numLinhas - fim_cabecalho - numVertices << ") = (";
			linhaAtual = numLinhas;
		}
		cout
				<< face[numLinhas - (numVertices + fim_cabecalho) - 1].v[faceVertice
						- 1];
		if (faceVertice + 1 <= numVertPorFace)
			cout << ", ";
		else
			cout << ")" << endl;
	}
}

bool construirCabecalho(char *pch, int *fim_cabecalho, int *numLinhas,
		int *verticeCoor, int *atributoPly, int *numVertices, int *numFaces) {

	if (strcmp(pch, "end_header") == 0) {
		fim_cabecalho = numLinhas;
		*verticeCoor = XCOOR;
	} else if (strcmp(pch, "vertex") == 0) {
		*atributoPly = VERTEX;
	} else if (strcmp(pch, "face") == 0) {
		*atributoPly = FACE;
	} else if (*atributoPly == VERTEX) {
		*numVertices = atoi(pch);
		vert = new Vertice[*numVertices];
		*atributoPly = NONE;
	} else if (*atributoPly == FACE) {
		*numFaces = atoi(pch);
		*atributoPly = NONE;
		face = new Face[*numFaces];
	} else
		return false;

	return true;
}

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
	char * pch;
	ifstream finPly(nomeArquivo); // Cria arquivo para leitura em modo texto

	// Seção de Comandos
	if (!finPly) {
		cerr << "Erro ao abrir o arquivo" << endl;
		exit(EXIT_FAILURE);
	}

	while (!finPly.eof()) { // Enquanto não terminou o arquivo
		finPly.getline(buff, MAX);
		pch = strtok(buff, " ,\r\n");
		while (pch != NULL) {
			numPalavras++;
			// Construção do cabeçalho
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
			} else
			//if(!construirCabecalho(pch, &fim_cabecalho, &numLinhas, &verticeCoor, &atributoPly, &numVertices, &numFaces))
			if (fim_cabecalho > 0 // Lista e grava vértices na lista de vértices
			&& numLinhas < numVertices + fim_cabecalho + 1) {
				if (strcmp(pch, "\r") != 0) {
					if (verticeCoor == XCOOR) {
						vert[numLinhas - fim_cabecalho - 1].x = atof(pch);
						imprimirVertice(numLinhas, fim_cabecalho, XCOOR);
						verticeCoor = YCOOR;
					} else if (verticeCoor == YCOOR) {
						vert[numLinhas - fim_cabecalho - 1].y = atof(pch);
						imprimirVertice(numLinhas, fim_cabecalho, YCOOR);
						verticeCoor = ZCOOR;
					} else if (verticeCoor == ZCOOR) {
						vert[numLinhas - fim_cabecalho - 1].z = atof(pch);
						imprimirVertice(numLinhas, fim_cabecalho, ZCOOR);
						verticeCoor = XCOOR;
					}
				}
			} else if (fim_cabecalho > 0 // Lista e grava faces na lista de faces
			&& numLinhas < numFaces + numVertices + fim_cabecalho + 1) {
				if (strcmp(pch, "\r") != 0) {
					if (numLinhas == numVertices + fim_cabecalho + 1
							&& numVertPorFace == 0) {
						// Para todas as faces
						numVertPorFace = atoi(pch);
						for (int var = 0; var < numFaces; ++var) {
							face[var].v = new int[numVertPorFace];
						}
						faceVertice = 1;
					} else if (faceVertice <= numVertPorFace
							&& faceVertice > 0) {
						// Atribuir número de vértices para a face local ou atual
						face[numLinhas - (numVertices + fim_cabecalho) - 1].numVertices =
								numVertPorFace;

						// Atribuir a posição do vértice na lista de vértices do arquivo ply
						face[numLinhas - (numVertices + fim_cabecalho) - 1].v[faceVertice
								- 1] = atoi(pch);
						imprimirFace(numLinhas, fim_cabecalho, linhaAtual,
								numVertices, faceVertice, numVertPorFace);

						if (faceVertice + 1 <= numVertPorFace)
							faceVertice++;
						else
							faceVertice = 0;
					} else if (strcmp(pch, "\r") != 0)
						faceVertice++;
				}
			}
			numCaracteres += strlen(pch);
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
#ifdef __linux__
	Wind = glutCreateWindow("Malha Ply");
#else
	glutCreateWindow("Malha Ply");
#endif
	inicializarMalha();
	glutDisplayFunc(desenharMalha);
	glutReshapeFunc(redesenharMalha);
//	glutKeyboardFunc(tecladoMalha);
	glutKeyboardFunc(GerenciaTeclado);
	glutMouseFunc(GerenciaMouseMalha);
	glutSpecialFunc(SpecialKeys);
	glutMainLoop();

	return 0;
}

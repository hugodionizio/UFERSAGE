/*
 * Malha.c
 *
 *  Created on: Mar 30, 2016
 *      Author: hugo
 */

#define ARQUIVO_TESTE "airplanelinux.ply"

#include <GL/glew.h>
#include <GL/glui.h>

// Diretivas
#include <fstream> // Para a classe de arquivos
#include <iostream>
#include <cstring>

using namespace std;

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

FGAPI int FGAPIENTRY Wind;

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
	glEnable(GL_DEPTH_TEST);

	makeMalhaImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef GL_VERSION_1_1
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef GL_VERSION_1_1
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
			0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#else
	glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,
			0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#endif
}

void desenharMalha(void) {
	bool salvar = false;
	// Seção de Declarações Internas
	ifstream fin("Malha.ply", ios::binary);
	ofstream fout2("MalhaTmp.ply", ios::binary);

	// Ler malha de um arquivo
	cout << "Lendo malha de arquivo .ply..." << endl;
	int tam = 0;
	while (fin.read(reinterpret_cast<char *>(&f1), sizeof(Face))) {
		tam++;
	}

	if (tam == 0) {
		cout << "Arquivo inexistente." << endl;
		criarMalha(&m1, x, y, 6, 8, 10, 12);
		salvar = true;
	} else {
		m1.f = new Face[1];
		m1.f = &f1;
		x = m1.f->v1.x;
		y = m1.f->v1.y;
	}
	fin.close();

	cout << "Imprimindo..." << endl;
//	else {
//		cout << m1.f->v1.x << endl;
//		cout << m1.f->v1.y << endl;
//		cout << m1.f->v2.x << endl;
//		cout << m1.f->v2.y << endl;
//		cout << m1.f->v3.x << endl;
//		cout << m1.f->v3.y << endl;
//	}

	f1 = *m1.f;
	x = f1.v1.x;
	y = f1.v1.y;

	cout << x << endl;
	cout << y << endl;
	cout << f1.v1.x << endl;
	cout << f1.v1.y << endl;
	cout << f1.v2.x << endl;
	cout << f1.v2.y << endl;
	cout << f1.v3.x << endl;
	cout << f1.v3.y << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
#ifdef GL_VERSION_1_1
	glBindTexture(GL_TEXTURE_2D, texName);
#endif

	glBegin(GL_QUADS);
	glTexCoord2f(x, y);
	glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(2.41421, 1.0, -1.41421);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(2.41421, -1.0, -1.41421);
	glEnd();

	if (salvar) {
//		m1.f->v1.x*=2;

// Gravar/atualizar/substituir malha em um arquivo
		cout << "Gravando malha em arquivo .ply..." << endl;
		ofstream fout("Malha.ply", ios::binary);
		fout.write(reinterpret_cast<char *>(&f1), sizeof(Face));
		fout.close();
	} else {
		cout << "Fazendo backup..." << endl;
		fout2.write(reinterpret_cast<char *>(&f1), sizeof(Face));
		fout2.close();
	}

	glFlush();
	glDisable(GL_TEXTURE_2D);
}

void redesenharMalha(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -3.6);
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
		glutDestroyWindow(Wind);
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

int mainMalha(int argc, char **argv) {
	const int MAX = 80;

	// Variáveis
	int comecouPalavra = 0, numPalavras = 0, numLinhas = 0, numCaracteres = 0;
	char buff[MAX];
	int fim_cabecalho = -1;
	int atributoPly = NONE;
	int numVertices = 0, numFaces = 0, numVertPorFace = 3;
	int verticeCoor = NONE, faceVertice = NONE;

	char *nomeArquivo;
	if (argc > 2)
		nomeArquivo = argv[2];
	else
		nomeArquivo = (char *) ARQUIVO_TESTE;

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
				for (int var = 0; var < numFaces; ++var) {
					face[var].v = new int[numVertPorFace];
				}
			} else if (fim_cabecalho > 0 // Lista e grava vértices na lista de vértices
					&& numLinhas < numVertices + fim_cabecalho + 1) {
				if (verticeCoor == XCOOR) {
					vert[numLinhas - fim_cabecalho].x = atof(pch);
					if (numLinhas - fim_cabecalho < 10)
						cout << "P(" << vert[numLinhas - fim_cabecalho].x;
					verticeCoor = YCOOR;
				} else if (verticeCoor == YCOOR) {
					vert[numLinhas - fim_cabecalho].y = atof(pch);
					if (numLinhas - fim_cabecalho < 10)
						cout << ", " << vert[numLinhas - fim_cabecalho].y;
					verticeCoor = ZCOOR;
				} else if (verticeCoor == ZCOOR) {
					vert[numLinhas - fim_cabecalho].z = atof(pch);
					if (numLinhas - fim_cabecalho < 10)
						cout << ", " << vert[numLinhas - fim_cabecalho].z << ")" << endl;
					verticeCoor = XCOOR;
				}
			} else if (fim_cabecalho > 0 // Lista e grava faces na lista de faces
					&& numLinhas < numFaces + numVertices + fim_cabecalho) {
				if (numLinhas == numVertices + fim_cabecalho || faceVertice == numVertPorFace)
					faceVertice = 0;
				else if (faceVertice < numVertPorFace) {
					face[numLinhas - (numVertices + fim_cabecalho)].numVertices =
							numVertices;
					face[numLinhas - (numVertices + fim_cabecalho)].v[faceVertice] =
							atoi(pch);
					if (numLinhas - fim_cabecalho - numVertices < 10)
						cout << "face(i) = " << atoi(pch)
							<< endl;
					faceVertice++;
				}
			}
			pch = strtok(NULL, " ");
		}

		numCaracteres += strlen(buff);
//		if(numLinhas < 10)
			//cout << "(" << strlen(buff) << " caracteres)" << buff << endl;
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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(650, 600);
	glutInitWindowPosition(100, 100);
//   glutCreateWindow(argv[0]);
	Wind = glutCreateWindow("Malha Ply");
	inicializarMalha();
	glutDisplayFunc(desenharMalha);
	glutReshapeFunc(redesenharMalha);
	glutKeyboardFunc(tecladoMalha);
	glutMainLoop();
	return 0;
}

/*
 * Malha.c
 *
 *  Created on: Mar 30, 2016
 *      Author: hugo
 */

#include <GL/glew.h>
#include <GL/glui.h>

// Diretivas
#include <fstream> // Para a classe de arquivos
#include <iostream>

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
};

struct Face {
	Vertice v1;
	Vertice v2;
	Vertice v3;
};

struct Malha {
	Face *f;
};

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

int mainMalha(int argc, char **argv) {

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

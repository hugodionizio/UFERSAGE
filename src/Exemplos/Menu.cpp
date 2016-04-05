// Menu.c - Isabel H. Manssour
// Um programa OpenGL simples que exemplifica
// como exibir textos e utilizar menus e funções
// callback para verificar a movimenta��o do 
// mouse na janela GLUT.
// Este c�digo est� baseado nos exemplos 
// dispon�veis no livro "OpenGL SuperBible", 
// 2nd Edition, de Richard S. e Wright Jr.

#ifdef WINDOWS
# include <windows.h>
# include <gl/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <GL/glui.h>
#endif
#include <string.h>
#include <stdio.h>
#include "Exemplos.h"
#include "../Examples/examples.h"

// Constantes
//#define QUADRADO 1
//#define TRIANGULO 2
//#define LOSANGO   3
enum Exemplo {
	// Exemplos (Manssour)
	PRIMEIRO_PROGRAMA,
	ANIMA,
	INTERACAO,
	NUM_PRIM_EXEMPLOS,
	QUADRADO,
	TRIANGULO,
	LOSANGO,
	PRIMITIVAS,
	TEAPOT3D,
	ILUMINACAO,
	NUM_EXEMPLOS,

	// Examples (redbook)
	CHUNKOPENGL,
	HELLO,
	DOUBLE,
	LINES,
	POLYS,
	VARRAY,
	MVARRAY,
	CUBE,
	MODEL,
	CLIP,
	PLANET,
	ROBOT,
	UNPROJECT,
	SMOOTH,
	LIGHT,
	MOVELIGHT,
	MATERIAL,
	COLORMAT,
	NUM_EXAMPLES
};

enum Cor {
	VERMELHO, VERDE, AZUL, NUM_CORES
};

// Variáveis
char texto[30];
GLfloat win_menu, r, g, b;
GLint view_w_menu, view_h_menu, primitiva;

#define OFFSET_X 125.0f
#define OFFSET_Y 125.0f

// Função que desenha um quadrado
void DesenhaQuadradoMenu(void) {
	glBegin (GL_QUADS);
	glVertex2f(-25.0f + OFFSET_X, -25.0f + OFFSET_Y);
	glVertex2f(-25.0f + OFFSET_X, 25.0f + OFFSET_Y);
	glVertex2f(25.0f + OFFSET_X, 25.0f + OFFSET_Y);
	glVertex2f(25.0f + OFFSET_X, -25.0f + OFFSET_Y);
	glEnd();
}

// Função que desenha um tri�ngulo
void DesenhaTrianguloMenu(void) {
	glBegin (GL_TRIANGLES);
	glVertex2f(-25.0f + OFFSET_X, -25.0f + OFFSET_Y);
	glVertex2f(0.0f + OFFSET_X, 25.0f + OFFSET_Y);
	glVertex2f(25.0f + OFFSET_X, -25.0f + OFFSET_Y);
	glEnd();
}

// Função que desenha um losango
void DesenhaLosangoMenu(void) {
	glBegin (GL_POLYGON);
	glVertex2f(-25.0f + OFFSET_X, 0.0f + OFFSET_Y);
	glVertex2f(0.0f + OFFSET_X, 25.0f + OFFSET_Y);
	glVertex2f(25.0f + OFFSET_X, 0.0f + OFFSET_Y);
	glVertex2f(0.0f + OFFSET_X, -25.0f + OFFSET_Y);
	glEnd();
}

// Desenha um texto na janela GLUT
void DesenhaTextoMenu(char *string) {
	glPushMatrix();
	// Posi��o no universo onde o texto ser� colocado
	glRasterPos2f(-win_menu + win_menu,
			win_menu - (win_menu * 0.08) + OFFSET_Y / 1.2);
	// Exibe caracter a caracter
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *string++);
	glPopMatrix();
}

// Função callback chamada para fazer o desenho
void DesenhaMenu(void) {
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	glClear (GL_COLOR_BUFFER_BIT);

	// Define a cor corrente
	glColor3f(r, g, b);

	// Desenha uma primitiva
	switch (primitiva) {
	// Exemplos (Manssour)
	case PRIMEIRO_PROGRAMA:
		DesenhaPrimeiroPrograma();
		break;
	case ANIMA:
		DesenhaAnima();
		break;
	case INTERACAO:
		DesenhaInteracao();
		break;
	case QUADRADO:
		DesenhaQuadradoMenu();
		break;
	case TRIANGULO:
		DesenhaTrianguloMenu();
		break;
	case LOSANGO:
		DesenhaLosangoMenu();
		break;
	case TEAPOT3D:
		DesenhaTeaPot3D();
		break;
	case ILUMINACAO:
		DesenhaIluminacao();
		break;

	// Examples (redbook)
	case CHUNKOPENGL:
		displayChunkOpenGL();
		break;
	case HELLO:
		displayHello();
		break;
	case DOUBLE:
		displayDouble();
		break;
	case LINES:
		displayLines();
		break;
	case POLYS:
		displayPolys();
		break;
	case VARRAY:
		displayVarray();
		break;
	case MVARRAY:
		displayMVArray();
		break;
	case CUBE:
		displayCube();
		break;
	case MODEL:
		displayModel();
		break;
	case CLIP:
		displayClip();
		break;
	case PLANET:
		displayPlanet();
		break;
	case ROBOT:
		displayRobot();
		break;
	case UNPROJECT:
		displayUnProject();
		break;
	case SMOOTH:
		displaySmooth();
		break;
	case LIGHT:
		displayLight();
		break;
	case MOVELIGHT:
		displayMoveLight();
		break;
	case MATERIAL:
		displayMaterial();
		break;
	case COLORMAT:
		displayColorMat();
		break;
	}

	// Exibe a posi��o do mouse na janela
	glColor3f(1.0f, 1.0f, 1.0f);
	DesenhaTextoMenu(texto);

	glutSwapBuffers();
}

// Inicializa par�metros de rendering
void InicializaMenu(void) {
	// Define a cor de fundo da janela de visualiza��o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	win_menu = 150.0f;
	primitiva = PRIMEIRO_PROGRAMA;
	r = 0.0f;
	g = 0.0f;
	b = 1.0f;
	strcpy(texto, "(0,0)");
}

// Função callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanelaMenu(GLsizei w, GLsizei h) {
	extern GLfloat windowHeight;
	extern GLfloat windowWidth;

	// Evita a divisao por zero
	if (h == 0)
		h = 1;

	// Estabelece a janela de sele��o (left, right, bottom, top)
	if (w <= h) {
		windowHeight = 250.0f * h / w;
		windowWidth = 250.0f;
	} else {
		windowWidth = 250.0f * w / h;
		windowHeight = 250.0f;
	}

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);
	view_w_menu = w;
	view_h_menu = h;

	// Inicializa o sistema de coordenadas
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
//	gluOrtho2D(-win_menu, win_menu, -win_menu, win_menu);
	gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

// Função callback chamada sempre que o mouse � movimentado
// sobre a janela GLUT com um bot�o pressionado
void MoveMouseBotaoPressionadoMenu(int x, int y) {
	sprintf(texto, "Botao pressionado (%d,%d)", x, y);
	glutPostRedisplay();
}

// Função callback chamada sempre que o mouse � movimentado
// sobre a janela GLUT 
void MoveMouseMenu(int x, int y) {
	sprintf(texto, "(%d,%d)", x, y);
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos do teclado
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciaisMenu(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		win_menu -= 10;
		if (win_menu < 10)
			win_menu = 10;
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win_menu, win_menu, -win_menu, win_menu);
	}
	if (key == GLUT_KEY_DOWN) {
		win_menu += 10;
		if (win_menu > 500)
			win_menu = 500;
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win_menu, win_menu, -win_menu, win_menu);
	}
	glutPostRedisplay();
}

// Gerenciamento do menu com as opções de cores
void MenuCor(int op) {
	switch (op) {
	case VERMELHO:
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
		break;
	case VERDE:
		r = 0.0f;
		g = 1.0f;
		b = 0.0f;
		break;
	case AZUL:
		r = 0.0f;
		g = 0.0f;
		b = 1.0f;
		break;
	}
	glutPostRedisplay();
}

// Gerenciamento do menu com as opções de exemplos
void MenuExemplos(int op) {
	if (op < NUM_EXEMPLOS && op != NUM_PRIM_EXEMPLOS && op != PRIMITIVAS) {
		primitiva = op;
	}
	glutPostRedisplay();
}

// Gerenciamento do menu com as opções de exemplos
void MenuExemplosRedBook(int op) {
	if (op < NUM_EXAMPLES && op > NUM_EXEMPLOS) {
		primitiva = op;
	}
	glutPostRedisplay();
}

// Gerenciamento do menu com as opções de exemplos
void MenuExemplosUnidadeI(int op) {
}

// Gerenciamento do menu principal           
void MenuPrincipal(int op) {
	if (op < NUM_PRIM_EXEMPLOS || (op > PRIMITIVAS && op < NUM_EXEMPLOS)) {
		primitiva = op;
	}
}

// Criacao do Menu
void CriaMenu() {
	int menu, submenu1, submenu2, submenu3, menuUnidadeI;

	submenu1 = glutCreateMenu(MenuCor);
	glutAddMenuEntry("Vermelho", VERMELHO);
	glutAddMenuEntry("Verde", VERDE);
	glutAddMenuEntry("Azul", AZUL);

	submenu2 = glutCreateMenu(MenuExemplos);
	glutAddMenuEntry("Quadrado", QUADRADO);
	glutAddMenuEntry("Triângulo", TRIANGULO);
	glutAddMenuEntry("Losango", LOSANGO);

	submenu3 = glutCreateMenu(MenuExemplosRedBook);
	glutAddMenuEntry("ChunkOpenGL", CHUNKOPENGL);
	glutAddMenuEntry("Hello", HELLO);
	glutAddMenuEntry("Double", DOUBLE);
	glutAddMenuEntry("Lines", LINES);
	glutAddMenuEntry("Polys", POLYS);
	glutAddMenuEntry("Varray", VARRAY);
	glutAddMenuEntry("MVArray", MVARRAY);
	glutAddMenuEntry("Cube", CUBE);
	glutAddMenuEntry("Model", MODEL);
	glutAddMenuEntry("Clip", CLIP);
	glutAddMenuEntry("Planet", PLANET);
	glutAddMenuEntry("Robot", ROBOT);
	glutAddMenuEntry("UnProject", UNPROJECT);
	glutAddMenuEntry("Smooth", SMOOTH);
	glutAddMenuEntry("Light", LIGHT);
	glutAddMenuEntry("MoveLight", MOVELIGHT);
	glutAddMenuEntry("Material", MATERIAL);
	glutAddMenuEntry("ColorMat", COLORMAT);

	menuUnidadeI = glutCreateMenu(MenuExemplosUnidadeI);
	glutAddSubMenu("Unidade I", submenu3);

	menu = glutCreateMenu(MenuPrincipal);
	glutAddMenuEntry("Primeiro Programa", PRIMEIRO_PROGRAMA);
	glutAddMenuEntry("Anima", ANIMA);
	glutAddMenuEntry("Interação", INTERACAO);
	glutAddSubMenu("Cor", submenu1);
	glutAddSubMenu("Primitivas", submenu2);
	glutAddMenuEntry("TeaPot3D", TEAPOT3D);
	glutAddMenuEntry("Iluminação", ILUMINACAO);
	glutAddSubMenu("Outros exemplos", menuUnidadeI);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)
			CriaMenu();

	glutPostRedisplay();
}

// Programa Principal 
int mainMenu(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(650, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Exemplo de Menu e Exibição de Caracteres");
	glutDisplayFunc(DesenhaMenu);
	glutReshapeFunc(AlteraTamanhoJanelaMenu);
	glutMotionFunc(MoveMouseBotaoPressionadoMenu);
	glutPassiveMotionFunc(MoveMouseMenu);
	glutMouseFunc(GerenciaMouse);
	glutSpecialFunc(TeclasEspeciaisMenu);
	glutTimerFunc(33, Timer, 1);
	InicializaMenu();
	glutMainLoop();
}

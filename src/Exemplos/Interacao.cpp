// Interacao.c - Isabel H. Manssour
// Um programa OpenGL simples que desenha um  quadrado em
// uma janela GLUT de acordo com intera��es do usu�rio.
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
#endif

GLfloat xf, yf, win;
GLint view_w, view_h;

// Fun��o callback chamada para fazer o desenho
void DesenhaInteracao(void) {
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	glClear (GL_COLOR_BUFFER_BIT);
	// Desenha um ret�ngulo preenchido com a cor corrente
	glBegin (GL_POLYGON);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(xf, 0.0f);
	glVertex2f(xf, yf);
	glVertex2f(0.0f, yf);
	glEnd();
	glFlush();
}

// Inicializa par�metros de rendering
void InicializaInteracao(void) {
	// Define a cor de fundo da janela de visualiza��o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	xf = 50.0f;
	yf = 50.0f;
	win = 250.0f;
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanelaInteracao(GLsizei w, GLsizei h) {
	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);
	view_w = w;
	view_h = h;

	// Inicializa o sistema de coordenadas
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-win, win, -win, win);
}

// Fun��o callback chamada para gerenciar eventos de teclado
void GerenciaTecladoInteracao(unsigned char key, int x, int y) {
	switch (key) {
	case 'R':
	case 'r': // muda a cor corrente para vermelho
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case 'G':
	case 'g': // muda a cor corrente para verde
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case 'B':
	case 'b': // muda a cor corrente para azul
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	}
	glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos do mouse
void GerenciaMouseInteracao(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			// Troca o tamanho do ret�ngulo, que vai do centro da
			// janela at� a posi��o onde o usu�rio clicou com o mouse
			xf = ((2 * win * x) / view_w) - win;
			yf = (((2 * win) * (y - view_h)) / -view_h) - win;
		}
	glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos do teclado   
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciaisInteracao(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		win -= 20;
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win, win, -win, win);
	}
	if (key == GLUT_KEY_DOWN) {
		win += 20;
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win, win, -win, win);
	}
	glutPostRedisplay();
}

// Programa Principal 
int mainInteracao(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(350, 300);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Exemplo de Interacao");
	glutDisplayFunc(DesenhaInteracao);
	glutReshapeFunc(AlteraTamanhoJanelaInteracao);
	glutKeyboardFunc(GerenciaTecladoInteracao);
	glutMouseFunc(GerenciaMouseInteracao);
	glutSpecialFunc(TeclasEspeciaisInteracao);
	InicializaInteracao();
	glutMainLoop();
}

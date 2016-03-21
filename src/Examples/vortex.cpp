#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
#define imageWidth 512
#define imageHeight 512

float xrot, yrot, zrot;

GLuint texture;
GLuint pbo;

unsigned char *image;
int t = 0;
int a = 200;
int bVortex = 240;
int c = 260;
float zoom;

void displayVortex() {
	int i = 0;
//do 2 iterations per frame so black/white don't alternate every frame
	for (i = 0; i < 2; i++) {
//clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//transform the view
		glLoadIdentity();

		glTranslatef(0, 0, zoom);
		glRotatef(xrot, 1, 0, 0);
		glRotatef(yrot, 0, 1, 0);
		glRotatef(zrot, 0, 0, 1);

		if (i == 1)
			glClearColor((float) (t % a) / a, (float) (t % bVortex) / bVortex,
					(float) (t % c) / c, 1);
		else
			glClearColor(0, 0, 0, 1);
		t++;

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, pbo);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, imageWidth, imageHeight,
				GL_RGBA,
				GL_UNSIGNED_BYTE, 0);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);

		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
		glTexCoord2f(1, 1);
		glVertex2f(1, 1);
		glTexCoord2f(1, 0);
		glVertex2f(1, -1);
		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		zrot += .001f;
		zoom = sin((float) t / 200) / 200 - 2.416;

// activate destination buffer
		glBindBuffer( GL_PIXEL_PACK_BUFFER_ARB, pbo);

// read data into pbo. note: use BGRA format for optimal performance
		glReadPixels(0, 0, imageWidth, imageHeight, GL_RGBA, GL_UNSIGNED_BYTE,
		NULL);

	}
	glutSwapBuffers();
	glutPostRedisplay();
}
int mainVortex(int argc, char **argv) {
//initialize necessary GLUT things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("");
	glutIdleFunc(&displayVortex);
	glClearColor(1, 1, 1, 1);

//create the data to put into the texture
	int size = imageWidth * imageHeight * 4;
	image = (unsigned char *) malloc(sizeof(unsigned char) * size);
	int i;
	for (i = 0; i < size; i = i + 1)
		image[i] = (i / 256);  //create the texture
	glGenTextures((GLuint) 1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, image); //initialize the extentions needed for using a PBO
	glewInit();
	if (!glewIsSupported("GL_VERSION_2_0 " "GL_ARB_pixel_buffer_object"))
		printf("ERROR: Support for necessary OpenGL extensions missing."); //create the PBO
	glGenBuffers(1, &pbo);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1); //upload our host image data to the pixel buffer
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, pbo);
	glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB,
			sizeof(unsigned char) * imageWidth * imageHeight * 4, image,
			GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0); //initialize the GL projection
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0f, (GLfloat) WINDOW_WIDTH / (GLfloat) WINDOW_HEIGHT,
			0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);  //enter the main loop
	glutMainLoop();
	return 0;
}

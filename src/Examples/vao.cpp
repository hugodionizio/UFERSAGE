/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 * vao.cpp
 *
 *  Created on: 21/03/2016
 *      Author: hugo
 */

#include "whateverYouNeed.h"

#define BUFFER_OFFSET(offset) ((GLvoid*) NULL + offset)
#define NumberOf(array) (sizeof(array)/sizeof(array[0]))

typedef struct {
	GLfloat x, y, z;
} vec3;

typedef struct {
	vec3 xlate; /* Translation */
	GLfloat angle;
	vec3 axis;
} XForm;

enum {
	Cube, Cone, NumVAOs
};
GLuint VAO[NumVAOs];
GLenum PrimType[NumVAOs];
GLsizei NumElements[NumVAOs];
XForm Xform[NumVAOs] = { { { -2.0, 0.0, 0.0 }, 0.0, { 0.0, 1.0, 0.0 } }, { {
		0.0, 0.0, 2.0 }, 0.0, { 1.0, 0.0, 0.0 } } };
GLfloat AngleVao = 0.0;

void initVao() {
	enum {
		Vertices, Colors, Elements, NumVBOs
	};
	GLuint buffers[NumVBOs];

	glGenVertexArrays(NumVAOs, VAO);
	{
		GLfloat cubeVerts[][3] = { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, 1.0 }, {
				-1.0, 1.0, -1.0 }, { -1.0, 1.0, 1.0 }, { 1.0, -1.0, -1.0 }, {
				1.0, -1.0, 1.0 }, { 1.0, 1.0, -1.0 }, { 1.0, 1.0, 1.0 }, };

		GLfloat cubeColors[][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0,
				1.0, 0.0 }, { 0.0, 1.0, 1.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 0.0,
				1.0 }, { 1.0, 1.0, 0.0 }, { 1.0, 1.0, 1.0 }, };

		GLubyte cubeIndices[] = { 0, 1, 3, 2, 4, 6, 7, 5, 2, 3, 7, 6, 0, 4, 5,
				1, 0, 2, 6, 4, 1, 5, 7, 3 };

		glBindVertexArray(VAO[Cube]);
		glGenBuffers(NumVBOs, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts,
		GL_STATIC_DRAW);
		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors,
		GL_STATIC_DRAW);
		glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glEnableClientState(GL_COLOR_ARRAY);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices,
		GL_STATIC_DRAW);

		PrimType[Cube] = GL_QUADS;
		NumElements[Cube] = NumberOf(cubeIndices);
	}
	{
		int i, idx;
		float dTheta;

#define NumConePoints 36
		/* We add one more vertex for the cone's apex */
		GLfloat coneVerts[NumConePoints + 1][3] = { { 0.0, 0.0, 1.0 } };
		GLfloat coneColors[NumConePoints + 1][3] = { { 1.0, 1.0, 1.0 } };
		GLubyte coneIndices[NumConePoints + 1];

		dTheta = 2 * M_PI / (NumConePoints - 1);
		idx = 1;
		for (i = 0; i < NumConePoints; ++i, ++idx) {
			float theta = i * dTheta;
			coneVerts[idx][0] = cos(theta);
			coneVerts[idx][1] = sin(theta);
			coneVerts[idx][2] = 0.0;

			coneColors[idx][0] = cos(theta);
			coneColors[idx][1] = sin(theta);
			coneColors[idx][2] = 0.0;

			coneIndices[idx] = idx;
		}

		glBindVertexArray(VAO[Cone]);
		glGenBuffers(NumVBOs, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coneVerts), coneVerts,
		GL_STATIC_DRAW);
		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coneColors), coneColors,
		GL_STATIC_DRAW);
		glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glEnableClientState(GL_COLOR_ARRAY);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coneIndices), coneIndices,
		GL_STATIC_DRAW);

		PrimType[Cone] = GL_TRIANGLE_FAN;
		NumElements[Cone] = NumberOf(coneIndices);
	}
	glEnable(GL_DEPTH_TEST);
}

void displayVao() {
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(AngleVao, 0.0, 1.0, 0.0);

	for (i = 0; i < NumVAOs; ++i) {
		glPushMatrix();
		glTranslatef(Xform[i].xlate.x, Xform[i].xlate.y, Xform[i].xlate.z);
		glRotatef(Xform[i].angle, Xform[i].axis.x, Xform[i].axis.y,
				Xform[i].axis.z);
		glBindVertexArray(VAO[i]);
		glDrawElements(PrimType[i], NumElements[i],
		GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
		glPopMatrix();
	}

	glPopMatrix();
	glutSwapBuffers();
}

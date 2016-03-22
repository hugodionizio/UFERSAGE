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
 * primrestart.cpp
 *
 *  Created on: 20/03/2016
 *      Author: hugo
 */

#include "whateverYouNeed.h"

#define BUFFER_OFFSET(offset) ((GLvoid *) NULL + offset)

#define XStart	-0.8
#define XEnd	0.8
#define YStart	-0.8
#define YEnd	0.8

#define NumXPoints			11
#define NumYPoints			11
#define NumPoints			(NumXPoints * NumYPoints)
#define NumPointsPerStrip	(2*NumXPoints)
#define NumStrips			(NumYPoints-1)
#define RestartIndex		0xffff

void initPrimRestart() {
	GLuint vbo, ebo;
	GLfloat * vertices;
	GLushort *indices;

	/* Set up vertex data */
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * NumPoints * sizeof(GLfloat), NULL,
	GL_STATIC_DRAW);

	vertices = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (vertices == NULL) {
		fprintf(stderr, "Unable to map vertex buffer\n");
		exit(EXIT_FAILURE);
	} else {
		int i, j;
		GLfloat dx = (XEnd - XStart) / (NumXPoints - 1);
		GLfloat dy = (YEnd - YStart) / (NumYPoints - 1);
		GLfloat *tmp = vertices;
		int n = 0;

		for (j = 0; j < NumYPoints; ++j) {
			GLfloat y = YStart + j * dy;

			for (i = 0; i < NumXPoints; ++i) {
				GLfloat x = XStart + i * dx;
				*tmp++ = x;
				*tmp++ = y;
			}
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glVertexPointer(2, GL_FLOAT, 0, BUFFER_OFFSET(0));
		glEnableClientState(GL_VERTEX_ARRAY);
	}

	/* Set up index data */
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	/* We allocate an extra restart index because it simplifies
	 **	 the element-array loop logic */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	NumStrips * (NumPointsPerStrip + 1) * sizeof(GLushort),
	NULL, GL_STATIC_DRAW);
	indices = (GLushort *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

	if (indices == NULL) {
		fprintf(stderr, "Unable to map index buffer\n");
		exit(EXIT_FAILURE);
	} else {
		int i, j;
		GLushort *index = indices;

		for (j = 0; j < NumStrips; ++j) {
			GLushort bottomRow = j * NumYPoints;
			GLushort topRow = bottomRow + NumYPoints;

			for (i = 0; i < NumXPoints; ++i) {
				*index++ = topRow + i;
				*index++ = bottomRow + i;
			}
			*index++ = RestartIndex;
		}
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}
	glPrimitiveRestartIndex(RestartIndex);
	glEnable(GL_PRIMITIVE_RESTART);
}

void displayPrimRestart() {
	int i, start;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1, 1, 1);
	glDrawElements(GL_TRIANGLE_STRIP,
	NumStrips * (NumPointsPerStrip + 1),
	GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

	glutSwapBuffers();
}


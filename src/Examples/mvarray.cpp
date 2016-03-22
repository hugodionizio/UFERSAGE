/*
 * mvarray.cpp
 *
 *  Created on: 20/03/2016
 *      Author: hugo
 */

#include "whateverYouNeed.h"

/*
void glMultiDrawElements(GLenum mode, GLsizei *count, GLenum type,
		const GLvoid **indices, GLsizei primcount) {
	int i;

	for (i = 0; i < primcount; i++) {
	if (count[i] > 0)
	glDrawElements(mode, count[i], type, indices[i]);
	}
}
*/

int mainMVArray(int argc, char **argv) {
	static GLubyte oneIndices[] = { 0, 1, 2, 3, 4, 5, 6 };
	static GLubyte twoIndices[] = { 7, 1, 8, 9, 10, 11 };
	static GLsizei count[] = { 7, 6 };
	const GLvoid *indices[2] = { oneIndices, twoIndices };

	// GL_LINE_STRIP, count, GL_UNSIGNED_BYTE, indices, (GLsizei)2
	GLenum mode = GL_LINE_STRIP;
	GLsizei *count2 = count;
	GLenum type = GL_UNSIGNED_BYTE;
//	static const GLvoid **indices = indices2;
	GLsizei primcount = 2;

//	void glMultiDrawElements(unsigned int, int *, unsigned int, const void * *, int)
	glMultiDrawElements(mode, count2, type, indices, primcount);

	return 0;
}

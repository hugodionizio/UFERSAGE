/*
 * whateverYouNeed.h
 *
 *  Created on: 20/03/2016
 *      Author: hugo
 */

#ifndef SRC_EXAMPLES_WHATEVERYOUNEED_H_
#define SRC_EXAMPLES_WHATEVERYOUNEED_H_

#define GLEW_STATIC
#ifdef WINDOWS
# include <windows.h>
# include <gl/wglew.h>
# include <gl/glut.h>
# include <gl/glui.h>
#else
# include <GL/glew.h>
# include <GL/freeglut.h>
//# include <GL/freeglut_ext.h>
# include <GL/gl.h>
# include <GL/glext.h>
//# include <GL/gl_mangle.h>
# include <GL/glu.h>
//# include <GL/glu_mangle.h>
# include <GL/glut.h>
# include <GL/glui.h>
//# include <GL/internal/glcore.h>
# include <math.h>
#endif

#endif /* SRC_EXAMPLES_WHATEVERYOUNEED_H_ */

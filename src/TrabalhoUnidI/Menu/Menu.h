/*
 * Menu.h
 *
 *  Created on: 29/03/2016
 *      Author: hugo
 */

#ifndef SRC_TRABALHOUNIDI_MENU_MENU_H_
#define SRC_TRABALHOUNIDI_MENU_MENU_H_

#ifdef WINDOWS
# include <windows.h>
# include <gl/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif
#include <string.h>
#include <stdio.h>
#include <ft2build.h>
#include <freetype2/freetype.h>
#include <config/ftheader.h>
#include <FTGL/ftgl.h>
#include <FTGL/FTGLPixmapFont.h>

void DesenhaQuadradoQuestaoMenu(void);	// Desenhar Quadrado
void DesenhaTrianguloQuestaoMenu(void);	// Função que desenha um triângulo
void DesenhaPentagonoQuestaoMenu(void);	// Função que desenha um pentagono
void DesenhaHexagonoQuestaoMenu(void);	// Função que desenha um hexagono

#endif /* SRC_TRABALHOUNIDI_MENU_MENU_H_ */

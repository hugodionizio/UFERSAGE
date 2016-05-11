/*
 * examples.h
 *
 *  Created on: 20/03/2016
 *      Author: hugo
 */

#ifndef SRC_EXAMPLES_EXAMPLES_H_
#define SRC_EXAMPLES_EXAMPLES_H_

#include "../Exemplos/Exemplos.h"

enum Example_I {
	// Examples (redbook)
	CHUNKOPENGL = NUM_EXEMPLOS,
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
	EXAMPLES_I
};

// Unidade I
int mainChunkOpenGL(int, char**);
int mainHello(int, char**);
int mainDouble(int, char**);
int mainLines(int, char**);
int mainPolys(int, char**);
int mainVarray(int, char**);
int mainMVArray(int, char**);
int mainCube(int, char**);
int mainModel(int, char**);
int mainClip(int, char**);
int mainPlanet(int, char**);
int mainRobot(int, char**);
int mainUnProject(int, char**);
int mainSmooth(int, char**);
int mainLight(int, char**);
int mainMoveLight(int, char**);
int mainMaterial(int, char**);
int mainColorMat(int, char**);

// Unidade II
int mainAlpha(int, char**);
int mainAlpha3D(int, char**);
int mainAARGB(int, char**);
int mainAAIndex(int, char**);
int mainFog(int, char**);
int mainFogIndex(int, char**);
int mainPolyOff(int, char**);
int mainTorus(int, char**);
int mainList(int, char**);
int mainStroke(int, char**);
int mainDrawf(int, char**);
int mainFont(int, char**);
int mainImage(int, char**);
int mainChecker(int, char**);
int mainTexSub(int, char**);
int mainMipMap(int, char**);
int mainTexBind(int, char**);
int mainTexGen(int, char**);
int mainStencil(int, char**);
int mainDof(int, char**);

// Unidade III
int mainTess(int, char**);
int mainQuadric(int, char**);
int mainBezCurve(int, char**);
int mainBezSurf(int, char**);
int mainBezMesh(int, char**);
int mainTextureSurf(int, char**);
int mainSurface(int, char**);
int mainPickSquare(int, char**);
int mainTrim(int, char**);
int mainSelect(int, char**);
int mainPickDepth(int, char**);
int mainFeedback(int, char**);

int mainVortex(int, char**);

// Funções
// Unidade I
void displayChunkOpenGL(void);
void displayHello(void);
void displayDouble(void);
void displayLines(void);
void displayPolys(void);
void displayVarray(void);
void displayMVArray(void);
void displayCube(void);
void displayModel(void);
void displayClip(void);
void displayPlanet(void);
void displayRobot(void);
void displayUnProject(void);
void displaySmooth(void);
void displayLight(void);
void displayMoveLight(void);
void displayMaterial(void);
void displayColorMat(void);

// Unidade II
void displayAlpha(void);
void displayAlpha3D(void);
void displayAARGB(void);
void displayAAIndex(void);
void displayFog(void);
void displayFogIndex(void);
void displayPolyOff(void);
void displayTorus(void);
void displayList(void);
void displayStroke(void);
void displayDrawf(void);
void displayFont(void);
void displayImage(void);
void displayChecker(void);
void displayTexSub(void);
void displayMipMap(void);
void displayTexBind(void);
void displayTexGen(void);
void displayStencil(void);
void displayDof(void);

// Unidade III
void displayTess(void);
void displayQuadric(void);
void displayBezCurve(void);
void displayBezSurf(void);
void displayBezMesh(void);
void displayTextureSurf(void);
void displaySurface(void);
void displayPickSquare(void);
void displayTrim(void);
void displaySelect(void);
void displayPickDepth(void);
void displayFeedback(void);

#endif /* SRC_EXAMPLES_EXAMPLES_H_ */

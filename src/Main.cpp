/*
 * Main.cpp
 *
 *  Created on: 03/02/2016
 *      Author: hugo
 */
#include <iostream>
#include <random>
#include <cstring>

#include "Examples/examples.h"
#include "Exemplos/Exemplos.h"
#include "TrabalhoUnidI/TrabalhoUnidI.h"
#include "TrabalhoUnidII/TrabalhoUnidII.h"

using namespace std;

typedef int (*PFunc)(int, char**); /* O tipo PFunc é ponteiro p/fção void */

enum Implementacoes {
	// Unidade I
	// Exercícios
	AULA01,
	MOUSE,

	// Exemplo (Professor Leandro Souza)
	EXEMPLOCALLBACKS,

	// Exemplos (Manssour)
	PRIMEIROPROGRAMA,
	MENU = 7,

	// Examples (redbook)

	// Trabalho I - Unidade I
	// Questão do Quadrado (Questão 2 - Parte 1)
	QUESTAOQUADRADO = 28,

	// Questão da Rasterização (Questão 1 - Parte 2)
	LINHASIMPLES,
	LINHAINCREMENTAL,
	LINHABRESENHAM,
	CIRCULOEQUACAO,
	CIRCULOCOORDPOLAR,
	CIRCULOBRESENHAM,
	PARABOLAEQUACAO,
	PARABOLAINCREMENTAL,
	EXPOENTEINCREMENTAL,

	// Questão do Menu (Questão 2 - Parte 2)
	QUESTAOMENU,

	// Questão das Transformações (Questão 3 - Parte 2)
	TRANSFORMACOES,

	// Questão do Quadrado (Questão 4 - Parte 2)
	PROTECAOTELA,
	// Fim da Unidade I

	// Unidade II
	// Examples (redbook)

	// Fim da Unidade II

	// Trabalho 2 - Unidade II
	PLY = 61,
	MALHA,

	// Unidade III
	// Examples (redbook)
	// Fim da Unidade III

	// Adicionais
	VORTEX = 75,

	NUM_IMPLEMENTACOES
};

int main(int argc, char **argv) {
	PFunc ptrf[] = {
			// Unidade I
			//	Exercícios
			mainAula01, mainMouse,

			//	Exemplo (Professor Leandro Souza)
			mainExemploCallbacks,

			// Exemplos (Manssour)
			mainPrimeiroPrograma, mainQuadrado, mainAnima, mainInteracao,
			mainMenu, mainTeaPot3D, mainIluminacao,

			// Examples (redbook)
			mainChunkOpenGL, mainHello, mainDouble, mainLines, mainPolys,
			mainVarray, mainMVArray, mainCube, mainModel, mainClip, mainPlanet,
			mainRobot, mainUnProject, mainSmooth, mainLight, mainMoveLight,
			mainMaterial, mainColorMat,

			// Trabalho I - Unidade I
			// Questão do Quadrado (Questão 2 - Parte 1)
			mainQuestaoQuadrado,

			// Questão da Rasterização (Questão 1 - Parte 2)
			mainLinhaSimples, mainLinhaIncremental, mainLinhaBresenham,
			mainCirculoEquacao, mainCirculoCoordPolar, mainCirculoBresenham,
			mainParabolaEquacao, mainParabolaIncremental,
			mainExpoenteIncremental,

			// Questão do Menu (Questão 2 - Parte 2)
			mainQuestaoMenu,

			// Questão das Transformações (Questão 3 - Parte 2)
			mainTransformacoes,

			// Questão do Quadrado (Questão 4 - Parte 2)
			mainProtecaoTela,
			// Fim da Unidade I

			// Unidade II
			// Examples (redbook)
			mainAlpha, mainAlpha3D, mainAARGB, mainAAIndex, mainFog,
			mainFogIndex, mainPolyOff, mainTorus, mainList, mainStroke,
			mainDrawf, mainFont, mainImage, mainChecker, mainTexSub, mainMipMap,
			mainTexBind, mainTexGen,
			mainStencil, // ???
			mainDof,
			// Fim da Unidade II

			// Trabalho 2 - Unidade II
			mainPly, mainMalha,

			// Unidade III
			// Examples (redbook)
			mainTess, mainQuadric, mainBezCurve, mainBezSurf, mainBezMesh,
			mainTextureSurf, mainSurface, mainPickSquare, mainTrim, mainSelect,
			mainPickDepth, mainFeedback, // ???
			// Fim da Unidade III

			//	Adicionais
			mainVortex };

	char *menu[] = {
			// Unidade I
			//	Exercícios
			"Aula01", "Mouse",

			//	Exemplo (Professor Leandro Souza)
			"ExemploCallbacks",

			// Exemplos (Manssour)
			"PrimeiroPrograma", "Quadrado", "Anima", "Interacao", "Menu",
			"TeaPot3D", "Iluminacao",

			// Examples (redbook)
			"ChunkOpenGL", "Hello", "Double", "Lines", "Polys", "Varray",
			"MVArray", "Cube", "Model", "Clip", "Planet", "Robot", "UnProject",
			"Smooth", "Light", "MoveLight", "Material", "ColorMat",

			// Trabalho I - Unidade I
			// Questão do Quadrado (Questão 2 - Parte 1)
			"QuestaoQuadrado",

			// Questão da Rasterização (Questão 1 - Parte 2)
			"LinhaSimples", "LinhaIncremental", "LinhaBresenham",
			"CirculoEquacao", "CirculoCoordPolar", "CirculoBresenham",
			"ParabolaEquacao", "ParabolaIncremental", "ExpoenteIncremental",

			// Questão do Menu (Questão 2 - Parte 2)
			"QuestaoMenu",

			// Questão das Transformações (Questão 3 - Parte 2)
			"Transformacoes",

			// Questão do Quadrado (Questão 4 - Parte 2)
			"ProtecaoTela",
			// Fim da Unidade I

			// Unidade II
			// Examples (redbook)
			"Alpha", "Alpha3D", "AARGB", "AAIndex", "Fog", "FogIndex",
			"PolyOff", "Torus", "List", "Stroke", "Drawf", "Font", "Image",
			"Checker", "TexSub", "MipMap", "TexBind", "TexGen", "Stencil",
			"Dof",
			// Fim da Unidade II

			// Trabalho 2 - Unidade II
			"Ply", "Malha",

			// Unidade III
			// Examples (redbook)
			"Tess", "Quadric", "BezCurve", "BezSurf", "BezMesh", "TextureSurf",
			"Surface", "PickSquare", "Trim", "Select", "PickDepth", "Feedback",
			// Fim da Unidade III

			//	Adicionais
			"Vortex" };

	cout << "Hello World!!" << endl;
	cout << "Hello OpenGL!" << endl;

	if (argc > 1) {
		int i;
		cout << "Executando " << argv[1] << "..." << endl;
		for (i = 0; i < NUM_IMPLEMENTACOES; ++i) {
			if (strcmp(argv[1], menu[i]) == 0) {
				(*ptrf[i])(argc, argv);
				break;
			}
		}
		if (strcmp(argv[1], "help") == 0) {
			for (int j = 0; j < NUM_IMPLEMENTACOES; ++j) {
				cout << menu[j] << "\t";
			}
			cout << endl;
		} else if (i == NUM_IMPLEMENTACOES)
			cout << "Opção não encontrada." << endl;
	} else
		(*ptrf[MALHA])(argc, argv);

// Unidade I
//	Exercícios
//	mainAula01(argc, argv);
//	mainMouse(argc, argv);

//	Exemplo (Professor Leandro Souza)
//	mainExemploCallbacks(argc, argv);

// Exemplos (Manssour)
//	mainPrimeiroPrograma(argc, argv);
//	mainQuadrado(argc, argv);
//	mainAnima(argc, argv);
//	mainInteracao(argc, argv);
//	mainMenu(argc, argv);
//	mainTeaPot3D(argc, argv);
//	mainIluminacao(argc, argv);

// Examples (redbook)
//	mainChunkOpenGL(argc, argv);
//	mainHello(argc, argv);
//	mainDouble(argc, argv);
//	mainLines(argc, argv);
//	mainPolys(argc, argv);
//	mainVarray(argc, argv);
//	mainMVArray(argc, argv);
//	mainCube(argc, argv);
//	mainModel(argc, argv);
//	mainClip(argc, argv);
//	mainPlanet(argc, argv);
//	mainRobot(argc, argv);
//	mainUnProject(argc, argv);
//	mainSmooth(argc, argv);
//	mainLight(argc, argv);
//	mainMoveLight(argc, argv);
//	mainMaterial(argc, argv);
//	mainColorMat(argc, argv);

// Trabalho I - Unidade I
// Questão do Quadrado (Questão 2 - Parte 1)
//	mainQuestaoQuadrado(argc, argv);

// Questão da Rasterização (Questão 1 - Parte 2)
//	mainLinhaSimples(argc, argv);
//	mainLinhaIncremental(argc, argv);
//	mainLinhaBresenham(argc, argv);
//	mainCirculoEquacao(argc, argv);
//	mainCirculoCoordPolar(argc, argv);
//	mainCirculoBresenham(argc, argv);
//	mainParabolaEquacao(argc, argv);
//	mainParabolaIncremental(argc, argv);
//	mainExpoenteIncremental(argc, argv);

// Questão do Menu (Questão 2 - Parte 2)
//	mainQuestaoMenu(argc, argv);

// Questão das Transformações (Questão 3 - Parte 2)
//	mainTransformacoes(argc, argv);

// Questão do Quadrado (Questão 4 - Parte 2)
//	mainProtecaoTela(argc, argv);
// Fim da Unidade I

// Unidade II
// Examples (redbook)
//	mainAlpha(argc, argv);
//	mainAlpha3D(argc, argv);
//	mainAARGB(argc, argv);
//	mainAAIndex(argc, argv);
//	mainFog(argc, argv);
//	mainFogIndex(argc, argv);
//	mainPolyOff(argc, argv);
//	mainTorus(argc, argv);
//	mainList(argc, argv);
//	mainStroke(argc, argv);
//	mainDrawf(argc, argv);
//	mainFont(argc, argv);
//	mainImage(argc, argv);
//	mainChecker(argc, argv);
//	mainTexSub(argc, argv);
//	mainMipMap(argc, argv);
//	mainTexBind(argc, argv);
//	mainTexGen(argc, argv);
//	mainStencil(argc, argv); // ???
//	mainDof(argc, argv);
// Fim da Unidade II

// Trabalho 2 - Unidade II
//	mainPly(argc, argv);
//	mainMalha(argc, argv);

// Unidade III
// Examples (redbook)
//	mainTess(argc, argv);
//	mainQuadric(argc, argv);
//	mainBezCurve(argc, argv);
//	mainBezSurf(argc, argv);
//	mainBezMesh(argc, argv);
//	mainTextureSurf(argc, argv);
//	mainSurface(argc, argv);
//	mainPickSquare(argc, argv);
//	mainTrim(argc, argv);
//	mainSelect(argc, argv);
//	mainPickDepth(argc, argv);
//	mainFeedback(argc, argv); // ???
// Fim da Unidade III

//	Adicionais
//	mainVortex(argc, argv);

	return (0);
}

/*
 * GerenciadorFuncoes.cpp
 *
 *  Created on: 11/05/2016
 *      Author: hugo
 */

#include <cstring>
#include "Main.h"

void executarPFunc(int i, int argc, char **argv) {
	PFunc ptrf[] = {
#ifdef __linux__
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

			// Trabalho 3 - Unidade III
			mainBezier,

			//	Adicionais
			mainVortex
#else
			mainMalha

			// Trabalho 3 - Unidade III
			mainBezier,
#endif
		};

	(*ptrf[i])(argc, argv);
}

char *retornarPFunc(int pos) {
	char *menu[] = {
#ifdef __linux__
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
			"Ply",
#endif
			"Malha",

#ifdef __linux__
			// Unidade III
			// Examples (redbook)
			"Tess", "Quadric", "BezCurve", "BezSurf", "BezMesh", "TextureSurf",
			"Surface", "PickSquare", "Trim", "Select", "PickDepth", "Feedback",
			// Fim da Unidade III
			"Bezier",

			//	Adicionais
			"Vortex"
#else
			"Bezier"
#endif
}			;


	return (char *)menu[pos];
}

bool lerPFunc(int i, int argc, char **argv) {

			if( strcmp(argv[1], retornarPFunc(i)) == 0)
			return true;
			else
			return false;
		}


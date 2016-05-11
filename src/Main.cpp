/*
 * Main.cpp
 *
 *  Created on: 03/02/2016
 *      Author: hugo
 */
#include <fstream> // Para a classe de arquivos
#include <iostream> // Para leitura/gravação de arquivos
//#include <random> // Para funções de distribuição
#include <cstring> // Para tratamento de strings
#include <stdlib.h>

#ifdef __linux__
#include <GL/glut.h>
#include "Examples/examples.h"
#include "Exemplos/Exemplos.h"
#include "TrabalhoUnidI/TrabalhoUnidI.h"
#else
#include <gl/glut.h>
#endif
#include "TrabalhoUnidII/TrabalhoUnidII.h"
#include "TrabalhoUnidIII/TrabalhoUnidIII.h"
#include "Main.h"

using namespace std;

int main(int argc, char **argv) {

			cout << "Hello World!" << endl;

#ifdef __linux__
			cout << "Hello Linux!!" << endl;
#endif

			cout << "Hello OpenGL!!!" << endl;

			if (argc > 1) {
				int i;
				cout << "Executando " << argv[1] << "..." << endl;
				for (i = 0; i < NUM_IMPLEMENTACOES; ++i) {
					if (lerPFunc(i, argc, argv)) {
						executarPFunc(i, argc, argv);
						break;
					}
				}
				if (strcmp(argv[1], "help") == 0) {
					for (int j = 0; j < NUM_IMPLEMENTACOES; ++j) {
						cout << retornarPFunc(j) << "\t";
					}
					cout << endl;
				} else if (i == NUM_IMPLEMENTACOES)
				cout << "Opção não encontrada." << endl;
			} else
			executarPFunc((VORTEX-1), argc, argv);

#ifdef __linux__
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
#endif

			return (0);
		}

/*
 * Main.cpp
 *
 *  Created on: 03/02/2016
 *      Author: hugo
 */
#include <iostream>
#include <random>

#include "Examples/examples.h"
#include "Exemplos/Exemplos.h"
#include "TrabalhoUnidI/Quadrado/Quadrado.h"

int main(int argc, char **argv) {
	  const int nrolls = 10000; // number of experiments
	  const int nstars = 95;    // maximum number of stars to distribute

	  std::default_random_engine generator;
	  std::uniform_int_distribution<int> distribution(0,9);

	  int p[10]={};

	  for (int i=0; i<nrolls; ++i) {
	    int number = distribution(generator);
	    ++p[number];
	  }

	  std::cout << "uniform_int_distribution (0,9):" << std::endl;
	  for (int i=0; i<10; ++i)
	    std::cout << i << ": " << std::string(p[i]*nstars/nrolls,'*') << std::endl;

	std::cout << "Hello World!!" << std::endl;
	std::cout << "Hello OpenGL!" << std::endl;

//	mainExemploCallbacks(argc, argv);
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
	mainColorMat(argc, argv);

//	mainPrimeiroPrograma(argc, argv);
//	mainQuadrado(argc, argv);
//	mainAnima(argc, argv);
//	mainInteracao(argc, argv);
//	mainMenu(argc, argv);
//	mainTeaPot3D(argc, argv);
//	mainIluminacao(argc, argv);
//	mainMouse(argc, argv);

//	mainVortex(argc, argv);

	return (0);
}

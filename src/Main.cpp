/*
 * Main.cpp
 *
 *  Created on: 03/02/2016
 *      Author: hugo
 */
#include <iostream>
#include <random>

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

//	mainPrimeiroPrograma(argc, argv);
//	mainQuadrado(argc, argv);
//	mainAnima(argc, argv);
//	mainInteracao(argc, argv);
//	mainMenu(argc, argv);
//	mainTeaPot3D(argc, argv);
	mainIluminacao(argc, argv);
//	mainMouse(argc, argv);

	return (0);
}

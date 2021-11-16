#include "FunctionApproximation_PSO.h"
#include "SBPolygon_SimulatedAnnealing.h"
#include "TravellingSalesman_TABU.h"
#include <iostream>

int main()
{
	//FunctionApproximation_PSO PSO(0.7f, 0.4f, 0.5f);
	//PSO.loadKnownValuesFromFile("../Input/FuncAppr2.txt");
	//PSO.ParticleSwarmOptimization();

	//https://www.matheretter.de/calc/geodrafter pontok kimutatása Logból
	//SBPolygon_SimulatedAnnealing SimAn;
	//SimAn.loadPointsFromFile("../Input/Points.txt");
	//SimAn.SimulatedAnnealing();

	//https://www.matheretter.de/calc/geodrafter útvonal kimutatása Logból
	//TravellingSalesman_TABU TABU;  //inkább hegymászó, mint TABU
	//TABU.loadTownsFromFile("../Input/Towns.txt");
	//TABU.TravellingSalesman();

	return 0;
}

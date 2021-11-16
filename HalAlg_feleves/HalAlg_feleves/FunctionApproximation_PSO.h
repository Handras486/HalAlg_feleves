#pragma once

#include "FunctionApproximation.h"
#include <array>
#include <string>

using namespace std;

const int POP_SIZE = 1000;
const int CYCLE_COUNT = 100;

class Particle
{

public:
	Particle()
	{
		InitializeParticle();
	}

private:
	array<float, 5> coefficients;
	array<float, 5> velocities;
	array<float, 5>local_opt;

	void InitializeParticle();
	void AddVelocity();

	friend class FunctionApproximation_PSO;
};

class FunctionApproximation_PSO : public FunctionApproximation
{
	//jelenlegi függvény: a*(x-b)^3 + c*(x-d)^2 + e
	//FuncAppr1: a=0,5 b=3 c=4,5 d=3, e=2
	//FuncAppr2: a=1   b=2 c=3   d=4, e=5

protected:
	static int counter;

	array<Particle*, POP_SIZE> population = array<Particle*, POP_SIZE>();
	array<float, 5>global_opt =  array<float,5>();
	float vel_strength;
	float local_opt_pull;
	float global_opt_pull;

	void InitializePopulation();
	bool StopCondition();
	void Evaluation();
	void CalculateVelocity();

	void PSOLogger();

public:
	FunctionApproximation_PSO(float vel_strength, float local_opt_pull, float global_opt_pull)
	{
		this->vel_strength = vel_strength;
		this->local_opt_pull = local_opt_pull;
		this->global_opt_pull = global_opt_pull;
	}

	void ParticleSwarmOptimization();

};


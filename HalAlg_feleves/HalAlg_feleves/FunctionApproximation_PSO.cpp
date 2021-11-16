#include "FunctionApproximation_PSO.h"
#include "RandomGenerator.h"

int FunctionApproximation_PSO::counter = 0;

void FunctionApproximation_PSO::InitializePopulation()
{
	for (size_t i = 0; i < global_opt.size(); i++)
	{
		global_opt[i] = randomUniform(0.0f, 6.0f);;
	}

	for (size_t i = 0; i < population.size(); i++)
	{
		population[i] = new Particle();
	}
}

bool FunctionApproximation_PSO::StopCondition()
{
	counter++;

	if (counter > CYCLE_COUNT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FunctionApproximation_PSO::Evaluation()
{
	for (size_t i = 0; i < population.size(); i++)
	{
		if (objective((*population[i]).coefficients) < objective((*population[i]).local_opt))    // fitness -> coefficent <> local opt
		{

			for (size_t j = 0; j < (*population[i]).coefficients.size(); j++)             
			{
				(*population[i]).local_opt[j] = (*population[i]).coefficients[j];     
			}

			if (objective((*population[i]).coefficients) < objective(global_opt))                // fitness -> coefficent <> global opt
			{

				for (size_t k = 0; k < (*population[i]).coefficients.size(); k++)
				{
					global_opt[k] = (*population[i]).coefficients[k];
				}
			}
		}
	}
}

void FunctionApproximation_PSO::CalculateVelocity()
{
	for (size_t i = 0; i < population.size(); i++)
	{
		for (size_t j = 0; j < (*population[i]).coefficients.size(); j++)
		{
			float rnd_loc = randomUniform(0.0f, 1.0f);
			float rnd_glob = randomUniform(0.0f, 1.0f);
			(*population[i]).velocities[j] =
				vel_strength * (*population[i]).velocities[j] +
				global_opt_pull * rnd_glob * (global_opt[j] - (*population[i]).coefficients[j]) +
				local_opt_pull * rnd_loc * ((*population[i]).local_opt[j] - (*population[i]).coefficients[j]);
		}
	}
}

void FunctionApproximation_PSO::PSOLogger()
{
	printf("%d.ciklus , globalis optimum: %f \n", counter, objective(global_opt));
	printf("koefficiensek: %f, %f, %f, %f, %f\n\n", global_opt[0], global_opt[1], global_opt[2], global_opt[3], global_opt[4]);
}

void FunctionApproximation_PSO::ParticleSwarmOptimization()
{

	InitializePopulation();
	Evaluation();
	while (!StopCondition())
	{
		CalculateVelocity();

		for (size_t i = 0; i < population.size(); i++)
		{
			(*population[i]).AddVelocity();
		}
		Evaluation();

		PSOLogger();
	}
}

void Particle::InitializeParticle()
{
	for (size_t i = 0; i < coefficients.size(); i++)
	{
		coefficients[i] = randomUniform(0.0f, 6.0f);
		local_opt[i] = randomUniform(0.0f, 6.0f);
		velocities[i] = randomUniform(-0.5f, 0.5f);
	}
}

void Particle::AddVelocity()
{
	for (size_t i = 0; i < coefficients.size(); i++)
	{
		coefficients[i]+= velocities[i];
	}
}

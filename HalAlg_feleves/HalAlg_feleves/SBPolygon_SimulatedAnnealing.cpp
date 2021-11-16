#include "SBPolygon_SimulatedAnnealing.h"
#include "RandomGenerator.h"
#include <math.h>
#include <algorithm>


void SBPolygon_SimulatedAnnealing::SimAnLogger()
{
	printf("%d.ciklus, kerulet: %f \n", time, cur_obj);
}

void SBPolygon_SimulatedAnnealing::InitializeBoundaryPoints()
{
	//Középpont kiszámítása
	for (size_t i = 0; i < BOUNDARY_POINT_COUNT; i++)
	{
		centroid.x += points[i].x;
		centroid.y += points[i].y;
	}
	centroid.x = centroid.x / BOUNDARY_POINT_COUNT;
	centroid.y = centroid.y / BOUNDARY_POINT_COUNT;

	//Körhatár sugarának kiszámítása
	for (size_t i = 0; i < BOUNDARY_POINT_COUNT; i++)
	{
		float distance = sqrtf(powf(points[i].x - centroid.x, 2) + powf(points[i].y - centroid.y, 2));
		if (distance > boundary_radius)
		{
			boundary_radius = distance;
		}
	}
	boundary_radius *= 1.5;

	//Körhatár pontok kiszámítása (amíg nem lesz minden pont a körhatáron belül)
	do
	{
		boundary_points.clear();
		boundary_point_angles.clear();

		for (size_t i = 0; i < BOUNDARY_POINT_COUNT; i++)
		{
			boundary_point_angles.push_back(randomUniform(0.0f, 6.283185307179f));
		}
		sort(boundary_point_angles.begin(), boundary_point_angles.end(), greater<float>());

		for (size_t i = 0; i < BOUNDARY_POINT_COUNT; i++)
		{
			Point temp;
			temp.x = centroid.x + cosf(boundary_point_angles[i]) * boundary_radius;
			temp.y = centroid.y + sinf(boundary_point_angles[i]) * boundary_radius;
			boundary_points.push_back(temp);
		}

	} while (constraint(boundary_points) != 0);

	savePointsToFile("SBPolygon_Start.txt", points, boundary_points, centroid);
}

bool SBPolygon_SimulatedAnnealing::StopCondition()
{
	if (time > 3000 && (old_obj - cur_obj) < 0.0000001f)
	{
		counter++;
		if (counter > 20)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		counter = 0;
		return false;
	}
}

void SBPolygon_SimulatedAnnealing::Temperature()
{
	if (time == 0)
	{
		Temp = Temp_max;
		Temp *= (1 - Temp_pull);
	}
	else
	{
		Temp *= (1 - Temp_pull);
	}
}

void SBPolygon_SimulatedAnnealing::CalculateRandomPoint(size_t i)
{
	Point temp;
	do
	{
		float angle = randomUniform(0.0f, 6.283185307179f);
		temp.x = boundary_points[i].x + cosf(angle) * jump_distance;
		temp.y = boundary_points[i].y + sinf(angle) * jump_distance;
		boundary_points_temp[i] = temp;

	} while (constraint(boundary_points_temp) != 0);
}

void SBPolygon_SimulatedAnnealing::SimulatedAnnealing()
{
	InitializeBoundaryPoints();

	cur_obj = objective(boundary_points);
	opt_obj = cur_obj;
	time = 0;
	while (!StopCondition())
	{
		old_obj = cur_obj;
		time += 1;
		for (size_t i = 0; i < BOUNDARY_POINT_COUNT; i++)
		{
			boundary_points_temp = boundary_points;
			CalculateRandomPoint(i);
			energy_lvl = objective(boundary_points_temp) - cur_obj;
			if (energy_lvl < 0)
			{
				boundary_points[i] = boundary_points_temp[i];
				cur_obj = objective(boundary_points);
				if (cur_obj < opt_obj)
				{
					opt_obj = cur_obj;
				}
			}
			else
			{
				Temperature();
				Prob = expf(-energy_lvl / (Temp * Boltzmann_const));
				if (randomUniform(0.0f, 1.0f) < Prob)
				{
					boundary_points[i] = boundary_points_temp[i];
					cur_obj = objective(boundary_points);
				}
			}
		}

		SimAnLogger();
	}

	savePointsToFile("SBPolygon_End.txt", points, boundary_points, centroid);
}

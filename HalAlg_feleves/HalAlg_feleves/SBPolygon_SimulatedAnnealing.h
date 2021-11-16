#pragma once
#include "SmallestBoundaryPolygon.h"
#include <string>
#include <vector>

using namespace std;

const int BOUNDARY_POINT_COUNT = 9;

class SBPolygon_SimulatedAnnealing : public SmallestBoundaryPolygon
{

protected:
	vector<Point> boundary_points;
	vector<float> boundary_point_angles;
	float boundary_radius = 0;
	Point centroid = Point();

	vector<Point> boundary_points_temp;
	int time = 0;
	int counter = 0;
	float old_obj = FLT_MAX;
	float cur_obj = 0;
	float opt_obj = 0;
	float energy_lvl = 0;
	float Temp = 0;
	float Prob = 0;

	float jump_distance = 0.6f;
	float Boltzmann_const = 0.01f;
	float Temp_max = 150;
	float Temp_pull = 0.0001f;

	void SimAnLogger();
	void InitializeBoundaryPoints();
	bool StopCondition();
	void Temperature();
	void CalculateRandomPoint(size_t i);

public:
	SBPolygon_SimulatedAnnealing() = default;
	SBPolygon_SimulatedAnnealing(float jump_distance, float Boltzmann_const, float Temp_max, float Temp_pull)
	{
		this->jump_distance = jump_distance;
		this->Boltzmann_const = Boltzmann_const;
		this->Temp_max = Temp_max;
		this->Temp_pull = Temp_pull;
	}

	void SimulatedAnnealing();

};


#include "TravellingSalesman_TABU.h"
#include "RandomGenerator.h"
#include <algorithm>



void TravellingSalesman_TABU::SetTABUBarrier()
{
	TABU_list.clear();
}

bool TravellingSalesman_TABU::StopCondition()
{

	if (old_opt_obj_value == opt_obj_value)
	{
		stop_counter++;
		if (stop_counter > 100)
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
		stop_counter = 0;
		old_opt_obj_value = opt_obj_value;
		return false;
	}
}

bool TravellingSalesman_TABU::IsTABU(Town& p)
{
	if (std::find(TABU_list.begin(), TABU_list.end(), p) != TABU_list.end()) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void TravellingSalesman_TABU::AddTABU(Town& p)
{
	TABU_list.push_back(p);
}

void TravellingSalesman_TABU::PurgeTABU()
{
	if (TABU_list.size() == TABU_list.max_size())
	{
		TABU_list.pop_front();
	}
}

void TravellingSalesman_TABU::AddClosestTown(Town& p)
{
	float mindistance = FLT_MAX;
	size_t closestTownID = -1;

	for (size_t i = 0; i < temp_towns.size(); i++)
	{
		float temp = sqrtf(powf(p.x - temp_towns[i].x, 2) + powf(p.y - temp_towns[i].y, 2) * 1.0f);

		if (temp != 0 && temp < mindistance)
		{
			mindistance = temp;
			closestTownID = i;
		}
	}

	cur_obj.push_back(temp_towns[closestTownID]);
	temp_towns.erase(temp_towns.begin() + closestTownID);
}

void TravellingSalesman_TABU::TravellingSalesman()
{
	opt_obj_value = FLT_MAX;
	old_opt_obj_value = old_opt_obj_value;

	while (!StopCondition())
	{
		temp_towns = towns;
		counter++;

		startingTownID = randomUniform(0, temp_towns.size() - 1);
		cur_obj.push_back(temp_towns[startingTownID]);
		temp_towns.erase(temp_towns.begin() + startingTownID);

		SetTABUBarrier();
		stuck = false;

		while (!stuck && !IsTABU(cur_obj.back()))
		{
			AddTABU(cur_obj.back());
			PurgeTABU();
			AddClosestTown(cur_obj.back());    

			if (cur_obj.size() == towns.size())
			{
				if (opt_obj.empty() || objective(cur_obj) < opt_obj_value)
				{
					opt_obj = cur_obj;
					opt_obj_value = objective(opt_obj);
				}
				stuck = true;
			}
		}
		
		cur_obj.clear();
		printf("%d. ciklus, jelenlegi optimalis ut hossza: %f \n", counter, opt_obj_value);
	}

	saveTownsToFile("OptimalRoute.txt",opt_obj);

}

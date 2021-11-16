#pragma once
#include "TravellingSalesman.h"
#include <vector>
#include <deque>

using namespace std;

class TravellingSalesman_TABU : public TravellingSalesmanProblem
{


protected:
	deque<Town> TABU_list;

	vector<Town> opt_obj;
	vector<Town> cur_obj;
	vector<Town> temp_towns;
	float opt_obj_value;
	bool stuck = false;
	int stop_counter = 0;
	int counter = 0;
	int startingTownID;
	float old_opt_obj_value;

	void SetTABUBarrier();
	bool StopCondition();
	bool IsTABU(Town& p);
	void AddTABU(Town& p);
	void PurgeTABU();
	void AddClosestTown(Town& p);

public:
	void TravellingSalesman();

};


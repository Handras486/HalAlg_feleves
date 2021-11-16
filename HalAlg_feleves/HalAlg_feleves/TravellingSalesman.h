#pragma once
#include <vector>
#include <string>

class Town
{
public:
	float x;
	float y;

	Town() = default;
	Town(float x, float y)
	{
		this->x = x;
		this->y = y;

	}

	friend bool operator==(const Town& lhs, const Town& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
};

class TravellingSalesmanProblem
{
protected:
	std::vector<Town> towns;
	float objective(std::vector<Town> solution);
public:
	void loadTownsFromFile(std::string fileName);
	void saveTownsToFile(std::string fileName, std::vector<Town> townVector);
};

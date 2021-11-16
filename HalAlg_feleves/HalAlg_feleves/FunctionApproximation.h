#pragma once
#include <array>
#include <vector>
#include <string>

class ValuePair
{
public:
	float input;
	float output;
};

class FunctionApproximation
{
protected:
	std::vector<ValuePair> known_values;

	float objective(std::array<float, 5> coefficients);
public:
	void loadKnownValuesFromFile(std::string fileName);
};

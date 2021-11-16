#include "FunctionApproximation.h"
#include <fstream>

using namespace std;

//
// Basic IO
//
void FunctionApproximation::loadKnownValuesFromFile(string fileName) {
	ifstream fvalues(fileName);
	while (!fvalues.eof()) {
		ValuePair valuepair;
		fvalues >> valuepair.input;
		fvalues >> valuepair.output;
		known_values.push_back(valuepair);
	};
	fvalues.close();
}

//
// Objective functions
//
float FunctionApproximation::objective(std::array<float, 5> coefficients) {
	float sum_diff = 0;
	for (auto valuepair : known_values) {
		float x = valuepair.input;
		float y = coefficients[0] * pow(x - coefficients[1], 3) +
			coefficients[2] * pow(x - coefficients[3], 2) +
			coefficients[4];
		float diff = (float)pow(y - valuepair.output, 2);
		sum_diff += diff;
	}
	return sum_diff;
}
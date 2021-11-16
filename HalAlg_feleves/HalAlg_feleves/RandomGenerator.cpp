#include "RandomGenerator.h"
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());

// random float between [min, max[
float randomUniform(float min, float max) {
	uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

// random size_t between [min, max]
int randomUniform(size_t min, size_t max) {
	uniform_real_distribution<float> dis((float)min, (float)max + 1);
	return (size_t)dis(gen);
}
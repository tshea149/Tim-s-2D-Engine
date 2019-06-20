#include "RandomNumberGenerator.h"

//template<typename T>
RandomNumberGenerator::RandomNumberGenerator(uint64_t seed)
{
	generator = std::mt19937_64(seed);
}

//template<typename T>
uint64_t RandomNumberGenerator::getNumBetween(uint64_t low, uint64_t high)
{
	std::uniform_int_distribution<>distribution = std::uniform_int_distribution<>(low, high);
	return distribution(generator);
}

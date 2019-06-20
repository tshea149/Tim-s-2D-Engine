/* Author: Tim */
#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <random>
#include <stdint.h>

// uses Mersenne Twister 19937 pseudo-random generator

//template <typename T>
class RandomNumberGenerator
{
private:
	std::mt19937_64 generator;

public:
	RandomNumberGenerator() = delete;
	RandomNumberGenerator(uint64_t seed);

	uint64_t getNumBetween(uint64_t low, uint64_t high);

};

#endif // !RANDOMNUMBERGENERATOR_H
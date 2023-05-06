#include "ipch.h"
#include "Randomizer.h"
#include <random>

namespace Rapier 
{

	static std::random_device l_RandomDevice;
	static std::mt19937_64 l_Engine64(l_RandomDevice());
	static std::uniform_int_distribution<uint64_t> l_UniformDistribution64;

	static std::mt19937 l_Engine32(l_RandomDevice());
	static std::uniform_int_distribution<uint32_t> l_UniformDistribution32;

	uint32_t Randomizer::RandomUINT32(uint32_t minimum, uint32_t maximum)
	{
		return l_UniformDistribution32(l_Engine32);
	}

	uint64_t Randomizer::RandomUINT64(uint64_t minimum, uint64_t maximum) 
	{
		return l_UniformDistribution64(l_Engine64);
	}
}
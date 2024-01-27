#include "math.hpp"

namespace math
{
	float getRandomFloat(float min, float max)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_real_distribution dist(min, max);

		return dist(rng);
	}
}
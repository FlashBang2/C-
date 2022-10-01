#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

#include "math.h"


struct Solution
{
	double rank, x, y, z;
	void fitness()
	{
		double ans = (6 * x + -y + std::pow(z, 200)) - 25;

		rank = (ans == 0) ? 999999 : std::abs(1 / ans);
	}
};

int main()
{
	// Create initial random solutions

	std::random_device device;
	std::uniform_real_distribution<double> unif(-100, 100);
	std::vector<Solution> solutions;

	const int iterations = 100000;
	for (int iteration = 0; iteration < iterations; iteration++)
		solutions.push_back(Solution{
			0,
			unif(device),
			unif(device),
			unif(device)
			});

	while (true)
	{

		// Run our fitness function

		for (auto& solution : solutions) { solution.fitness(); }

		// Sort our solutions by rank

		std::sort(solutions.begin(), solutions.end(),
			[](const auto& lhs, const auto& rhs) {
				return lhs.rank > rhs.rank;
			});

		//Print top solutions

		std::for_each(
			solutions.begin(),
			solutions.begin() + 10, [](const auto& solution) {
				std::cout << std::fixed
					<< "Rank" << static_cast<int>(solution.rank)
					<< "\n x:" << solution.x << " y:" << solution.y << " z:" << solution.z
					<< " \n";
			});

		//Take top solutions

		const int SAMPLE_SIZE = 1000;
		std::vector<Solution> sample;
		std::copy(
			solutions.begin(),
			solutions.begin() + SAMPLE_SIZE,
			std::back_inserter(sample)
		);
		solutions.clear();

		// Mutate the top solutions

		std::uniform_real_distribution<double> m(0.99, 1.01);
		std::for_each(sample.begin(), sample.end(), [&](auto& solution) {
			solution.x *= m(device);
			solution.y *= m(device);
			solution.z *= m(device);
			});

		// Cross over

		std::uniform_int_distribution<int> cross(0, SAMPLE_SIZE - 1);
		for (int iteration = 0; iteration < iterations; iteration++)
		{
			solutions.push_back(Solution{
				0,
				sample[cross(device)].x,
				sample[cross(device)].y,
				sample[cross(device)].z,
				});
		}
	}
}
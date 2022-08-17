#pragma once
#include "IChunkFactory.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
class PerlinNoise;

class PerlinNoiseChunkFactory : public IChunkFactory
{
	std::shared_ptr<PerlinNoise> _perlinNoise;
	
	std::shared_ptr<IChunk> chunk;
	int _octaves;
	double _persistence;
	std::default_random_engine generator;
public:
	PerlinNoiseChunkFactory(unsigned int octaves, double persistence);
	PerlinNoiseChunkFactory(std::shared_ptr<PerlinNoise>& perlinNoise, unsigned int octaves, double persistence);
	virtual ~PerlinNoiseChunkFactory();

	std::shared_ptr<IChunk> construct(const IChunkManager* chunkManager, unsigned chunkX, unsigned chunkY, unsigned chunkZ) override;

	void random_remove();
};


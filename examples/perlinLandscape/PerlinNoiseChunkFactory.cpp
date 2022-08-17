#include "PerlinNoiseChunkFactory.h"
#include "PerlinNoise.h"
#include "Chunk.h"
#include "IChunkManager.h"
#include "Voxels.h"



PerlinNoiseChunkFactory::PerlinNoiseChunkFactory(unsigned int octaves,
	double persistence) : _perlinNoise(std::make_shared<PerlinNoise>()), _octaves(octaves), _persistence(persistence)
{
	
}

PerlinNoiseChunkFactory::PerlinNoiseChunkFactory(std::shared_ptr<PerlinNoise>& perlinNoise,
	unsigned int octaves,
	double persistence) : _perlinNoise(perlinNoise), _octaves(octaves), _persistence(persistence)
{

}

PerlinNoiseChunkFactory::~PerlinNoiseChunkFactory()
{
}

std::shared_ptr<IChunk> PerlinNoiseChunkFactory::construct(const IChunkManager* chunkManager, unsigned chunkX, unsigned chunkY, unsigned chunkZ)
{
	std::cout << __FUNCTION__ << std::endl;
std::vector<std::shared_ptr<IVoxel>> voxels;	
	unsigned noiseValues[IChunk::Width][IChunk::Height];

	for (unsigned z=0; z < IChunk::Depth; z++)
	{
		unsigned worldZ = chunkZ * IChunk::Depth + z;
		double perlinY = static_cast<double>(worldZ) / static_cast<double>(chunkManager->getDepth() * IChunk::Depth);

		for (unsigned x = 0; x < IChunk::Width; x++)
		{
			unsigned worldX = chunkX * IChunk::Width + x;
			double perlinX = static_cast<double>(worldX) / static_cast<double>(chunkManager->getWidth() * IChunk::Width);

			double noiseValue = _perlinNoise->octavePerlin(perlinX, perlinY, 0.0, _octaves, _persistence);
			unsigned perlinWorldY = static_cast<unsigned>(noiseValue * static_cast<double>(chunkManager->getHeight() * IChunk::Height));
			noiseValues[x][z] = perlinWorldY;
		}
	}

	for (unsigned z=0; z < IChunk::Depth; z++)
	{
		for (unsigned y=0; y < IChunk::Height; y++)
		{
			unsigned worldY = chunkY * IChunk::Height + y;
			
			for (unsigned x=0; x < IChunk::Width; x++)
			{
				unsigned perlinWorldY = noiseValues[x][z];
				if (perlinWorldY > worldY)
				{
					// in theory in this instance we could reuse the voxel however if we want to deform the terrain or
					// take other discrete world effecting actions later we can't do this.
					// there are optimisations planned to allow this kind of virtualisation within the engine.
					std::shared_ptr<IVoxel> voxel;
					if (worldY > 20)
					{
						voxel = std::make_shared<SnowVoxel>();
					}
					else if (worldY > 16)
					{
						voxel = std::make_shared<MountainVoxel>();
					}
					else if (worldY == 15)
					{
						voxel = std::make_shared<WoodVoxel>();
					}
					else
					{
						voxel = std::make_shared<GrassVoxel>();
					}

					voxels.push_back(voxel);
				}
				else
				{
					voxels.push_back(nullptr);
				}
			}
		}
	}

	chunk = std::make_shared<Chunk>(voxels);
	this->chunkManager = chunkManager;
	return chunk;
}




void PerlinNoiseChunkFactory::random_add()
{
	if (chunkManager == nullptr)
	{
		return;
	}

	if (chunk == nullptr)
	{
		return;
	}
	
	std::uniform_int_distribution<int> distribution(0, chunk->getContainerWidthInVoxels()-1);
	auto dice = std::bind(distribution, generator);

	auto x = rand() % chunk->Width;
	auto z = rand() % chunk->Depth;
	auto y = rand() % chunk->Height;
	if(chunk->getVoxel(x,y,z) == nullptr)
	{
			std::cout << "Adding " << x << "\t" << y << "\t"<< z << "\t" << std::endl;
		auto voxel = std::make_shared<WoodVoxel>();
		chunk->getVoxel(x,y,z) = voxel;
		chunk->prepareRenderer();	
	}

}


void PerlinNoiseChunkFactory::random_remove()
{
	if (chunkManager == nullptr)
	{
		return;
	}

	if (chunk == nullptr)
	{
		return;
	}
	
	std::uniform_int_distribution<int> distribution(0, chunk->getContainerWidthInVoxels()-1);
	auto dice = std::bind(distribution, generator);

	auto x = rand() % chunk->Width;
	auto z = rand() % chunk->Depth;
	auto y = rand() % chunk->Height;

	if(chunk->getVoxel(x,y,z))
	{
			std::cout << "Removing " << x << "\t" << y << "\t"<< z << "\t" << std::endl;
		chunk->getVoxel(x,y,z)->setActive(false);
		chunk->tick(30);
		chunk->prepareRenderer();
	}
	//voxels.at(mean)->setActive(false);


}
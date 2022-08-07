//
// Created by Tony on 07/08/2022.
//

#include "Core/Ressource/Terrain/Terrain.h"

namespace Core
{

	std::shared_ptr<Terrain> Terrain::Load(const std::filesystem::path& p_terrainPath)
	{
		JsonObject terrainData = LoadJsonFile(p_terrainPath);
		if (terrainData.empty()) return nullptr;

		auto terrain = std::make_shared<Terrain>();

		terrain->m_chunkWidth = GetParameterFromJsonObject(terrainData, "ChunkWidth", terrain->m_chunkWidth);
		terrain->m_chunkHeight = GetParameterFromJsonObject(terrainData, "ChunkHeight", terrain->m_chunkHeight);

		auto chunks = GetParameterFromJsonObject(terrainData, "Chunks", true, false);
		if (chunks == terrainData) return nullptr;

		for (auto& chunk : chunks)
		{

		}

		return terrain;
	}

	void Terrain::RenderTerrainInCircleArea(std::shared_ptr<CircleArea> p_circleArea)
	{

	}

} // Core

//
// Created by Tony on 07/08/2022.
//

#include "Core/Ressource/Terrain/Chunck.h"

namespace Core
{

	std::shared_ptr<Chunck> Chunck::Load(const std::filesystem::path& p_chunckPath)
	{
		JsonObject chunckData = LoadJsonFile(p_chunckPath);
		if (chunckData.empty()) return nullptr;

		return nullptr;
	}

} // Core

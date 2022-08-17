//
// Created by Tony on 07/08/2022.
//

#include "Client/Ressource/Terrain/Chunck.h"

namespace Client
{

	std::shared_ptr<Chunck> Chunck::Load(const std::filesystem::path& p_chunckPath)
	{
		JsonObject chunckData = LoadJsonFile(p_chunckPath);
		if (chunckData.empty()) return nullptr;

		return nullptr;
	}

} // Client

//
// Created by Tony on 07/08/2022.
//

#ifndef MYVERSE_CHUNCK_H
#define MYVERSE_CHUNCK_H

#include "Utils.h"
#include "JsonUtils.h"

#include "CircleArea.h"

namespace Client
{

	class Terrain
	{
	public:
		Terrain() = default;
		~Terrain() = default;

		static std::shared_ptr<Terrain> Load(const std::filesystem::path& p_terrainPath);

		void RenderTerrainInCircleArea(std::shared_ptr<CircleArea> p_circleArea);

	private:
		float m_chunkWidth = 100.0f;
		float m_chunkHeight = 100.0f;
	};

} // Client

#endif // MYVERSE_CHUNCK_H

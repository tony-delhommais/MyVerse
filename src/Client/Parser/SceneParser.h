//
// Created by Tony on 12/11/2022.
//

#ifndef MYVERSE_SCENE_PARSER_H
#define MYVERSE_SCENE_PARSER_H

#include "Client/Utils/JsonUtils.h"

#include "Client/Builders/SceneBuilder.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

	class SceneParser
	{
	public:
		SceneParser() = default;
		~SceneParser() = default;

	public:
		static bool Serialize(const std::filesystem::path& p_path, std::shared_ptr<Scene> p_scene);
		static JsonObject Serialize(std::shared_ptr<Scene> p_scene);

		static std::shared_ptr<Scene> Parse(const std::filesystem::path& p_path);
		static std::shared_ptr<Scene> Parse(JsonObject& p_data);
	};

} // Client

#endif // MYVERSE_SCENE_PARSER_H
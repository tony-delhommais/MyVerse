//
// Created by Tony on 12/11/2022.
//

#include "Client/Parser/SceneParser.h"

namespace Client
{

	bool SceneParser::Serialize(const std::filesystem::path& p_path, std::shared_ptr<Scene> p_scene)
	{
		JsonObject data = SceneParser::Serialize(p_scene);

		return WriteJsonFile(p_path, data);
	}

	JsonObject SceneParser::Serialize(std::shared_ptr<Scene> p_scene)
	{
		JsonObject sceneData;

		sceneData["Type"] = "Scene";

		sceneData["Name"] = p_scene->GetName();

		//todo parse local entities

		return sceneData;
	}

	std::shared_ptr<Scene> SceneParser::Parse(const std::filesystem::path& p_path)
	{
		JsonObject data = LoadJsonFile(p_path);

		return SceneParser::Parse(data);
	}

	std::shared_ptr<Scene> SceneParser::Parse(JsonObject& p_data)
	{
		// Test if object have a Type Scene
		if (GetParameterFromJsonObject(p_data, "Type", "Null") != "Scene")
		{
#ifdef _DEBUG
			Debug::LogWarning("[SceneParser] Try to parse a Scene, but type is invalid");
#endif
			return nullptr;
		}

		SceneBuilder builder;

		builder.SetName(GetParameterFromJsonObject(p_data, "Name", "Default"));

		//todo parse local entities

		builder.Build();
	}

} // Client

//
// Created by Tony on 06/11/2022.
//

#include "Client/Entity/EntityParser.h"

namespace Client
{

	JsonObject EntityParser::Serialize(std::shared_ptr<Entity> p_entity)
	{
		//todo

		return JsonObject();
	}

	std::shared_ptr<Entity> EntityParser::Parse(JsonObject& p_data)
	{
		// Test if object have a Type Entity
		if (GetParameterFromJsonObject(p_data, "Type", "Null") != "Entity")
		{
#ifdef _DEBUG
			Debug::LogWarning("[EntityParser] Try to parse an Entity, but type is invalid");
#endif
			return nullptr;
		}

		EntityBuilder builder;

		builder.SetActive(GetParameterFromJsonObject(p_data, "IsActive", true));

		builder.SetTag(GetParameterFromJsonObject(p_data, "Tag", "Standard"));

		builder.SetPrefabReferenceUuid(GetParameterFromJsonObject(p_data, "PrefabReferenceUuid", "Null"));

		JsonObject& componentsArrayData = GetParameterFromJsonObject(p_data, "Components", true, false);

		if (componentsArrayData != p_data)
		{
			for (auto& componentData : componentsArrayData)
			{
				std::string componentType = GetParameterFromJsonObject(componentData, "Type", "Null");

				if (componentType == "Transform")
				{
					builder.SetLocalTransform(TransformParser::Parse(componentData));
				}
				else if (componentType == "Camera")
				{
					builder.SetCamera(CameraParser::Parse(componentData));
				}
				else if (componentType == "MeshRenderer")
				{
					//todo add mesh renderer to builder
				}
				else if (componentType == "Script")
				{
					builder.AddScript(ScriptFactory::instance().Make(componentData));
				}
			}
		}

		JsonObject& childsArrayData = GetParameterFromJsonObject(p_data, "Childs", true, false);

		if (childsArrayData != p_data)
		{
			for (auto& childData : childsArrayData)
			{
				auto newChild = EntityParser::Parse(childData);

				if (!newChild)
				{
#ifdef _DEBUG
					Debug::LogWarning("[EntityParser] Failed to parse a Child for an Entity");
#endif
					continue;
				}

				builder.AddChild(newChild);
			}
		}

		return builder.Build();
	}

} // Client
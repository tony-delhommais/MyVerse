//
// Created by Tony on 06/11/2022.
//

#include "TransformParser.h"

namespace Client
{

	JsonObject TransformParser::Serialize(std::shared_ptr<Transform> p_transform)
	{
		JsonObject transformData;

		transformData["Type"] = "Transform";

		glm::vec3 position = p_transform->GetPosition();
		transformData["Position"] = JsonObject::array({ position[0], position[1], position[2] });

		glm::vec3 rotation = p_transform->GetEulerRotation();
		transformData["Rotation"] = JsonObject::array({ rotation[0], rotation[1], rotation[2] });

		glm::vec3 scale = p_transform->GetScale();
		transformData["Scale"] = JsonObject::array({ scale[0], scale[1], scale[2] });

		return transformData;
	}

	std::shared_ptr<Transform> TransformParser::Parse(JsonObject& p_data)
	{
		// Test if object have a Type Entity
		if (GetParameterFromJsonObject(p_data, "Type", "Null") != "Transform")
		{
#ifdef _DEBUG
			Debug::LogWarning("[TransformParser] Try to parse a Transform, but type is invalid");
#endif
			return nullptr;
		}

		TransformBuilder builder;

		JsonObject& position = GetParameterFromJsonObject(p_data, "Position", true, false);
		if (position != p_data && position.size() == 3)
			builder.Position(glm::vec3(position[0], position[1], position[2]));

		JsonObject& rotation = GetParameterFromJsonObject(p_data, "Rotation", true, false);
		if (rotation != p_data && rotation.size() == 3)
			builder.EulerRotation(glm::vec3(rotation[0], rotation[1], rotation[2]));

		JsonObject& scale = GetParameterFromJsonObject(p_data, "Scale", true, false);
		if (scale != p_data && rotation.size() == 3)
			builder.Scale(glm::vec3(scale[0], scale[1], scale[2]));

		return builder.Build();
	}

} // Client
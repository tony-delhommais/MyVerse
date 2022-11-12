//
// Created by Tony on 06/11/2022.
//

#include "Client/Parser/CameraParser.h"

namespace Client
{

	JsonObject CameraParser::Serialize(std::shared_ptr<Camera> p_camera)
	{
		JsonObject cameraData;

		cameraData["Type"] = "Camera";

		cameraData["Fov"] = p_camera->GetFov();

		cameraData["Near"] = p_camera->GetNearFar()[0];
		cameraData["Far"] = p_camera->GetNearFar()[1];

		return cameraData;
	}

	std::shared_ptr<Camera> CameraParser::Parse(JsonObject& p_data)
	{
		// Test if object have a Type Camera
		if (GetParameterFromJsonObject(p_data, "Type", "Null") != "Camera")
		{
#ifdef _DEBUG
			Debug::LogWarning("[CameraParser] Try to parse an Entity, but type is invalid");
#endif
			return nullptr;
		}

		CameraBuilder builder;

		builder.SetFov(GetParameterFromJsonObject(p_data, "Fov", Camera::DEFAULT_FOV()));

		builder.SetNear(GetParameterFromJsonObject(p_data, "Near", Camera::DEFAULT_NEAR_FAR()[0]));
		builder.SetNear(GetParameterFromJsonObject(p_data, "Far", Camera::DEFAULT_NEAR_FAR()[1]));

		return builder.Build();
	}

} // Client
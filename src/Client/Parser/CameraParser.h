//
// Created by Tony on 08/11/2022.
//

#ifndef MYVERSE_CAMERA_PARSER_H
#define MYVERSE_CAMERA_PARSER_H

#include "Client/Utils/JsonUtils.h"

#include "Client/Builders/CameraBuilder.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

	class CameraParser
	{
	public:
		CameraParser() = default;
		~CameraParser() = default;

	public:
		static JsonObject Serialize(std::shared_ptr<Camera> p_camera);

		static std::shared_ptr<Camera> Parse(JsonObject& p_data);
	};

} // Client

#endif // MYVERSE_CAMERA_PARSER_H

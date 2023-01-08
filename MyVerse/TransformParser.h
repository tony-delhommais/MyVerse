//
// Created by Tony on 06/11/2022.
//

#ifndef MYVERSE_TRANSFORM_PARSER_H
#define MYVERSE_TRANSFORM_PARSER_H

#include "JsonUtils.h"

#include "TransformBuilder.h"

#ifdef _DEBUG
#include "Debug.h"
#endif

namespace Client
{

	class TransformParser
	{
	public:
		TransformParser() = default;
		~TransformParser() = default;

	public:
		static JsonObject Serialize(std::shared_ptr<Transform> p_transform);

		static std::shared_ptr<Transform> Parse(JsonObject& p_data);
	};

} // Client

#endif // MYVERSE_TRANSFORM_PARSER_H

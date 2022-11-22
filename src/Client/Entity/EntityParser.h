//
// Created by Tony on 06/11/2022.
//

#ifndef MYVERSE_ENTITY_PARSER_H
#define MYVERSE_ENTITY_PARSER_H

#include "Client/Entity/EntityBuilder.h"

#include "Client/Components/Transform/TransformParser.h"
#include "Client/Components/Camera/CameraParser.h"

namespace Client
{

	class EntityParser
	{
	public:
		EntityParser() = default;
		~EntityParser() = default;

	public:
		static JsonObject Serialize(std::shared_ptr<Entity> p_entity);

		static std::shared_ptr<Entity> Parse(JsonObject& p_data);
	};

} // Client

#endif // MYVERSE_ENTITY_PARSER_H
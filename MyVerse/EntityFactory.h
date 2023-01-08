//
// Created by Tony on 23/09/2022.
//

#ifndef MYVERSE_ENTITY_FACTORY_H
#define MYVERSE_ENTITY_FACTORY_H

#include "JsonUtils.h"

#include "Entity.h"

namespace Client
{

	class EntityFactory
	{
	private:
		EntityFactory() = default;
		~EntityFactory() = default;

	public:
		static EntityFactory& instance();

		bool Register(const std::string& p_entityType, std::function<std::shared_ptr<Entity>(JsonObject& p_entityParameters)> p_entityBuilder);

		template<typename T>
		std::shared_ptr<T> Make(JsonObject& p_entityParameters)
		{
			static_assert(std::is_base_of<Entity, T>::value, "Make parameter must inherit from type Entity");

			std::string entityType = GetParameterFromJsonObject(p_entityParameters, "Type", "Null");

			if (entityType == "Null")
			{
#ifdef _DEBUG
				Debug::LogWarning("[EntityFactory] Try to parse an Entity, but type is invalid");
#endif
				return nullptr;
			}

			std::shared_ptr<Entity> entity = m_entityBuilders[entityType](p_entityParameters);

			return std::dynamic_pointer_cast<T>(entity);
		}

	private:
		std::map<std::string, std::function<std::shared_ptr<Entity>(JsonObject& p_entityParameters)>> m_entityBuilders;
	};

} // Client

#endif // MYVERSE_ENTITY_FACTORY_H

//
// Created by Tony on 06/11/2022.
//

#ifndef MYVERSE_ENTITY_BUILDER_H
#define MYVERSE_ENTITY_BUILDER_H

#include "Client/Entity/Entity.h"

#include "Client/Builders/TransformBuilder.h"

namespace Client
{

	class EntityBuilder
	{
	public:
		EntityBuilder();
		~EntityBuilder() = default;

	public:
		std::shared_ptr<Entity> Build();

		EntityBuilder& SetActive(bool p_isActive);
		EntityBuilder& SetTag(const std::string& p_tag);
		EntityBuilder& SetPrefabReferenceUuid(const std::string& p_prefabReferenceUuid);
		EntityBuilder& SetPrefabReferenceUuid(const UUIDv4::UUID& p_prefabReferenceUuid);
		EntityBuilder& SetLocalTransform(std::shared_ptr<Transform> p_localTransform);
		EntityBuilder& SetMeshRenderer(std::shared_ptr<MeshRenderer> p_meshRenderer);
		EntityBuilder& SetScript(std::shared_ptr<Script> p_script);
		EntityBuilder& AddChild(std::shared_ptr<Entity> p_child);

	private:
		bool m_isActive = true;
		std::string m_tag = "None";
		UUIDv4::UUID m_prefabReferenceUuid;

		std::list<std::shared_ptr<Entity>> m_childrens;

		std::shared_ptr<Transform> m_localTransform = nullptr;

		std::shared_ptr<MeshRenderer> m_meshRenderer = nullptr;
		std::shared_ptr<Script> m_script = nullptr;
	};

} // Client

#endif // MYVERSE_ENTITY_BUILDER_H

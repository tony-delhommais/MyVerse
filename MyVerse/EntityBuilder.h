//
// Created by Tony on 06/11/2022.
//

#ifndef MYVERSE_ENTITY_BUILDER_H
#define MYVERSE_ENTITY_BUILDER_H

#include "Entity.h"

#include "TransformBuilder.h"

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
		EntityBuilder& SetPrefabReferenceUuid(const uuids::uuid& p_prefabReferenceUuid);
		EntityBuilder& AddChild(std::shared_ptr<Entity> p_child);
		EntityBuilder& SetLocalTransform(std::shared_ptr<Transform> p_localTransform);
		EntityBuilder& SetCamera(std::shared_ptr<Camera> p_camera);
		EntityBuilder& SetMeshRenderer(std::shared_ptr<MeshRenderer> p_meshRenderer);
		EntityBuilder& AddScript(std::shared_ptr<Script> p_script);

	private:
		bool m_isActive = true;
		std::string m_tag = "None";
		uuids::uuid m_prefabReferenceUuid;

		std::list<std::shared_ptr<Entity>> m_childrens;

		std::shared_ptr<Transform> m_localTransform = nullptr;

		std::shared_ptr<Camera> m_camera = nullptr;

		std::shared_ptr<MeshRenderer> m_meshRenderer = nullptr;
		std::list<std::shared_ptr<Script>> m_scripts;
	};

} // Client

#endif // MYVERSE_ENTITY_BUILDER_H

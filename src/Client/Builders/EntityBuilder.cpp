//
// Created by Tony on 06/11/2022.
//

#include "Client/Builders/EntityBuilder.h"

namespace Client
{

	EntityBuilder::EntityBuilder()
	{
		m_localTransform = TransformBuilder().Build();
	}

	std::shared_ptr<Entity> EntityBuilder::Build()
	{
		std::shared_ptr<Entity> entity = std::make_shared<Entity>(m_isActive, m_tag, m_prefabReferenceUuid, m_localTransform, m_camera, m_meshRenderer, m_scripts);

		for (std::shared_ptr<Entity> child : m_childrens)
			entity->AddChild(child);

		return entity;
	}

	EntityBuilder& EntityBuilder::SetActive(bool p_isActive)
	{
		m_isActive = p_isActive;

		return *this;
	}

	EntityBuilder& EntityBuilder::SetTag(const std::string& p_tag)
	{
		m_tag = p_tag;

		return *this;
	}
	
	EntityBuilder& EntityBuilder::SetPrefabReferenceUuid(const std::string& p_prefabReferenceUuid)
	{
		m_prefabReferenceUuid = UUIDv4::UUID::fromStrFactory(p_prefabReferenceUuid);

		return *this;
	}

	EntityBuilder& EntityBuilder::SetPrefabReferenceUuid(const UUIDv4::UUID& p_prefabReferenceUuid)
	{
		m_prefabReferenceUuid = p_prefabReferenceUuid;

		return *this;
	}

	EntityBuilder& EntityBuilder::AddChild(std::shared_ptr<Entity> p_child)
	{
		m_childrens.push_back(p_child);

		return *this;
	}

	EntityBuilder& EntityBuilder::SetLocalTransform(std::shared_ptr<Transform> p_localTransform)
	{
		m_localTransform = p_localTransform;

		return *this;
	}

	EntityBuilder& EntityBuilder::SetCamera(std::shared_ptr<Camera> p_camera)
	{
		m_camera = p_camera;

		return *this;
	}

	EntityBuilder& EntityBuilder::SetMeshRenderer(std::shared_ptr<MeshRenderer> p_meshRenderer)
	{
		m_meshRenderer = p_meshRenderer;

		return *this;
	}

	EntityBuilder& EntityBuilder::AddScript(std::shared_ptr<Script> p_script)
	{
		m_scripts.push_back(p_script);

		return *this;
	}

} // Client

//
// Created by Tony on 06/11/2022.
//

#include "TransformBuilder.h"

namespace Client
{

	std::shared_ptr<Transform> TransformBuilder::Build()
	{
		std::shared_ptr<Transform> transform = std::make_shared<Transform>(m_entity, glm::mat4(1.0));

		transform->SetPosition(m_position);
		transform->SetRotation(m_rotation);
		transform->SetScale(m_scale);

		return transform;
	}

	TransformBuilder& TransformBuilder::ComponentEntity(std::shared_ptr<Entity> p_entity)
	{
		m_entity = p_entity;

		return *this;
	}

	TransformBuilder& TransformBuilder::Position(const glm::vec3 p_position)
	{
		m_position = p_position;

		return *this;
	}

	TransformBuilder& TransformBuilder::Rotation(const glm::quat p_rotation)
	{
		m_rotation = p_rotation;

		return *this;
	}

	TransformBuilder& TransformBuilder::EulerRotation(const glm::vec3 p_eulerRotation, bool p_useDegree)
	{
		if (p_useDegree)
			m_rotation = glm::quat(glm::radians(p_eulerRotation));
		else
			m_rotation = glm::quat(p_eulerRotation);

		return *this;
	}

	TransformBuilder& TransformBuilder::Scale(const glm::vec3 p_scale)
	{
		m_scale = p_scale;

		return *this;
	}

} // Client

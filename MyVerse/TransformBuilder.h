//
// Created by Tony on 06/11/2022.
//

#ifndef MYVERSE_TRANSFORM_BUILDER_H
#define MYVERSE_TRANSFORM_BUILDER_H

#include "MathUtils.h"

#include "Transform.h"

namespace Client
{

	class TransformBuilder
	{
	public:
		TransformBuilder() = default;
		~TransformBuilder() = default;

	public:
		std::shared_ptr<Transform> Build();

		TransformBuilder& ComponentEntity(std::shared_ptr<Entity> p_entity);
		TransformBuilder& Position(const glm::vec3 p_position);
		TransformBuilder& Rotation(const glm::quat p_rotation);
		TransformBuilder& EulerRotation(const glm::vec3 p_eulerRotation, bool p_useDegree = true);
		TransformBuilder& Scale(const glm::vec3 p_scale);

	private:
		std::shared_ptr<Entity> m_entity = nullptr;

		glm::vec3 m_position = glm::vec3(0.0);
		glm::quat m_rotation = glm::quat(1.0, 0.0, 0.0, 0.0);
		glm::vec3 m_scale = glm::vec3(1.0);
	};

} // Client

#endif // MYVERSE_TRANSFORM_BUILDER_H

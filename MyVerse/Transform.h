//
// Created by Tony on 06/11/2022.
//

#ifndef MYVERSE_TRANSFORM_H
#define MYVERSE_TRANSFORM_H

#include "Component.h"

#include "MathUtils.h"

namespace Client
{

	class Transform : public Component
	{
	public:
		Transform(std::shared_ptr<Entity> p_entity, const glm::mat4& p_localTransform);
		~Transform() = default;

	public:
		void Translate(const glm::vec3& p_position);
		void Rotate(const glm::quat& p_rotation);
		void RotateEuler(const glm::vec3& p_eulerRotation, bool p_useDegree = true);
		void Scale(const glm::vec3& p_scale);

		glm::vec3 Forward();
		glm::vec3 Right();
		glm::vec3 Up();

		void SetLocalTransform(const glm::mat4& p_localTransform);
		glm::mat4 GetLocalTransform();

		glm::mat4 GetModelMatrix();
		glm::vec3 GetModelPosition();
		glm::quat GetModelRotation();
		glm::vec3 GetModelEulerRotation(bool p_useDegree = true);
		glm::vec3 GetModelScale();

		void SetPosition(const glm::vec3& p_position);
		glm::vec3 GetPosition();

		void SetRotation(const glm::quat& p_rotation);
		glm::quat GetRotation();

		void SetEulerRotation(const glm::vec3& p_eulerRotation, bool p_useDegree = true);
		glm::vec3 GetEulerRotation(bool p_useDegree = true);

		void SetScale(const glm::vec3& p_scale);
		glm::vec3 GetScale();

	private:
		void DecomposeLocalMatrix(glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale);
		void ComposeLocalMatrix(glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale);

	private:
		glm::mat4 m_localTransform;
	};

} // Client

#endif // MYVERSE_TRANSFORM_H

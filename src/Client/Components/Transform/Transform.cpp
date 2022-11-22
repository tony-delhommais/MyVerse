//
// Created by Tony on 06/11/2022.
//

#include "Client/Components/Transform/Transform.h"

#include "Client/Entity/Entity.h"

namespace Client
{

	Transform::Transform(std::shared_ptr<Entity> p_entity, const glm::mat4& p_localTransform) :
		Component(ComponentType::TRANSFORM, p_entity),
		m_localTransform(p_localTransform)
	{

	}

	void Transform::Translate(const glm::vec3& p_position)
	{
		m_localTransform[3].xyz += p_position;
	}

	void Transform::Rotate(const glm::quat& p_rotation)
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		rotation *= p_rotation;

		ComposeLocalMatrix(position, rotation, scale);
	}

	void Transform::RotateEuler(const glm::vec3& p_eulerRotation, bool p_useDegree)
	{
		if (p_useDegree)
			Rotate(glm::quat(glm::radians(p_eulerRotation)));
		else
			Rotate(glm::quat(p_eulerRotation));
	}

	void Transform::Scale(const glm::vec3& p_scale)
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		scale *= p_scale;

		ComposeLocalMatrix(position, rotation, scale);
	}

	glm::vec3 Transform::Forward()
	{

		glm::quat worldRotation = GetModelRotation();

		float x = worldRotation.x;
		float y = worldRotation.y;
		float z = worldRotation.z;
		float w = worldRotation.w;

		return glm::vec3(2 * (x * z + w * y), 2 * (y * z - w * x), 1 - 2 * (x * x + y * y));
	}

	glm::vec3 Transform::Right()
	{
		glm::quat worldRotation = GetModelRotation();

		float x = worldRotation.x;
		float y = worldRotation.y;
		float z = worldRotation.z;
		float w = worldRotation.w;

		return glm::vec3(1 - 2 * (y * y + z * z), 2 * (x * y + w * z), 2 * (x * z - w * y)) * -1.0f;
	}

	glm::vec3 Transform::Up()
	{
		glm::quat worldRotation = GetModelRotation();

		float x = worldRotation.x;
		float y = worldRotation.y;
		float z = worldRotation.z;
		float w = worldRotation.w;

		return glm::vec3(2 * (x * y - w * z), 1 - 2 * (x * x + z * z), 2 * (y * z + w * x));
	}

	void Transform::SetLocalTransform(const glm::mat4& p_localTransform)
	{
		m_localTransform = p_localTransform;
	}

	glm::mat4 Transform::GetLocalTransform()
	{
		return m_localTransform;
	}

	glm::mat4 Transform::GetModelMatrix()
	{
		if (GetEntity() && GetEntity()->GetParent())
		{
			return GetEntity()->GetParent()->GetTransform()->GetModelMatrix() * m_localTransform;
		}

		return m_localTransform;
	}

	glm::vec3 Transform::GetModelPosition()
	{
		return GetModelMatrix()[3].xyz;
	}

	glm::quat Transform::GetModelRotation()
	{
		return glm::toQuat(GetModelMatrix());
	}

	glm::vec3 Transform::GetModelEulerRotation(bool p_useDegree)
	{
		if (p_useDegree) return glm::degrees(glm::eulerAngles(GetModelRotation()));
		else return glm::eulerAngles(GetModelRotation());
	}

	glm::vec3 Transform::GetModelScale()
	{
		return glm::vec3(glm::length(glm::vec3(GetModelMatrix()[0])), glm::length(glm::vec3(GetModelMatrix()[1])), glm::length(glm::vec3(GetModelMatrix()[2])));
	}

	void Transform::SetPosition(const glm::vec3& p_position)
	{
		m_localTransform[3].xyz = p_position;
	}

	glm::vec3 Transform::GetPosition()
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		return position;
	}

	void Transform::SetRotation(const glm::quat& p_rotation)
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		rotation = p_rotation;

		ComposeLocalMatrix(position, rotation, scale);
	}

	glm::quat Transform::GetRotation()
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		return rotation;
	}

	void Transform::SetEulerRotation(const glm::vec3& p_eulerRotation, bool p_useDegree)
	{
		if (p_useDegree) SetRotation(glm::quat(glm::degrees(p_eulerRotation)));
		else SetRotation(glm::quat(p_eulerRotation));
	}

	glm::vec3 Transform::GetEulerRotation(bool p_useDegree)
	{
		if (p_useDegree) return glm::degrees(glm::eulerAngles(GetRotation()));
		else return glm::eulerAngles(GetRotation());
	}

	void Transform::SetScale(const glm::vec3& p_scale)
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		scale = p_scale;

		ComposeLocalMatrix(position, rotation, scale);
	}

	glm::vec3 Transform::GetScale()
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		return scale;
	}

	void Transform::DecomposeLocalMatrix(glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale)
	{
		Math::DecomposeMatrix(m_localTransform, p_position, p_rotation, p_scale);
	}

	void Transform::ComposeLocalMatrix(glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale)
	{
		Math::ComposeMatrix(m_localTransform, p_position, p_rotation, p_scale);
	}

} // Client

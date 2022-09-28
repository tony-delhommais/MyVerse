//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_ENTITY_H
#define MYVERSE_ENTITY_H

#include "Client/Utils/GraphicsUtils.h"
#include "Client/Utils/MathUtils.h"
#include "Client/Utils/JsonUtils.h"

#include "Client/Common/RessourceManager.h"

#include "Client/Ressource/Prefab.h"
#include "Client/Ressource/Scene.h"

#include "Client/Components/MeshRenderer.h"

#include "Client/Factories/ScriptFactory.h"

#include "Client/Entity/EntityExecutionState.h"

namespace Client
{

	class Entity : public std::enable_shared_from_this<Entity>
	{
	public:
		Entity();
		virtual ~Entity();

		std::shared_ptr<Entity> InstantiatePrefab(const UUIDv4::UUID& p_prefabUuid);
		void DestroyEntity();

	public:
		std::shared_ptr<Entity> SetParent(std::shared_ptr<Entity> p_newParent, bool p_keepWorldTransform = false);
		std::shared_ptr<Entity> GetParent();

		std::shared_ptr<Entity> AddChild(std::shared_ptr<Entity> p_newChild);
		std::shared_ptr<Entity> RemoveChild(std::shared_ptr<Entity> p_oldChild);

		std::list<std::shared_ptr<Entity>> GetChilds();

		std::shared_ptr<Entity> FindChildWithTag(const std::string& p_tag);
		std::list<std::shared_ptr<Entity>> FindChildsWithTag(const std::string& p_tag);

		void Translate(const glm::vec3& p_position);
		void Rotate(const glm::quat& p_rotation);
		void RotateEuler(const glm::vec3& p_eulerRotation, bool p_useDegree = true);
		void Scale(const glm::vec3& p_scale);

		glm::vec3 Forward();
		glm::vec3 Right();
		glm::vec3 Up();

		void UpdateExecution(float p_deltaTime);
		void Render(glm::mat4& p_MVPParent);

	public:
		EntityExecutionState GetCurrentEntityExecutionState();

		void SetActive(bool p_isActive);
		bool IsActive();

		void SetTag(const std::string& p_tag);
		std::string GetTag();

		void SetPrefabReferenceUuid(const UUIDv4::UUID& p_prefabReferenceUuid);
		bool IsEntityReferencedToAPrefab();

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

		void SetMeshRenderer(std::shared_ptr<MeshRenderer> p_meshRenderer);

		void SetScript(std::shared_ptr<Script> p_script);

		template<typename T>
		std::shared_ptr<T> GetScript()
		{
			static_assert(std::is_base_of<Script, T>::value, "GetScript parameter must inherit from type Script");

			std::list<std::shared_ptr<Component>> components;

			if (m_script)
				return std::dynamic_pointer_cast<T>(m_script);

			return nullptr;
		}

	private:
		bool IsChildOf(std::shared_ptr<Entity> p_testEntity);
		bool IsParentOf(std::shared_ptr<Entity> p_testEntity);

		void DetermineNextEntityState();

		void DecomposeLocalMatrix(glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale);
		void ComposeLocalMatrix(glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale);

	private:
		static bool s_isEntityMakerRegistered;

		EntityExecutionState m_currentEntityExecutionState = EntityExecutionState::PreAwake;
		EntityExecutionState m_wantedEntityExecutionState = EntityExecutionState::Update;

		bool m_isActive = true;
		std::string m_tag = "None";
		UUIDv4::UUID m_prefabReferenceUuid;

		std::shared_ptr<Entity> m_parent;

		std::list<std::shared_ptr<Entity>> m_childrens;

		glm::mat4 m_localTransform;

		std::shared_ptr<MeshRenderer> m_meshRenderer;
		std::shared_ptr<Script> m_script;
	};

} // Client

#endif // MYVERSE_ENTITY_H

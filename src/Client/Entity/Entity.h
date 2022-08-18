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

		static std::shared_ptr<Entity> Make(JsonObject& p_entityParameters);

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

		void InstantiatePrefab(const UUIDv4::UUID& p_prefabUuid);
		void DestroyEntity();

		bool AddComponent(std::shared_ptr<Component> p_component);

		template<typename T>
		std::shared_ptr<T> GetComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "GetComponent parameter must inherit from type Component");

			std::list<std::shared_ptr<Component>> components;

			components.push_back(m_meshRenderer);
			components.insert(components.end(), m_scripts.begin(), m_scripts.end());

			for (auto& component : components)
			{
				std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
				if (castedComponent)
					return castedComponent;
			}

			return nullptr;
		}

		template<typename T>
		std::list<std::shared_ptr<T>> GetComponents()
		{
			static_assert(std::is_base_of<Component, T>::value, "GetComponents parameter must inherit from type Component");

			std::list<std::shared_ptr<Component>> components;

			components.push_back(m_meshRenderer);
			components.insert(components.end(), m_scripts.begin(), m_scripts.end());

			std::list<std::shared_ptr<T>> Tcomponents;

			for (auto& component : components)
			{
				std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
				if (castedComponent)
					Tcomponents.push_back(castedComponent);
			}

			return Tcomponents;
		}

		void UpdateExecution(float p_deltaTime);
		void Render();

	public:
		EntityExecutionState GetCurrentEntityExecutionState();

		void SetActive(bool p_isActive);
		bool IsActive();

		void SetTag(const std::string& p_tag);
		std::string GetTag();

		void SetPrefabReferenceUuid(const UUIDv4::UUID& p_prefabReferenceUuid);
		bool IsEntityReferencedToAPrefab();

		const glm::mat4& GetLocalTransform();
		const glm::mat4& GetWorldTransform();

		void SetLocalPosition(const glm::vec3& p_position);
		const glm::vec3& GetLocalPosition();
		const glm::vec3& GetWorldPosition();

		void SetLocalRotation(const glm::quat& p_rotation);
		glm::quat GetLocalRotation();
		glm::quat GetWorldRotation();

		void SetLocalEulerRotation(const glm::vec3& p_eulerRotation, bool p_useDegree = true);
		glm::vec3 GetLocalEulerRotation(bool p_useDegree = true);
		glm::vec3 GetWorldEulerRotation(bool p_useDegree = true);

		void SetLocalScale(const glm::vec3& p_scale);
		const glm::vec3& GetLocalScale();
		const glm::vec3& GetWorldScale();

	private:
		bool IsChildOf(std::shared_ptr<Entity> p_testEntity);
		bool IsParentOf(std::shared_ptr<Entity> p_testEntity);

		void DetermineNextEntityState();

		void ComputeLocalTransform();
		void DecomposeWorldTransform();

	private:
		GLint m_shaderModelMatrixUniformLocation = -1;

		EntityExecutionState m_currentEntityExecutionState = EntityExecutionState::PreAwake;
		EntityExecutionState m_wantedEntityExecutionState = EntityExecutionState::Update;

		long long m_decomposeWorldTransformLastCompute = 0;
		long long m_getWorldTransformLastCompute = 0;

		bool m_isActive = true;
		std::string m_tag = "None";
		UUIDv4::UUID m_prefabReferenceUuid;

		std::shared_ptr<Entity> m_parent;

		std::list<std::shared_ptr<Entity>> m_childrens;

		glm::mat4 m_localTransform;

		glm::vec3 m_localPosition;
		glm::vec3 m_localRotation;
		glm::vec3 m_localScale;

		glm::mat4 m_worldTransform;

		glm::vec3 m_worldPosition;
		glm::vec3 m_worldRotation;
		glm::vec3 m_worldScale;

		std::shared_ptr<MeshRenderer> m_meshRenderer;
		std::list<std::shared_ptr<Script>> m_scripts;
	};

} // Client

#endif // MYVERSE_ENTITY_H

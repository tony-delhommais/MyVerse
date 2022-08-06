//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_ENTITY_H
#define MYVERSE_ENTITY_H

#include "Core/Utils/GraphicsUtils.h"
#include "Core/Utils/MathUtils.h"
#include "Core/Utils/JsonUtils.h"

#include "Core/Managers/RessourceManager.h"

#include "Core/Ressource/Prefab.h"

#include "Core/Rendering/Scene.h"

#include "Core/Components/MeshRenderer.h"
#include "Core/Components/Camera.h"

#include "Core/Factories/ScriptFactory.h"

#include "Core/Entity/EntityExecutionState.h"

namespace Core
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
        void RotateEuler(const glm::vec3& p_eulerRotation, bool p_useDegree = true);
        //void Rotate(const glm::quat& p_rotation);
        void Scale(const glm::vec3& p_scale);

        glm::vec3 Forward();
        glm::vec3 Right();
        glm::vec3 Up();

        void InstantiatePrefab(UUIDv4::UUID& p_prefabUuid);
		void DestroyEntity();

		bool AddComponent(std::shared_ptr<Component> p_component);

		template<typename T>
		std::shared_ptr<T> GetComponent()
		{
			static_assert(std::is_base_of<Component, T>::value, "GetComponent parameter must inherit from type Component");

			std::list<std::shared_ptr<Component>> components;

			components.push_back(m_meshRenderer);
			components.push_back(m_camera);
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
            components.push_back(m_camera);
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
		void Render(const glm::mat4& p_VPMatrix, const glm::mat4& p_parentModel);

    public:
        EntityExecutionState GetCurrentEntityExecutionState();

		void SetActive(bool p_isActive);
		bool IsActive();

		void SetTag(const std::string& p_tag);
		std::string GetTag();

        void SetPrefabReferenceUuid(const UUIDv4::UUID& p_prefabReferenceUuid);
		bool IsEntityReferencedToAPrefab();

        glm::mat4& GetLocalTransform();
        glm::mat4 GetWorldTransform();

        void SetLocalPosition(const glm::vec3& p_position);
        glm::vec3 GetLocalPosition();
        glm::vec3 GetWorldPosition();

        //void SetLocalRotation(const glm::quat& p_rotation);
        //glm::quat GetLocalRotation();
        glm::quat GetWorldRotation();
        glm::vec3 GetWorldEulerRotation(bool p_useDegree = true);

        void SetLocalEulerRotation(const glm::vec3 p_eulerRotation, bool p_useDegree = true);
        glm::vec3 GetLocalEulerRotation(bool p_useDegree = true);

        void SetLocalScale(const glm::vec3 p_scale);
        glm::vec3 GetLocalScale();
        glm::vec3 GetWorldScale();

	private:
		bool IsChildOf(std::shared_ptr<Entity> p_testEntity);
		bool IsParentOf(std::shared_ptr<Entity> p_testEntity);

        void DetermineNextEntityState();

        void ComputeLocalTransform();
        void DecomposeWorldTransform();

        EntityExecutionState m_currentEntityExecutionState = EntityExecutionState::PreAwake;
        EntityExecutionState m_wantedEntityExecutionState = EntityExecutionState::Update;

		bool m_isActive = true;
		std::string m_tag = "None";
        UUIDv4::UUID m_prefabReferenceUuid;

		std::shared_ptr<Entity> m_parent;

		std::list<std::shared_ptr<Entity>> m_childrens;

        glm::mat4 m_localTransform;

        glm::vec3 m_localPosition;
        glm::vec3 m_localRotation;
        glm::vec3 m_localScale;

        glm::vec3 m_worldPosition;
        glm::quat m_worldRotation;
        glm::vec3 m_worldScale;

		std::shared_ptr<MeshRenderer> m_meshRenderer;
		std::shared_ptr<Camera> m_camera;
		std::list<std::shared_ptr<Script>> m_scripts;
	};

} // Core

#endif // MYVERSE_ENTITY_H

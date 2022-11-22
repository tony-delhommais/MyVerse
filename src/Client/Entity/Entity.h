//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_ENTITY_H
#define MYVERSE_ENTITY_H

#include "Client/Utils/GraphicsUtils.h"
#include "Client/Utils/MathUtils.h"
#include "Client/Utils/JsonUtils.h"

#include "Client/Common/SceneManager.h"
#include "Client/Common/RessourceManager.h"

#include "Client/Ressource/Prefab.h"

#include "Client/Components/Transform.h"
#include "Client/Components/Camera.h"
#include "Client/Components/MeshRenderer.h"

#include "Client/Factories/ScriptFactory.h"

#include "Client/Entity/EntityExecutionState.h"

namespace Client
{

	class Entity : public std::enable_shared_from_this<Entity>
	{
	public:
		Entity(bool p_isActive, const std::string& p_tag, const UUIDv4::UUID& p_prefabReferenceUuid, std::shared_ptr<Transform> p_localTransform, std::shared_ptr<Camera> p_camera,  std::shared_ptr<MeshRenderer> p_meshRenderer, std::list<std::shared_ptr<Script>> p_scripts);
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

		std::shared_ptr<Transform> GetTransform();

		//void SetMeshRenderer(std::shared_ptr<MeshRenderer> p_meshRenderer);

		//void SetScript(std::shared_ptr<Script> p_script);

		/*template<typename T>
		std::shared_ptr<T> GetScript()
		{
			static_assert(std::is_base_of<Script, T>::value, "GetScript parameter must inherit from type Script");

			std::list<std::shared_ptr<Component>> components;

			if (m_script)
				return std::dynamic_pointer_cast<T>(m_script);

			return nullptr;
		}*/

	private:
		bool IsChildOf(std::shared_ptr<Entity> p_testEntity);
		bool IsParentOf(std::shared_ptr<Entity> p_testEntity);

		void DetermineNextEntityState();

	private:
		EntityExecutionState m_currentEntityExecutionState = EntityExecutionState::PreAwake;
		EntityExecutionState m_wantedEntityExecutionState = EntityExecutionState::Update;

		bool m_isActive = true;
		std::string m_tag = "None";
		UUIDv4::UUID m_prefabReferenceUuid;

		std::shared_ptr<Entity> m_parent;

		std::list<std::shared_ptr<Entity>> m_childrens;

		std::shared_ptr<Transform> m_localTransform;

		std::shared_ptr<Camera> m_camera;

		std::shared_ptr<MeshRenderer> m_meshRenderer;
		std::list<std::shared_ptr<Script>> m_scripts;
	};

} // Client

#endif // MYVERSE_ENTITY_H

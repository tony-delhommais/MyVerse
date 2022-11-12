//
// Created by Tony on 29/06/2022.
//

#include "Client/Entity/Entity.h"

#include "Client/Core/ApplicationCore.h"

namespace Client
{

	Entity::Entity(bool p_isActive, const std::string& p_tag, const UUIDv4::UUID& p_prefabReferenceUuid, std::shared_ptr<Transform> p_localTransform, std::shared_ptr<Camera> p_camera, std::shared_ptr<MeshRenderer> p_meshRenderer, std::list<std::shared_ptr<Script>> p_scripts) :
		m_tag(p_tag),
		m_prefabReferenceUuid(p_prefabReferenceUuid),
		m_localTransform(p_localTransform),
		m_camera(p_camera),
		m_meshRenderer(p_meshRenderer),
		m_scripts(p_scripts)
	{
		SetActive(p_isActive);

		m_localTransform->RotateEuler(glm::vec3(0.0f, 180.0f, 0.0f));
	}

	Entity::~Entity()
	{
		m_childrens.clear();
	}

	std::shared_ptr<Entity> Entity::InstantiatePrefab(const UUIDv4::UUID& p_prefabUuid)
	{
		auto prefab = RessourceManager::FindPrefab(p_prefabUuid);

		std::shared_ptr<Entity> newChild = prefab->InstantiateNew();
		newChild->SetPrefabReferenceUuid(p_prefabUuid);

		AddChild(newChild);

		return newChild;
	}

	void Entity::DestroyEntity()
	{
		m_wantedEntityExecutionState = EntityExecutionState::PostDestroy;

		for (auto& child : m_childrens)
		{
			child->DestroyEntity();
		}
	}

	std::shared_ptr<Entity> Entity::SetParent(std::shared_ptr<Entity> p_newParent, bool p_keepWorldTransform)
	{
		if(m_parent) // If this has a parent
			m_parent->RemoveChild(shared_from_this());
		else // Otherwise parent is the scene
			Scene::instance().RemoveLocalEntity(shared_from_this());

		if(p_newParent) // If new parent is not Null
			p_newParent->AddChild(shared_from_this());
		else // Otherwise new parent is scene
			Scene::instance().AddLocalEntity(shared_from_this());

		// Set the new parent
		m_parent = p_newParent;

		return p_newParent;
	}

	std::shared_ptr<Entity> Entity::GetParent()
	{
		return m_parent;
	}

	std::shared_ptr<Entity> Entity::AddChild(std::shared_ptr<Entity> p_newChild)
	{
		if (!p_newChild) // If new child is not Null
			return nullptr;

		if (p_newChild->m_parent) // If new child already have a parent
			return nullptr;

		// Add new child to the list
		m_childrens.push_back(p_newChild);

		// Set the parent of the new child
		p_newChild->m_parent = shared_from_this();

		return p_newChild;
	}

	std::shared_ptr<Entity> Entity::RemoveChild(std::shared_ptr<Entity> p_oldChild)
	{
		if (!p_oldChild) // If old child is not Null
			return nullptr;

		if (!p_oldChild->m_parent) // If old child has no parent
			return nullptr;

		if (p_oldChild->m_parent.get() != this) // If parent of old child is not this
			return nullptr;

		// Remove old child from list
		m_childrens.erase(std::remove(m_childrens.begin(), m_childrens.end(), p_oldChild), m_childrens.end());

		// Set parent of old child to Null
		p_oldChild->m_parent = nullptr;

		return p_oldChild;
	}

	std::list<std::shared_ptr<Entity>> Entity::GetChilds()
	{
		return m_childrens;
	}

	std::shared_ptr<Entity> Entity::FindChildWithTag(const std::string& p_tag)
	{
		if (GetTag() == p_tag)
			return shared_from_this();

		for (auto& child : m_childrens)
		{
			auto foundEntity = child->FindChildWithTag(p_tag);
			if (foundEntity)
				return foundEntity;
		}

		return nullptr;
	}

	std::list<std::shared_ptr<Entity>> Entity::FindChildsWithTag(const std::string& p_tag)
	{
		std::list<std::shared_ptr<Entity>> foundEntities;

		if (GetTag() == p_tag)
			foundEntities.push_back(shared_from_this());

		for (auto& child : m_childrens)
		{
			auto foundEntitiesOnChild = child->FindChildsWithTag(p_tag);
			
			foundEntities.insert(foundEntities.end(), foundEntitiesOnChild.begin(), foundEntitiesOnChild.end());
		}

		return foundEntities;
	}

	void Entity::UpdateExecution(float p_deltaTime)
	{
		bool notEqual = m_currentEntityExecutionState != m_wantedEntityExecutionState;

		switch (m_currentEntityExecutionState) {
		case Awake:
			if(notEqual)
				for(std::shared_ptr<Script> script : m_scripts)
					script->Awake();
			break;
		case OnEnable:
			if(notEqual)
				for (std::shared_ptr<Script> script : m_scripts)
					script->OnEnable();
			break;
		case Start:
			if(notEqual)
				for (std::shared_ptr<Script> script : m_scripts)
					script->Start();
			break;
		case Update:
			for (std::shared_ptr<Script> script : m_scripts)
				script->Update(p_deltaTime);
			break;
		case OnDisable:
			if(notEqual)
				for (std::shared_ptr<Script> script : m_scripts)
					script->OnDisable();
			break;
		case Destroy:
			if(notEqual)
				for (std::shared_ptr<Script> script : m_scripts)
					script->Destroy();
			break;
		default:
			break;
		}

		std::list<std::shared_ptr<Entity>>::iterator it = m_childrens.begin();
		while (it != m_childrens.end())
		{
			std::list<std::shared_ptr<Entity>>::iterator childToTest = it;

			childToTest->get()->UpdateExecution(p_deltaTime);

			it++;

			if (childToTest->get()->GetCurrentEntityExecutionState() == EntityExecutionState::PostDestroy)
			{
				m_childrens.erase(childToTest);
			}
		}

		DetermineNextEntityState();
	}

	void Entity::Render(glm::mat4& p_MVPParent)
	{
		if (m_isActive)
		{
			glm::mat4 MVP = p_MVPParent * m_localTransform->GetLocalTransform();

			if (m_meshRenderer)
			{
				ApplicationCore::instance().GetActiveShader()->SetMatrixUniform(EnumMatrix::MODELVIEWPROJECTION_MATRIX, MVP);

				m_meshRenderer->Render();
			}

			for (auto& child : m_childrens)
			{
				child->Render(MVP);
			}
		}
	}

	EntityExecutionState Entity::GetCurrentEntityExecutionState()
	{
		return m_currentEntityExecutionState;
	}

	void Entity::SetActive(bool p_isActive)
	{
		if(p_isActive) m_wantedEntityExecutionState = EntityExecutionState::Update;
		else
		{
			if (m_currentEntityExecutionState == EntityExecutionState::PreAwake) m_wantedEntityExecutionState = EntityExecutionState::Awake;
			else m_wantedEntityExecutionState = EntityExecutionState::OnDisable;
		}

		m_isActive = p_isActive;

		for(auto& child : m_childrens) child->SetActive(p_isActive);
	}

	bool Entity::IsActive()
	{
		return m_isActive;
	}

	void Entity::SetTag(const std::string& p_tag)
	{
		m_tag = p_tag;
	}

	std::string Entity::GetTag()
	{
		return m_tag;
	}

	void Entity::SetPrefabReferenceUuid(const UUIDv4::UUID& p_prefabReferenceUuid)
	{
		m_prefabReferenceUuid = p_prefabReferenceUuid;
	}

	bool Entity::IsEntityReferencedToAPrefab()
	{
		auto prefabRefStruct = RessourceManager::FindPrefab(m_prefabReferenceUuid);

		return prefabRefStruct != nullptr;
	}

	std::shared_ptr<Transform> Entity::GetTransform()
	{
		return m_localTransform;
	}

	/*void Entity::SetMeshRenderer(std::shared_ptr<MeshRenderer> p_meshRenderer)
	{
		if (p_meshRenderer)
			p_meshRenderer->SetEntity(shared_from_this());

		m_meshRenderer = p_meshRenderer;
	}

	void Entity::SetScript(std::shared_ptr<Script> p_script)
	{
		if (p_script)
			p_script->SetEntity(shared_from_this());

		m_script = p_script;
	}*/

	bool Entity::IsChildOf(std::shared_ptr<Entity> p_testEntity)
	{
		return p_testEntity->IsParentOf(shared_from_this());
	}

	bool Entity::IsParentOf(std::shared_ptr<Entity> p_testEntity)
	{
		if (!p_testEntity->m_parent)
			return false;

		if (this == p_testEntity->m_parent.get())
			return true;

		return p_testEntity->m_parent->IsParentOf(p_testEntity);
	}

	void Entity::DetermineNextEntityState()
	{
		if(m_wantedEntityExecutionState != m_currentEntityExecutionState)
		{
			switch (m_currentEntityExecutionState) {
			case PreAwake:
				m_currentEntityExecutionState = EntityExecutionState::Awake;
				break;
			case Awake:
				m_currentEntityExecutionState = EntityExecutionState::OnEnable;
				break;
			case OnEnable:
				m_currentEntityExecutionState = EntityExecutionState::Start;
				break;
			case Start:
				m_currentEntityExecutionState = EntityExecutionState::Update;
				break;
			case Update:
				m_currentEntityExecutionState = EntityExecutionState::OnDisable;
				break;
			case OnDisable:
				if(m_wantedEntityExecutionState == EntityExecutionState::PostDestroy) m_currentEntityExecutionState = EntityExecutionState::Destroy;
				else m_currentEntityExecutionState = EntityExecutionState::OnEnable;
				break;
			case Destroy:
				m_currentEntityExecutionState = EntityExecutionState::PostDestroy;
				break;
			}
		}
	}

} // Client

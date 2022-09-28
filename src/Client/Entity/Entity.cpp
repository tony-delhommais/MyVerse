//
// Created by Tony on 29/06/2022.
//

#include "Client/Entity/Entity.h"

#include "Client/Factories/EntityFactory.h"

#include "Client/Core/ApplicationCore.h"

namespace Client
{

	Entity::Entity()
	{
		m_localTransform = glm::mat4(1.0);

		RotateEuler(glm::vec3(0.0f, 180.0f, 0.0f));
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

	void Entity::Translate(const glm::vec3& p_position)
	{
		m_localTransform[3].xyz += p_position;
	}

	void Entity::Rotate(const glm::quat& p_rotation)
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		rotation *= p_rotation;

		ComposeLocalMatrix(position, rotation, scale);
	}

	void Entity::RotateEuler(const glm::vec3& p_eulerRotation, bool p_useDegree)
	{
		if (p_useDegree)
			Rotate(glm::quat(glm::radians(p_eulerRotation)));
		else
			Rotate(glm::quat(p_eulerRotation));
	}

	void Entity::Scale(const glm::vec3& p_scale)
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		scale *= p_scale;

		ComposeLocalMatrix(position, rotation, scale);
	}

	glm::vec3 Entity::Forward()
	{
		
		glm::quat worldRotation = GetModelRotation();

		float x = worldRotation.x;
		float y = worldRotation.y;
		float z = worldRotation.z;
		float w = worldRotation.w;

		return glm::vec3(2 * (x * z + w * y), 2 * (y * z - w * x), 1 - 2 * (x * x + y * y));
	}

	glm::vec3 Entity::Right()
	{
		glm::quat worldRotation = GetModelRotation();

		float x = worldRotation.x;
		float y = worldRotation.y;
		float z = worldRotation.z;
		float w = worldRotation.w;

		return glm::vec3(1 - 2 * (y * y + z * z), 2 * (x * y + w * z), 2 * (x * z - w * y)) * -1.0f;
	}

	glm::vec3 Entity::Up()
	{
		glm::quat worldRotation = GetModelRotation();

		float x = worldRotation.x;
		float y = worldRotation.y;
		float z = worldRotation.z;
		float w = worldRotation.w;

		return glm::vec3(2 * (x * y - w * z), 1 - 2 * (x * x + z * z), 2 * (y * z + w * x));
	}

	void Entity::UpdateExecution(float p_deltaTime)
	{
		bool notEqual = m_currentEntityExecutionState != m_wantedEntityExecutionState;

		switch (m_currentEntityExecutionState) {
		case Awake:
			if(notEqual)
				if(m_script)
					m_script->Awake();
			break;
		case OnEnable:
			if(notEqual)
				if (m_script)
					m_script->OnEnable();
			break;
		case Start:
			if(notEqual)
				if (m_script)
					m_script->Start();
			break;
		case Update:
			if (m_script)
				m_script->Update(p_deltaTime);
			break;
		case OnDisable:
			if(notEqual)
				if (m_script)
					m_script->OnDisable();
			break;
		case Destroy:
			if(notEqual)
				if (m_script)
					m_script->Destroy();
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
			glm::mat4 MVP = p_MVPParent * m_localTransform;

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

	void Entity::SetLocalTransform(const glm::mat4& p_localTransform)
	{
		m_localTransform = p_localTransform;
	}

	glm::mat4 Entity::GetLocalTransform()
	{
		return m_localTransform;
	}

	glm::mat4 Entity::GetModelMatrix()
	{
		if (GetParent())
		{
			return GetParent()->GetModelMatrix() * m_localTransform;
		}

		return m_localTransform;
	}

	glm::vec3 Entity::GetModelPosition()
	{
		return GetModelMatrix()[3].xyz;
	}

	glm::quat Entity::GetModelRotation()
	{
		return glm::toQuat(GetModelMatrix());
	}

	glm::vec3 Entity::GetModelEulerRotation(bool p_useDegree)
	{
		if (p_useDegree) return glm::degrees(glm::eulerAngles(GetModelRotation()));
		else return glm::eulerAngles(GetModelRotation());
	}

	glm::vec3 Entity::GetModelScale()
	{
		return glm::vec3(glm::length(glm::vec3(GetModelMatrix()[0])), glm::length(glm::vec3(GetModelMatrix()[1])), glm::length(glm::vec3(GetModelMatrix()[2])));
	}

	void Entity::SetPosition(const glm::vec3& p_position)
	{
		m_localTransform[3].xyz = p_position;
	}

	glm::vec3 Entity::GetPosition()
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		return position;
	}

	void Entity::SetRotation(const glm::quat& p_rotation)
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		rotation = p_rotation;

		ComposeLocalMatrix(position, rotation, scale);
	}

	glm::quat Entity::GetRotation()
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		return rotation;
	}

	void Entity::SetEulerRotation(const glm::vec3& p_eulerRotation, bool p_useDegree)
	{
		if(p_useDegree) SetRotation(glm::quat(glm::degrees(p_eulerRotation)));
		else SetRotation(glm::quat(p_eulerRotation));
	}

	glm::vec3 Entity::GetEulerRotation(bool p_useDegree)
	{
		if (p_useDegree) return glm::degrees(glm::eulerAngles(GetRotation()));
		else return glm::eulerAngles(GetRotation());
	}

	void Entity::SetScale(const glm::vec3& p_scale)
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		scale = p_scale;

		ComposeLocalMatrix(position, rotation, scale);
	}

	glm::vec3 Entity::GetScale()
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		DecomposeLocalMatrix(position, rotation, scale);

		return scale;
	}

	void Entity::SetMeshRenderer(std::shared_ptr<MeshRenderer> p_meshRenderer)
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
	}

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

	void Entity::DecomposeLocalMatrix(glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale)
	{
		Math::DecomposeMatrix(m_localTransform, p_position, p_rotation, p_scale);
	}

	void Entity::ComposeLocalMatrix(glm::vec3& p_position, glm::quat& p_rotation, glm::vec3& p_scale)
	{
		Math::ComposeMatrix(m_localTransform, p_position, p_rotation, p_scale);
	}

	bool Entity::s_isEntityMakerRegistered = EntityFactory::instance().Register("Entity", [](JsonObject& p_entityParameters) -> std::shared_ptr<Entity> {
		// Test if object have a Type Entity
		if (GetParameterFromJsonObject(p_entityParameters, "Type", "Null") != "Entity")
		{
#ifdef _DEBUG
			Debug::LogWarning("[Entity] Try to parse an Entity, but type is invalid");
#endif
			return nullptr;
		}

		auto newEntity = std::make_shared<Entity>();

		// Set if Entity is active
		newEntity->SetActive(GetParameterFromJsonObject(p_entityParameters, "IsActive", true));

		// Set the Tag of the Entity
		newEntity->SetTag(GetParameterFromJsonObject(p_entityParameters, "Tag", "Standard"));

		bool transformIsValid = true;

		JsonObject& position = GetParameterFromJsonObject(p_entityParameters, "Position", true, false);
		if (position == p_entityParameters || position.size() != 3)
			transformIsValid = false;

		JsonObject& rotation = GetParameterFromJsonObject(p_entityParameters, "Rotation", true, false);
		if (rotation == p_entityParameters || rotation.size() != 3)
			transformIsValid = false;

		JsonObject& scale = GetParameterFromJsonObject(p_entityParameters, "Scale", true, false);
		if (scale == p_entityParameters || rotation.size() != 3)
			transformIsValid = false;

		if (transformIsValid)
		{
			newEntity->Translate(glm::vec3(position[0], position[1], position[2]));
			newEntity->RotateEuler(glm::vec3(rotation[0], rotation[1], rotation[2]));
			newEntity->Scale(glm::vec3(scale[0], scale[1], scale[2]));
		}
#ifdef _DEBUG
		else
		{
			Debug::LogWarning("[Entity] Failed to parse a Transform, some invalid data");
		}
#endif

		// Add components to the new Entity
		JsonObject& componentsArray = GetParameterFromJsonObject(p_entityParameters, "Components", true, false);

		if (componentsArray != p_entityParameters)
		{
			for (auto& componentProprety : componentsArray)
			{
				auto componentType = GetParameterFromJsonObject(componentProprety, "Type", "Null");

				if (componentType == "MeshRenderer")
				{
					newEntity->SetMeshRenderer(MeshRenderer::Make(componentProprety));
				}
				else if (componentType == "Script")
				{
					newEntity->SetScript(ScriptFactory::instance().Make(componentProprety));
				}
			}
		}

		// Add childs to the new Entity
		JsonObject& childs_array = GetParameterFromJsonObject(p_entityParameters, "Childs", true, false);

		if (childs_array != p_entityParameters && !childs_array.empty())
		{
			for (JsonObject& jsonChild : childs_array)
			{
				auto newChild = EntityFactory::instance().Make<Entity>(jsonChild);

				if (!newChild)
				{
#ifdef _DEBUG
					Debug::LogWarning("[Entity] Failed to parse a Child for an Entity");
#endif
					continue;
				}

				newEntity->AddChild(newChild);
			}
		}

		return newEntity;
	});

} // Client

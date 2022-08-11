//
// Created by Tony on 29/06/2022.
//

#include "Core/Entity/Entity.h"

#include "Core/CoreClass/ApplicationCore.h"

namespace Core
{

Entity::Entity()
{
	m_localTransform = glm::mat4(1.0);

	m_localPosition = glm::vec3(0.0);
	m_localRotation = glm::vec3(0.0);
	m_localScale = glm::vec3(1.0);

	ComputeLocalTransform();
}

Entity::~Entity()
{
	m_childrens.clear();

	m_scripts.clear();
}

std::shared_ptr<Entity> Entity::Make(JsonObject& p_entityParameters)
{
	// Test if object have a Type Entity
	if (GetParameterFromJsonObject(p_entityParameters, "Type", "Null") != "Entity")
	{
#ifdef _DEBUG
		Debug::LogWarning("[Entity] Try to parse a Entity, but type is invalid");
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

	if (!transformIsValid)
	{
#ifdef _DEBUG
		Debug::LogWarning("[Entity] Failed to parse a Transform, some invalid data");
#endif
	}
	else
	{
		newEntity->SetLocalPosition(glm::vec3(position[0], position[1], position[2]));
		newEntity->SetLocalEulerRotation(glm::vec3(rotation[0], rotation[1], rotation[2]));
		newEntity->SetLocalScale(glm::vec3(scale[0], scale[1], scale[2]));
	}

	// Add components to the new Entity
	JsonObject& componentsArray = GetParameterFromJsonObject(p_entityParameters, "Components", true, false);

	if (componentsArray != p_entityParameters)
	{
		for (auto& componentProprety : componentsArray)
		{
			auto componentType = GetParameterFromJsonObject(componentProprety, "Type", "Null");

			if (componentType == "Null") continue;

			if (componentType == "Camera")
			{
				auto camera = Camera::Make(componentProprety);
				if (!camera) continue;

				camera->SetEntity(newEntity);

				newEntity->m_camera = camera;

				continue;
			}

			if (componentType == "MeshRenderer")
			{
				auto meshRenderer = MeshRenderer::Make(componentProprety);
				if (!meshRenderer) continue;

				meshRenderer->SetEntity(newEntity);

				newEntity->m_meshRenderer = meshRenderer;

				continue;
			}

			if (componentType == "Script")
			{
				auto script = ScriptFactory::instance().Make(componentProprety);
				if (!script) continue;

				script->SetEntity(newEntity);

				newEntity->m_scripts.push_back(script);

				continue;
			}
		}
	}

	// Add childs to the new Entity
	JsonObject& childs_array = GetParameterFromJsonObject(p_entityParameters, "Childs", true, false);
	if (childs_array != p_entityParameters && !childs_array.empty())
	{
		for (JsonObject& jsonChild : childs_array)
		{
		auto newChild = Entity::Make(jsonChild);

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
}

std::shared_ptr<Entity> Entity::SetParent(std::shared_ptr<Entity> p_newParent, bool p_keepWorldTransform)
{
	if(p_keepWorldTransform)
	{
		auto currentWorldPosition = GetWorldPosition();
		auto currentWorldRotation = GetWorldEulerRotation();
		auto currentWorldScale = GetWorldScale();

		if(!p_newParent)
		{
			SetLocalPosition(currentWorldPosition);
			SetLocalEulerRotation(currentWorldRotation);
			SetLocalScale(currentWorldScale);
		}
		else
		{
			SetLocalPosition(currentWorldPosition - p_newParent->GetWorldPosition());
			SetLocalEulerRotation(currentWorldRotation - p_newParent->GetWorldEulerRotation());
			SetLocalScale(currentWorldScale - p_newParent->GetWorldScale());
		}
	}

	if(m_parent) // If this has a parent
		m_parent->RemoveChild(shared_from_this());
	else // Otherwise parent is the scene
		ApplicationCore::instance().GetActiveScene()->RemoveLocalEntity(shared_from_this());

	if(p_newParent) // If new parent is not Null
		p_newParent->AddChild(shared_from_this());
	else // Otherwise new parent is scene
		ApplicationCore::instance().GetActiveScene()->AddLocalEntity(shared_from_this());

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
	m_localPosition += p_position;

	ComputeLocalTransform();
}

void Entity::Rotate(const glm::quat& p_rotation)
{
	m_localRotation += glm::eulerAngles(p_rotation);

	ComputeLocalTransform();
}

void Entity::RotateEuler(const glm::vec3& p_eulerRotation, bool p_useDegree)
{
	if (p_useDegree) m_localRotation += glm::radians(p_eulerRotation);
	else m_localRotation += p_eulerRotation;

	ComputeLocalTransform();
}

void Entity::Scale(const glm::vec3& p_scale)
{
	m_localScale *= p_scale;

	ComputeLocalTransform();
}

glm::vec3 Entity::Forward()
{
	glm::quat worldRotation = GetWorldRotation();

	float x = worldRotation.x;
	float y = worldRotation.y;
	float z = worldRotation.z;
	float w = worldRotation.w;

	return glm::vec3(2 * (x * z + w * y), 2 * (y * z - w * x), 1 - 2 * (x * x + y * y));
}

glm::vec3 Entity::Right()
{
	glm::quat worldRotation = GetWorldRotation();

	float x = worldRotation.x;
	float y = worldRotation.y;
	float z = worldRotation.z;
	float w = worldRotation.w;

	return glm::vec3(1 - 2 * (y * y + z * z), 2 * (x * y + w * z), 2 * (x * z - w * y)) * -1.0f;
}

glm::vec3 Entity::Up()
{
	glm::quat worldRotation = GetWorldRotation();

	float x = worldRotation.x;
	float y = worldRotation.y;
	float z = worldRotation.z;
	float w = worldRotation.w;

	return glm::vec3(2 * (x * y - w * z), 1 - 2 * (x * x + z * z), 2 * (y * z + w * x));
}

void Entity::InstantiatePrefab(const UUIDv4::UUID& p_prefabUuid)
{
	auto prefab = RessourceManager::FindPrefab(p_prefabUuid);

	std::shared_ptr<Entity> newChild = prefab->InstantiateNew();
	newChild->SetPrefabReferenceUuid(p_prefabUuid);

	AddChild(newChild);
}

void Entity::DestroyEntity()
{
	m_wantedEntityExecutionState = EntityExecutionState::PostDestroy;

	for (auto& child : m_childrens)
	{
		child->DestroyEntity();
	}
}

bool Entity::AddComponent(std::shared_ptr<Component> p_component)
{
	if (!p_component)
		return false;

	// Test the type of the Component
	auto meshRenderer = std::dynamic_pointer_cast<MeshRenderer>(p_component);
	if (meshRenderer)
	{
		if (m_meshRenderer)
			return false;

		m_meshRenderer = meshRenderer;

		return true;
	}

	// Test the type of the Component
	auto camera = std::dynamic_pointer_cast<Camera>(p_component);
	if (camera)
	{
		if (m_camera)
			return false;

		m_camera = camera;

		return true;
	}

	// Test the type of the Component
	auto script = std::dynamic_pointer_cast<Script>(p_component);
	if (script)
	{
		m_scripts.push_back(script);

		return true;
	}

	return false;
}

void Entity::UpdateExecution(float p_deltaTime)
{
	bool notEqual = m_currentEntityExecutionState != m_wantedEntityExecutionState;

	switch (m_currentEntityExecutionState) {
	case Awake:
		if(notEqual) for (auto& script : m_scripts) script->Awake();
		break;
	case OnEnable:
		if(notEqual) for (auto& script : m_scripts) script->OnEnable();
		break;
	case Start:
		if(notEqual) for (auto& script : m_scripts) script->Start();
		break;
	case Update:
		for (auto& script : m_scripts) script->Update(p_deltaTime);
		break;
	case OnDisable:
		if(notEqual) for (auto& script : m_scripts) script->OnDisable();
		break;
	case Destroy:
		if(notEqual) for (auto& script : m_scripts) script->Destroy();
		break;
	default:
		break;
	}

	bool destroyPrevious = false;
	for (auto it = m_childrens.begin(); it != m_childrens.end(); it++)
	{
		if (destroyPrevious)
		{
			m_childrens.erase(--it);

			destroyPrevious = false;
		}

		it->get()->UpdateExecution(p_deltaTime);

		if (it->get()->GetCurrentEntityExecutionState() == EntityExecutionState::PostDestroy)
		{
			destroyPrevious = true;
		}
	}

	DetermineNextEntityState();
}

void Entity::Render()
{
	if (m_isActive)
	{
		if (m_meshRenderer)
		{
			if (m_shaderModelMatrixUniformLocation == -1)
			{
				m_shaderModelMatrixUniformLocation = ApplicationCore::instance().GetActiveShader()->FindUniformLocation("ModelMatrix");
			}
			
			ApplicationCore::instance().GetActiveShader()->SetUniformMat4(m_shaderModelMatrixUniformLocation, GetWorldTransform());

			m_meshRenderer->Render();
		}

		for (auto& child : m_childrens)
		{
			child->Render();
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

const glm::mat4& Entity::GetLocalTransform()
{
	ComputeLocalTransform();

	return m_localTransform;
}

const glm::mat4& Entity::GetWorldTransform()
{
	if (m_getWorldTransformLastCompute == ApplicationCore::instance().GetFrameCount()) return m_worldTransform;
	m_getWorldTransformLastCompute = ApplicationCore::instance().GetFrameCount();

	m_worldTransform = m_localTransform;

	if (GetParent())
	{
		m_worldTransform = GetParent()->GetWorldTransform() * m_localTransform;
	}

	return m_worldTransform;
}

void Entity::SetLocalPosition(const glm::vec3& p_position)
{
	m_localPosition = p_position;

	ComputeLocalTransform();
}

const glm::vec3& Entity::GetLocalPosition()
{
	return m_localPosition;
}

const glm::vec3& Entity::GetWorldPosition()
{
	DecomposeWorldTransform();

	return m_worldPosition;
}

void Entity::SetLocalRotation(const glm::quat& p_rotation)
{
	m_localRotation = glm::eulerAngles(p_rotation);

	ComputeLocalTransform();
}

glm::quat Entity::GetLocalRotation()
{
	return glm::quat(m_localRotation);
}

glm::quat Entity::GetWorldRotation()
{
	DecomposeWorldTransform();

	return glm::quat(m_worldRotation);
}

void Entity::SetLocalEulerRotation(const glm::vec3& p_eulerRotation, bool p_useDegree)
{
	if (p_useDegree) m_localRotation = glm::radians(p_eulerRotation);
	else m_localRotation = p_eulerRotation;

	ComputeLocalTransform();
}

glm::vec3 Entity::GetLocalEulerRotation(bool p_useDegree)
{
	if (p_useDegree) return glm::degrees(m_localRotation);
	else return m_localRotation;
}

glm::vec3 Entity::GetWorldEulerRotation(bool p_useDegree)
{
	DecomposeWorldTransform();

	if (p_useDegree) return glm::degrees(m_worldRotation);
	else return m_worldRotation;
}

void Entity::SetLocalScale(const glm::vec3& p_scale)
{
	m_localScale = p_scale;

	ComputeLocalTransform();
}

const glm::vec3& Entity::GetLocalScale()
{
	return m_localScale;
}

const glm::vec3& Entity::GetWorldScale()
{
	DecomposeWorldTransform();

	return m_worldScale;
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

void Entity::ComputeLocalTransform()
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0), m_localPosition);
	glm::mat4 rotate = glm::mat4_cast(glm::quat(m_localRotation));
	glm::mat4 scale = glm::scale(glm::mat4(1.0), m_localScale);

	m_localTransform = translate * rotate * scale;
}

void Entity::DecomposeWorldTransform()
{
	if (m_decomposeWorldTransformLastCompute == ApplicationCore::instance().GetFrameCount()) return;
	m_decomposeWorldTransformLastCompute = ApplicationCore::instance().GetFrameCount();

	glm::vec3 skew;
	glm::vec4 perspective;
	glm::quat rotation;

	glm::decompose(GetWorldTransform(), m_worldScale, rotation, m_worldPosition, skew, perspective);
	m_worldRotation = glm::eulerAngles(rotation);
}

} // Core

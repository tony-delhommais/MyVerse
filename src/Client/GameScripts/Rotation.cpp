//
// Created by Tony on 29/06/2022.
//

#include "Client/GameScripts/Rotation.h"

void Rotation::Update(float p_deltaTime)
{
	float angle = m_indice * p_deltaTime * glm::half_pi<float>();
	GetEntity()->GetTransform()->RotateEuler(glm::vec3(0.0, angle, 0.0), false);
}

void Rotation::SetIndice(float p_indice)
{
	m_indice = p_indice;
}

bool Rotation::s_isRegistered = ScriptFactory::instance().Register("Rotation", [](JsonObject& parameters) {
	auto script = std::make_shared<Rotation>();

	script->m_indice = GetParameterFromJsonObject(parameters, "Indice", script->m_indice);

	return script;
});

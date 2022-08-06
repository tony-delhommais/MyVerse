//
// Created by Tony on 29/06/2022.
//

#include "Client/Scripts/Rotation.h"

void Rotation::Update(float p_deltaTime)
{
	GetEntity()->RotateEuler(glm::vec3(0.0, m_indice * p_deltaTime * glm::half_pi<float>(), 0.0), false);
}

void Rotation::SetIndice(float p_indice)
{
	m_indice = p_indice;
}

bool Rotation::s_isRegistered = ScriptFactory::instance().Register("Rotation", [](JsonObject& parameters)
	{
		auto script = std::make_shared<Rotation>();

		script->m_indice = GetParameterFromJsonObject(parameters, "Indice", script->m_indice);

		return script;
	});

//
// Created by Tony on 29/06/2022.
//

#include "Client/Components/Script/ScriptFactory.h"

namespace Client
{

	ScriptFactory& ScriptFactory::instance()
	{
		static ScriptFactory instance;
		return instance;
	}

	bool ScriptFactory::Register(const std::string& p_scriptName, std::function<std::shared_ptr<Script>(JsonObject& p_scriptParameters)> p_scriptBuilder)
	{
		if (m_scriptsBuilders.find(p_scriptName) != std::end(m_scriptsBuilders))
		{
			return false;
		}
		m_scriptsBuilders[p_scriptName] = p_scriptBuilder;

		return true;
	}

	std::shared_ptr<Script> ScriptFactory::Make(JsonObject& p_componentProprety)
	{
		bool scriptIsValid = true;

		if (GetParameterFromJsonObject(p_componentProprety, "Type", "Null") != "Script")
			scriptIsValid = false;

		std::string name = GetParameterFromJsonObject(p_componentProprety, "Name", "Null");
		if (name == "Null")
			scriptIsValid = false;

		if (!scriptIsValid)
		{
			return nullptr;
		}

		JsonObject parameters = GetParameterFromJsonObject(p_componentProprety, "Parameters", false, true);
		if (parameters == p_componentProprety)
			parameters = {};

		auto script = m_scriptsBuilders[name](parameters);

#ifdef _DEBUG
		if (!script)
			Debug::LogWarning("[ScriptFactory] Failed to instanciate a Script");
#endif

		return script;
	}

} // Client

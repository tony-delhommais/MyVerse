//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_SCRIPT_FACTORY_H
#define MYVERSE_SCRIPT_FACTORY_H

#include "Core/Utils/JsonUtils.h"

#include "Core/Components/Script.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

	class ScriptFactory
	{
	private:
		ScriptFactory() = default;
		~ScriptFactory() = default;

	public:
		static ScriptFactory& instance();

		bool Register(const std::string& p_scriptName, std::function<std::shared_ptr<Script>(JsonObject& p_scriptParameters)> p_scriptBuilder);

		std::shared_ptr<Script> Make(JsonObject& p_componentProprety);

	private:
		std::map<std::string, std::function<std::shared_ptr<Script>(JsonObject& p_scriptParameters)>> m_scriptsBuilders;
	};

} // Core

#endif // MYVERSE_SCRIPT_FACTORY_H

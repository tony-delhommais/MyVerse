//
// Created by Tony on 05/11/2022.
//

#include "Client/Common/ScriptManager.h"

namespace Client
{

	ScriptManager& ScriptManager::instance()
	{
		static ScriptManager instance;
		return instance;
	}

	void ScriptManager::UpdateExecution(float p_deltaTime)
	{
		std::list<std::shared_ptr<ScriptExecutionState>>::iterator scriptsIterator = m_scripts.begin();

		while (scriptsIterator != m_scripts.end())
		{
			std::list<std::shared_ptr<ScriptExecutionState>>::iterator scriptToTest = scriptsIterator;

			scriptsIterator++;

			if (scriptToTest->use_count() == 1)
			{
				m_scripts.erase(scriptToTest);
				continue;
			}

			scriptToTest->get()->UpdateExecution(p_deltaTime);
		}
	}

	void ScriptManager::AddExecutionScript(std::shared_ptr<ScriptExecutionState> p_newManagedScript)
	{
		m_scripts.push_back(p_newManagedScript);
	}

} // Client

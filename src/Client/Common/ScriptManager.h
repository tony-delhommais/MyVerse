//
// Created by Tony on 05/11/2022.
//

#ifndef MYVERSE_SCRIPT_MANAGER_H
#define MYVERSE_SCRIPT_MANAGER_H

#include "Client/Utils/Utils.h"

#include "Client/Components/ScriptExecutionState.h"

namespace Client
{

	class ScriptManager
	{
	private:
		ScriptManager() = default;
		~ScriptManager() = default;

	public:
		static ScriptManager& instance();

		void UpdateExecution(float p_deltaTime);

		void AddExecutionScript(std::shared_ptr<ScriptExecutionState> p_newManagedScript);

	private:
		std::list<std::shared_ptr<ScriptExecutionState>> m_scripts;
	};

} // Client

#endif // MYVERSE_SCRIPT_MANAGER_H

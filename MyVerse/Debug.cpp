//
// Created by Tony on 29/06/2022.
//

#include "Debug.h"

namespace Client
{

	void Debug::LogInfo(const std::string& p_log)
	{
		std::cout << "[Info] " << p_log << std::endl;
	}

	void Debug::LogWarning(const std::string& p_log)
	{
		std::cout << "[Warning] " << p_log << std::endl;
	}

	void Debug::LogError(const std::string& p_log)
	{
		std::cout << "[Error] " << p_log << std::endl;
	}

} // Client

//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_DEBUG_H
#define MYVERSE_DEBUG_H

#include "Utils.h"

namespace Client
{

	class Debug
	{
	public:
		static void LogInfo(const std::string& p_log);

		static void LogWarning(const std::string& p_log);

		static void LogError(const std::string& p_log);
	};

} // Client

#endif // MYVERSE_DEBUG_H

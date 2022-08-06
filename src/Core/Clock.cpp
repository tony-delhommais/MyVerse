//
// Created by Tony on 29/06/2022.
//

#include "Core/Clock.h"

namespace Core
{

	Clock& Clock::instance()
	{
		static Clock instance;
		return instance;
	}

	void Clock::ResetStopWatch(const std::string& p_stopWatchName)
	{
		auto stopWatch = m_stopWatches.find(p_stopWatchName);

		if (stopWatch == m_stopWatches.end())
		{
			m_stopWatches.insert(std::map<std::string, __int64>::value_type(p_stopWatchName, (__int64)(glfwGetTime() * 1000)));
			
			stopWatch = m_stopWatches.find(p_stopWatchName);
		}

		stopWatch->second = (__int64)(glfwGetTime() * 1000000);
	}

	float Clock::GetStopWatchTime(const std::string& p_stopWatchName)
	{
		return GetMillisecondStopWatchTime(p_stopWatchName) / 1000.0f;
	}

	float Clock::GetMillisecondStopWatchTime(const std::string& p_stopWatchName)
	{
		return GetNanosecondStopWatchTime(p_stopWatchName) / 1000.0f;
	}

	__int64 Clock::GetNanosecondStopWatchTime(const std::string& p_stopWatchName)
	{
		auto stopWatch = m_stopWatches.find(p_stopWatchName);

		if (stopWatch == m_stopWatches.end())
		{
			ResetStopWatch(p_stopWatchName);

			stopWatch = m_stopWatches.find(p_stopWatchName);
		}

		return (__int64)(glfwGetTime() * 1000000) - stopWatch->second;
	}

} // Core

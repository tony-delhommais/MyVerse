//
// Created by Tony on 29/06/2022.
//

#include "Client/Common/Clock.h"

namespace Client
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
			m_stopWatches.insert(std::map<std::string, long long>::value_type(p_stopWatchName, (long long)(glfwGetTime() * 1000000)));
			
			stopWatch = m_stopWatches.find(p_stopWatchName);
		}

		stopWatch->second = (long long)(glfwGetTime() * 1000000);
	}

	float Clock::GetStopWatchTime(const std::string& p_stopWatchName)
	{
		return GetMillisecondStopWatchTime(p_stopWatchName) / 1000.0f;
	}

	float Clock::GetMillisecondStopWatchTime(const std::string& p_stopWatchName)
	{
		return GetMicrosecondStopWatchTime(p_stopWatchName) / 1000.0f;
	}

	long long Clock::GetMicrosecondStopWatchTime(const std::string& p_stopWatchName)
	{
		auto stopWatch = m_stopWatches.find(p_stopWatchName);

		if (stopWatch == m_stopWatches.end())
		{
			ResetStopWatch(p_stopWatchName);

			stopWatch = m_stopWatches.find(p_stopWatchName);
		}

		return (long long)(glfwGetTime() * 1000000) - stopWatch->second;
	}

} // Client

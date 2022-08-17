//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_CLOCK_H
#define MYVERSE_CLOCK_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/GraphicsUtils.h"

namespace Core
{

	class Clock
	{
	private:
		Clock() = default;
		~Clock() = default;

	public:
		static Clock& instance();

		void ResetStopWatch(const std::string& p_stopWatchName);

	public:
		float GetStopWatchTime(const std::string& p_stopWatchName);
		float GetMillisecondStopWatchTime(const std::string& p_stopWatchName);
		long long GetMicrosecondStopWatchTime(const std::string& p_stopWatchName);

	private:
		std::map<std::string, long long> m_stopWatches;
	};

} // Core

#endif // MYVERSE_CLOCK_H

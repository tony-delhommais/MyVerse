//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_CLOCK_H
#define MYVERSE_CLOCK_H

#include "Core/Utils/Utils.h"
#include "Core/Utils/GraphicsUtils.h"

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
		__int64 GetNanosecondStopWatchTime(const std::string& p_stopWatchName);

	private:
		std::map<std::string, __int64> m_stopWatches;
	};

} // Core

#endif // MYVERSE_CLOCK_H

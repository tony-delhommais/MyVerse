//
// Created by Tony on 29/06/2022.
//

#include "Client/Utils/Utils.h"

namespace Core
{

	std::vector<std::string> SplitString(const std::string& p_text, const std::string& p_delims)
	{
		//https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
		std::vector<std::string> tokens;
		std::size_t start = p_text.find_first_not_of(p_delims), end = 0;

		while ((end = p_text.find_first_of(p_delims, start)) != std::string::npos)
		{
			tokens.push_back(p_text.substr(start, end - start));
			start = p_text.find_first_not_of(p_delims, end);
		}
		if (start != std::string::npos)
			tokens.push_back(p_text.substr(start));

		return tokens;
	}

} // Core

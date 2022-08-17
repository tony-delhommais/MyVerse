//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_UTILS_H
#define MYVERSE_UTILS_H

#include "uuid_v4.h"

#include <list>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <memory>

namespace Core
{

	std::vector<std::string> SplitString(const std::string& p_text, const std::string& p_delims);

} // Core

#endif // MYVERSE_UTILS_H

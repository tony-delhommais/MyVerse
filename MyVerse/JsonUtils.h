//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_JSON_UTILS_H
#define MYVERSE_JSON_UTILS_H

#include <string>
#include <fstream>
#include <filesystem>

#include "nlohmann/json.hpp"

namespace Client
{

	typedef nlohmann::json JsonObject;

	JsonObject LoadJsonFile(const std::filesystem::path& p_jsonFilePath);
	bool WriteJsonFile(const std::filesystem::path& p_jsonFilePath, JsonObject& p_data);

	int GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, int p_default);
	int GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, int p_default);

	float GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, float p_default);
	float GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, float p_default);

	bool GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, bool p_default);
	bool GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, bool p_default);

	std::string GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, const char* p_default);
	std::string GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, const std::string& p_default);

	JsonObject& GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, bool p_isArray, bool p_isObject);
	JsonObject& GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, bool p_isArray, bool p_isObject);

} // Client

#endif // MYVERSE_JSON_UTILS_H

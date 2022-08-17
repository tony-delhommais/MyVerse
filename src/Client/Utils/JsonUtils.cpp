//
// Created by Tony on 29/06/2022.
//

#include "Client/Utils/JsonUtils.h"

namespace Core
{

	JsonObject LoadJsonFile(const std::filesystem::path& p_jsonFilePath)
	{
		if(!std::filesystem::exists(p_jsonFilePath))
			return JsonObject();

		std::fstream jsonFile;

		jsonFile.open(p_jsonFilePath.string(), std::ios::in);

		JsonObject jsonObject;
		jsonFile >> jsonObject;
		jsonFile.close();

		return jsonObject;
	}

	int GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, int p_default)
	{
		return GetParameterFromJsonObject(p_jsonObject, std::string(p_parameter), p_default);
	}

	int GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, int p_default)
	{
		if (!p_jsonObject.contains(p_parameter))
			return p_default;

		if (!p_jsonObject[p_parameter].is_number_integer())
			return p_default;

		return static_cast<int>(p_jsonObject[p_parameter]);
	}

	float GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, float p_default)
	{
		return GetParameterFromJsonObject(p_jsonObject, std::string(p_parameter), p_default);
	}

	float GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, float p_default)
	{
		if (!p_jsonObject.contains(p_parameter))
			return p_default;

		if (!p_jsonObject[p_parameter].is_number_float())
			return p_default;

		return static_cast<float>(p_jsonObject[p_parameter]);
	}

	bool GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, bool p_default)
	{
		return GetParameterFromJsonObject(p_jsonObject, std::string(p_parameter), p_default);
	}

	bool GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, bool p_default)
	{
		if (!p_jsonObject.contains(p_parameter))
			return p_default;

		if (!p_jsonObject.contains(p_parameter))
			return p_default;

		return static_cast<bool>(p_jsonObject[p_parameter]);
	}

	std::string GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, const char* p_default)
	{
		return GetParameterFromJsonObject(p_jsonObject, std::string(p_parameter), std::string(p_default));
	}

	std::string GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, const std::string& p_default)
	{
		if (!p_jsonObject.contains(p_parameter))
			return static_cast<std::string>(p_default);

		if (!p_jsonObject[p_parameter].is_string())
			return static_cast<std::string>(p_default);

		return static_cast<std::string>(p_jsonObject[p_parameter]);
	}

	JsonObject& GetParameterFromJsonObject(JsonObject& p_jsonObject, const char* p_parameter, bool p_isArray, bool p_isObject)
	{
		return GetParameterFromJsonObject(p_jsonObject, std::string(p_parameter), p_isArray, p_isObject);
	}

	JsonObject& GetParameterFromJsonObject(JsonObject& p_jsonObject, const std::string& p_parameter, bool p_isArray, bool p_isObject)
	{
		if (!p_jsonObject.contains(p_parameter))
			return p_jsonObject;

		if (p_isArray == p_isObject)
			return p_jsonObject;

		if (p_isArray && !p_jsonObject[p_parameter].is_array())
			return p_jsonObject;

		if (p_isObject && !p_jsonObject[p_parameter].is_object())
			return p_jsonObject;

		return p_jsonObject[p_parameter];
	}

} // Core

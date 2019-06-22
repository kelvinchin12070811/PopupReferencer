//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <map>
#include <any>
#include "libs/nlohmann/json.hpp"

class ConfigMng
{
public:
	static ConfigMng* getInstance();

	template <typename T>
	T get(const std::string& key);

	bool has(const std::string& key);
	void syncConfigs();

	template <typename T>
	void set(const std::string& key,  const T& value);
private:
	ConfigMng();
	~ConfigMng();
	
private:
	bool changed{ false };
	nlohmann::json settings;
	nlohmann::json defValues;
};

template<typename T>
inline T ConfigMng::get(const std::string& key)
{
	auto result = settings[key];
	if (result.is_null())
	{
		return defValues[key].get<T>();
	}
	return result.get<T>();
}

template<typename T>
inline void ConfigMng::set(const std::string& key, const T& value)
{
	changed = true;
	settings[key] = value;
}

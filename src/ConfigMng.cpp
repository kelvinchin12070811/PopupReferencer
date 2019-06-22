//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <fstream>
#include <qdebug.h>
#include <qstringlist.h>
#include <sstream>
#include "ConfigMng.hpp"

ConfigMng* ConfigMng::getInstance()
{
	static ConfigMng instance;
	return &instance;
}

bool ConfigMng::has(const std::string& key)
{
	return getValue(key).is_null();
}

void ConfigMng::syncConfigs()
{
	if (!changed) return;
	
	std::ofstream output;
	output.open("config.json", std::ios::out);
	if (!output.is_open()) throw std::runtime_error{ "can't open config file" };
	output << settings.dump(4);
	output.close();

	changed = false;
}

ConfigMng::ConfigMng()
{
	 std::ifstream file;
	 file.open("config.json", std::ios::in);
	 if (file.is_open())
	 {
		 std::ostringstream buf;
		 buf << file.rdbuf();
		 settings = nlohmann::json::parse(buf.str());

	 }
	 else
	 {
		settings = nlohmann::json::value_type{
			{ "display", nlohmann::json::value_type{ "high_dpi_scaling", true } },
			{ "system", nlohmann::json::value_type{ "lang", "english" } }
		};

		settings = R"({"display": {"high_dpi_scaling": true}, "system": {"lang": "english"}})"_json;
	 }
	 file.close();
}

ConfigMng::~ConfigMng()
{
	syncConfigs();
}

nlohmann::json::value_type& ConfigMng::getValue(const std::string& key)
{
	QStringList ids = QString::fromStdString(key).split(".");
	nlohmann::json::value_type* value{ nullptr };

	for (auto&& itr : ids)
	{
		if (value == nullptr)
		{
			value = &settings[itr.toStdString()];
		}
		else
		{
			value = &(*value)[itr.toStdString()];
		}
	}

	return *value;
}

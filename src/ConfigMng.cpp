//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <fstream>
#include <qdebug.h>
#include <sstream>
#include "ConfigMng.hpp"

ConfigMng* ConfigMng::getInstance()
{
	static ConfigMng instance;
	return &instance;
}

bool ConfigMng::has(const std::string& key)
{
	return settings[key].is_null();
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
	 file.close();

	defValues = nlohmann::json{
		{ "display.high_dpi_scaling", true },
		{ "system.lang", "english" }
	};
}

ConfigMng::~ConfigMng()
{
	syncConfigs();
}

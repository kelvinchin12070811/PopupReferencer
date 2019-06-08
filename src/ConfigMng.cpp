//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <qdebug.h>
#include "ConfigMng.hpp"

ConfigMng* ConfigMng::getInstance()
{
	static ConfigMng instance;
	return &instance;
}

QVariant ConfigMng::get(const QString& key)
{
	auto result = settings->value(key);
	if (result.isNull())
	{
		try
		{
			return defValues.at(key);
		}
		catch (std::exception & e)
		{
			return result;
		}
	}
	return result;
}

bool ConfigMng::has(const QString& key)
{
	return settings->contains(key);
}

void ConfigMng::syncConfigs()
{
	settings->sync();
}

void ConfigMng::set(const QString& key, const QVariant& value)
{
	settings->setValue(key, value);
}

ConfigMng::ConfigMng()
{
	settings = std::make_unique<QSettings>("config.ini", QSettings::IniFormat);

	defValues.insert({
		{ "display.high_dpi_scaling", QVariant{ true } },
		{ "system.lang", QVariant{ QString{ "english" } } }
	});
}

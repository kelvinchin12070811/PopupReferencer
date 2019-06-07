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

QVariant ConfigMng::get(const QString& key, const QVariant& defaultValue)
{
	return settings->value(key, defaultValue);
}

bool ConfigMng::has(const QString& key)
{
	return settings->contains(key);
}

QVariant ConfigMng::init(const QString& key, const QVariant& value)
{
	auto result = get(key);
	if (result.isNull())
	{
		set(key, value);
		result = value;
	}
	return result;
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
}

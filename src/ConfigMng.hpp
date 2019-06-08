//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <map>
#include <memory>
#include <qvariant.h>
#include <qsettings.h>

class ConfigMng
{
public:
	static ConfigMng* getInstance();

	QVariant get(const QString& key);
	bool has(const QString& key);
	void syncConfigs();
	void set(const QString& key, const QVariant& value);
private:
	ConfigMng();
	~ConfigMng() = default;
	
private:
	std::unique_ptr<QSettings> settings;
	std::map<QString, QVariant> defValues;
};
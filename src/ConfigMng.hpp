//===========================================================================================================
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0.If a copy of the MPL was not distributed with this
// file, You can obtain one at http ://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <memory>
#include <qvariant.h>
#include <qsettings.h>

class ConfigMng
{
public:
	static ConfigMng* getInstance();

	QVariant get(const QString& key, const QVariant& value = QVariant{});
	bool has(const QString& key);
	QVariant init(const QString& key, const QVariant& defaultValue = QVariant{});
	void syncConfigs();
	void set(const QString& key, const QVariant& value);
private:
	ConfigMng();
	~ConfigMng() = default;
	
private:
	std::unique_ptr<QSettings> settings;
};
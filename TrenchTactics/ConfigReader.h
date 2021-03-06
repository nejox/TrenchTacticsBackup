#pragma once
#include "jsoncpp/dist/json/json.h"
#include "UnitConf.h"
#include "MapConf.h"
#include "TechConf.h"
#include "TileConf.h"
#include "BalanceConf.h"
#include "ButtonConf.h"
#include "MenuBarConf.h"
#include <string>
#include <map>


/**
 * ConfigReader class which enables reading configs
 * Provides a singelton instance
 * Then provides all instances of different configurations
 */
class ConfigReader
{
public:
	~ConfigReader();
	ConfigReader(const ConfigReader&) = delete;
	ConfigReader& operator=(const ConfigReader&) = delete;
	ConfigReader(ConfigReader&&) = delete;
	ConfigReader& operator=(ConfigReader&&) = delete;

	static auto& instance() {
		static ConfigReader confReader;
		return confReader;
	}

	std::shared_ptr<UnitConf> getUnitConf(int id)
	{
		return this->unitConfMap[id];
	}

	std::shared_ptr<BalanceConf> getBalanceConf() {
		return this->balanceConf;
	}

	std::shared_ptr<MapConf> getMapConf() {
		return this->mapConf;
	}

	std::shared_ptr<TechConf> getTechnicalConf() {
		return this->techConf;
	}

	std::shared_ptr<TileConf> getTileConf() {
		return this->tileConf;
	}
	std::shared_ptr<ButtonConf> getButtonConf() {
		return this->buttonConf;
	}
	std::shared_ptr<MenuBarConf> getMenuBarConf() {
		return this->menuBarConf;
	}

	void initConfigurations();

private:
	ConfigReader();
	std::map<int, std::shared_ptr<UnitConf>> unitConfMap;
	std::shared_ptr<BalanceConf> balanceConf;
	std::shared_ptr<MapConf> mapConf;
	std::shared_ptr<TechConf> techConf;
	std::shared_ptr<TileConf> tileConf;
	std::shared_ptr<ButtonConf> buttonConf;
	std::shared_ptr<MenuBarConf> menuBarConf;
	Json::Value getJsonRootFromFile(std::string filePath);
	std::shared_ptr<MapConf> createMapConf();
	std::shared_ptr<TechConf> createTechConf();
	std::shared_ptr<BalanceConf> createBalanceConf();
	std::shared_ptr<TileConf> createTileConf();
	std::shared_ptr<ButtonConf> createButtonConf();
	std::shared_ptr<MenuBarConf> createMenuBarConf();
	std::map<int, std::shared_ptr<UnitConf>> createUnitConfMap();
};
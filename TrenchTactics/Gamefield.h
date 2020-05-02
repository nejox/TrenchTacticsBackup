#pragma once
#include "FieldTile.h"
#include "PlayerTile.h"
#include "MenuTile.h"
#include "MouseClickEvent.h"
#include "RendererImpl.h"
#include "MapConf.h"
#include "stdlib.h"
#include <vector>
#include <ctime>
#include "Gamephases.h"
#include "SpriteMarker.h"

/**
 * Gamefield class for generating and holding the playingfield
 */
class Gamefield {
private:
	static const int defaultXSizeField = 18;
	static const int defaultYSizeField = 12;

	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> menuBar;
	std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> headquarterTilePlayerBlue;
	std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> headquarterTilePlayerRed;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> playingfield;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnBlue;
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnRed;

	Gamefield();

	void setAllFieldSizes();
	void setSizePlayerTilesBlue();
	void setSizePlayerTilesRed();
	void setSizeMenuBar();
	void setSizePlayingField();
	void setSizeSpawnBlue();
	void setSizeSpawnRed();

	void initiatePlayerTilesBlue();
	void initiatePlayerTilesRed();
	void initiateMenuTiles();
	void initiateSpawnTilesBlue();
	void initiateSpawnTilesRed();
	void initiatePlayingFieldTiles();

	std::shared_ptr<FieldTile> getSpawnFieldRed(int posY, int posX);
	std::shared_ptr<FieldTile> getSpawnFieldBlue(int posY, int posX);

	Sprite* getRandomButtonSprite(int rndNumber);
	Sprite* getRandomSpawnTileSprite(int rndNumber, bool colorRed);

public:
	~Gamefield();

	std::shared_ptr<Tile> getTilePointerAt(int x, int y);

	Gamefield(const Gamefield&) = delete;
	Gamefield& operator=(const Gamefield&) = delete;
	Gamefield(Gamefield&&) = delete;
	Gamefield& operator=(Gamefield&&) = delete;

	static auto& instance() {
		static Gamefield gamefield;
		return gamefield;
	}

	//noch noetig?
	void resetGameField();

	int spawnUnitInSpawn(std::shared_ptr<Unit> unit, bool redPlayerActive);

	bool fieldTileIsFree(int x, int y, std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> activeSpawn);

	void init(int FieldWidth, int FieldHeight, int Seed);

	std::shared_ptr<FieldTile> findeTileByUnit(std::shared_ptr<Unit> pUnit);

	void displayButtons(GAMEPHASES::GAMEPHASE phase);
	void deleteButtons(GAMEPHASES::GAMEPHASE phase);

	std::shared_ptr<MenuTile> getMenuTileFromXY(int posX, int posY);
	std::shared_ptr<FieldTile> getFieldTileFromXY(int posX, int posY);
	std::shared_ptr<FieldTile> getSpawnTileFromXY(bool colorRed, int posX, int posY);

	void setMenuBar(std::shared_ptr<vector<vector <std::shared_ptr<MenuTile>>>> menuBar) {
		this->menuBar = menuBar;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> getMenuBar() {
		return menuBar;
	}
	void setHqTilePlayerBlue(std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> hqTilePlayer) {
		this->headquarterTilePlayerBlue = hqTilePlayer;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> getHqTilePlayerBlue() {
		return this->headquarterTilePlayerBlue;
	}
	void setHqTilePlayerRed(std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> hqTilePlayer) {
		this->headquarterTilePlayerRed = hqTilePlayer;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<PlayerTile>>>> getHqTilePlayerRed() {
		return this->headquarterTilePlayerRed;
	}
	void setPlayingfield(std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> field) {
		this->playingfield = field;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> getPlayingfield() {
		return this->playingfield;
	}
	void setSpawnBlue(std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnBlue) {
		this->spawnBlue = spawnBlue;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> getSpawnBlue() {
		return this->spawnBlue;
	}
	void setSpawnRed(std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> spawnRed) {
		this->spawnRed = spawnRed;
	}
	std::shared_ptr<vector<vector<std::shared_ptr<FieldTile>>>> getSpawnRed() {
		return this->spawnRed;
	}



	// void assignEventToTile(MouseClickEvent event); -----noch noetig?

	void markTilesAround(int xPos, int yPos, int range);
	void selectTile(int xPos, int yPos);

	void deselectAndUnmarkAllTiles();
};
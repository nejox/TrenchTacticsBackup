#pragma once
#include "SpriteText.h"
#include "Sprite.hpp"
#include "Player.h"
#include "MenuTile.h"

/**
* Menubar wrapper class 
* controls all things concerning the menubar including buttons sprites setup and teardown
*/
class MenuBar
{
public:

	MenuBar(const MenuBar&) = delete;
	MenuBar& operator=(const MenuBar&) = delete;
	MenuBar(MenuBar&&) = delete;
	MenuBar& operator=(MenuBar&&) = delete;
	~MenuBar() {}

	static auto& instance() {
		static MenuBar menuBar;
		return menuBar;
	}


	/**
	* set up Menubarbackground
	* Initializes a MenuBar instance with fully configurated moneyToken unitCountTOken incomeToken phaseText
	* initializes money, income, unitCount, activePhaseToken activePhaseText, activePlayer and sets positions
	* initializes unit stats HP, AP, DMG
	*/
	void init()
	{

		menuBar = make_shared<vector<vector<std::shared_ptr<MenuTile>>>>();
		setSizeMenuBar();
		initiateMenuTiles();

		activePlayerFlag = make_shared<Sprite>();
		activePlayerFlag->setPos(19 * 64 + 4, 12 * 64 + 37);

		activePhaseToken = make_shared<Sprite>();
		activePhaseToken->setPos((64 * 19 + 3), (13 * 64 + 44));

		activePhaseText = make_shared<SpriteText>(22);
		activePhaseText->setPos((64 * 20 + 4), (13 * 64 + 52));

		phaseText = make_shared<SpriteText>(22);
		phaseText->setPos((64 * 20 + 4), (14 * 64 + 6));
		phaseText->load("PHASE");

		money = make_shared<SpriteText>(22);
		money->setPos((64 + 27), (12 * 64 + 9 + 32));

		income = make_shared<SpriteText>(22);
		income->setPos((64 + 27), (13 * 64 + 5));

		unitCount = make_shared<SpriteText>(22);
		unitCount->setPos((64 + 27), (13 * 64 + 48));

		unitHP = make_shared<SpriteText>(25);
		unitHP->setPos((64 * 9 + 40), (64 * 12 + 32));

		unitAP = make_shared<SpriteText>(25);
		unitAP->setPos((64 * 9 + 40), (64 * 13));

		unitDMG = make_shared<SpriteText>(25);
		unitDMG->setPos((64 * 9 + 40), (64 * 13 + 32));
		
		unitRange = make_shared<SpriteText>(25);
		unitRange->setPos((64 * 9 + 40), (64 * 14));
	}

	void updateMenuBar(GAMEPHASES::GAMEPHASE phase, shared_ptr<Player> activePlayer)
	{
		this->resetMenuBar();
		this->reInitButtons(phase); // hier muss nochmal dran gearbeitet werden
		this->updateTokens(activePlayer);
		this->updatePlayerStats(activePlayer);
	}

	void refreshMenuBar(shared_ptr<Player> activePlayer)
	{
		this->resetMenuBar();
		this->refreshAllButtonDisplays(); 
		this->updateTokens(activePlayer);
		this->updatePlayerStats(activePlayer);
	}

	void resetMenuBar();

	/**
	*renders the active players stats
	*Overloaded funtion
	*/
	void updatePlayerStats(shared_ptr<Player> activePlayer)
	{
		showPlayerStats(activePlayer);
	}
	void showPlayerStats(shared_ptr<Player> activePlayer);

	/**
	*renders the active players stats and the currently active Units HP
	*Overloaded funtion
	*/
	void updateUnitStats(shared_ptr<Unit> unit)
	{
		resetUnitStats();
		showUnitStats(unit);
	}

	void resetUnitStats();
	void showUnitStats(shared_ptr<Unit>unit);

	void setSizeMenuBar();
	void initiateMenuTiles();
	std::shared_ptr<MenuTile> getMenuTileFromXY(int posX, int posY);

	void displayTokens(shared_ptr<Player> activePlayer);

	void updateTokens(shared_ptr<Player> activePlayer)
	{
		this->displayTokens(activePlayer);
	}

	void initButtons(GAMEPHASES::GAMEPHASE phase);
	void deleteButtons();

	void deleteAllButtonDisplays();
	void resetAllButtonDisplays();

	void refreshAllButtonDisplays();

	void reInitButtons(GAMEPHASES::GAMEPHASE phase)
	{
		this->deleteButtons();
		this->initButtons(phase);
	}

	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> getMenuBar()
	{
		return this->menuBar;
	}


private:
	std::shared_ptr<vector<vector<std::shared_ptr<MenuTile>>>> menuBar;
	std::shared_ptr<Sprite> activePlayerFlag;
	std::shared_ptr<Sprite> activePhaseToken;
	std::shared_ptr<SpriteText> activePhaseText;
	std::shared_ptr<SpriteText> phaseText;
	std::shared_ptr<SpriteText> money;
	std::shared_ptr<SpriteText> income;
	std::shared_ptr<SpriteText> unitCount;
	std::shared_ptr<SpriteText> unitHP;
	std::shared_ptr<SpriteText> unitAP;
	std::shared_ptr<SpriteText> unitDMG;
	std::shared_ptr<SpriteText> unitRange;
	

	MenuBar() {};
};

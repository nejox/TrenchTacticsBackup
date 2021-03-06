#pragma once
#include "SpriteText.h"
#include "Sprite.h"
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
	void init();

	/**
	* Updaes the MenuBar with new Buttons
	* \param phase current phase
	* \param activePlayer currently activePlayer
	*/
	void updateMenuBar(GAMEPHASES::GAMEPHASE phase, std::shared_ptr<Player> activePlayer);

	/**
	* Refreshes the MenuBar with current Buttons
 * \param phase the gamephase the game currently resides in
 * \param activePlayer the currently active player - respectively the new active player
	*/
	void refreshMenuBar(std::shared_ptr<Player> activePlayer);
	
	/**
	* Renders background over the sidePanels of the menubar
	*/
	void resetMenuBarSidePanels();



	/**
	*renders the active players stats
	*/
	void updatePlayerStats(std::shared_ptr<Player> activePlayer);

	/** 
	*renders the currently active Units stats
	*Overloaded funtion
	*/
	void updateUnitStats(std::shared_ptr<Unit> unit)
	{
		resetUnitStats();
		showUnitStats(unit);
	}

	/** 
	* renders over the middle of the menubar, where unitstats are shown
	*/
	void resetUnitStats();

	/**
	* Displays units currentHp/MaxHp/
	* Displays units currentAp/MaxAp/
	* Displays units damage
	* Displays units range
	*/
	void showUnitStats(std::shared_ptr<Unit>unit);

	/**
	* Sets the size of the menubar at the gamestart.
	*
	*/
	void setSizeMenuBar();

	/**
	* Function to set up the MenuTiles at gamestart.
	*
	*/
	void initiateMenuTiles();

	/**
	* get a menu tile based on a pixel position x and y
	* returns nullptr when not valid
	*
	* \param posX
	* \param posY
	* \return
	*/
	std::shared_ptr<MenuTile> getMenuTileFromXY(int posX, int posY);

	/**
	*  Updates the tokens on the Menubar: CurrentPhase, ActivePlayerFlag 
	* 
	*/
	void updateTokens(std::shared_ptr<Player> activePlayer);

	/**
	* display necessary buttons based on phase.
	*
	* \param current gamephase
	*/
	void initButtons(GAMEPHASES::GAMEPHASE phase);

	/**
	* deletes all Buttons
	*/
	void deleteAllButtons();

	/**
	* renders background over all current buttons being displayed
	*/
	void deleteAllButtonDisplays();

	/**
	* Sets all buttons in menubar to be unpressed
	*/
	void resetAllButtonsToNeutral();

	/**
	* rerenders All Buttons
	*/
	void refreshAllButtonDisplays();

	/**
	* Sets up all buttons for the gamephase
	* \ param current gamephase
	*/
	void reInitButtons(GAMEPHASES::GAMEPHASE phase)
	{
		this->deleteAllButtons();
		this->initButtons(phase);
	}

	std::shared_ptr<std::vector<std::vector<std::shared_ptr<MenuTile>>>> getMenuBar()
	{
		return this->menuBar;
	}


private:
	const std::string slash = " / ";
	const std::string hp = "HP: ";
	const std::string ap = "AP: ";
	const std::string dmg = "DMG: ";
	const std::string rng = "RANGE: ";

	const int pixelToTileFactor = 64;

	std::shared_ptr<std::vector<std::vector<std::shared_ptr<MenuTile>>>> menuBar;
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

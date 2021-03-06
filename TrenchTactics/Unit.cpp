#include "Unit.h"
#include "Gamefield.h"
#include "UnitMovementFinishedEvent.h"



/**
 * Initializes Unit type with all values from config.
 *
 * \param unittype the type of unit that will be created
 * \param colorRed specifies which player is the owner of the new unit and selects the right sprites based on this bool
 */
Unit::Unit(TYPES::UNITTYPE unittype, bool colorRed)
{
	m_colorRed = colorRed;

	m_ID = ConfigReader::instance().getUnitConf(unittype)->getId();
	m_hp = ConfigReader::instance().getUnitConf(unittype)->getHP();
	m_currentHP = ConfigReader::instance().getUnitConf(unittype)->getHP();
	m_range = ConfigReader::instance().getUnitConf(unittype)->getRange();
	m_cost = ConfigReader::instance().getUnitConf(unittype)->getCost();
	m_ap = ConfigReader::instance().getUnitConf(unittype)->getAP();
	m_currentAP = ConfigReader::instance().getUnitConf(unittype)->getAP();
	m_dmg = ConfigReader::instance().getUnitConf(unittype)->getDmg();
	m_apCostAttack = ConfigReader::instance().getUnitConf(unittype)->getAPCostAttack();
	m_apCostMove = ConfigReader::instance().getUnitConf(unittype)->getAPCostMove();
	m_movementRange = ConfigReader::instance().getUnitConf(unittype)->getMovementRange();
	m_apCostTrench = ConfigReader::instance().getUnitConf(unittype)->getAPCostTrench();
	m_spawnProbability = ConfigReader::instance().getUnitConf(unittype)->getSpawnProbability();
	m_name = ConfigReader::instance().getUnitConf(unittype)->getName();
	m_sprite = std::make_shared<SpriteUnit>(colorRed, unittype);
	m_spriteHealthBar = std::make_shared<SpriteHealthBar>(colorRed);
	m_state = STATES::UNITSTATE::STANDING_NEUTRAL;
	m_level = 1;
	m_targetX = 0;
	m_targetY = 0;
	m_speed = 1.1f;
}

/**
 * Attack the provided target (unit)
 * updates health of target and ap of attacking unit
 *
 * \param target unit that will be attacked
 */
void Unit::attack(std::shared_ptr<Unit> target, bool cover)
{
	this->setState(STATES::SHOOTING);

	if (cover)
	{
		if (target->changeHP((m_dmg * 0.9f)))
		{
			this->levelUp();
		}
	}

	else {
		if (target->changeHP(m_dmg)) {
			this->levelUp();
		}
	}


	updateAP(m_apCostAttack);

}

/**
 * Attack the provided target(headquarter)
 * changes health of headquarter and ap of attacking unit
 *
 * \param target headquarter that will be attacked
 */
void Unit::attack(std::shared_ptr<Headquarter> target)
{
	this->setState(STATES::SHOOTING);
	target->changeHP(m_dmg);
	updateAP(m_apCostAttack);
}

/**
 * change the hp of the current unit
 * raises deathevent if unit is at or below zero health after health change
 * returns booleans if unit died
 * \param damage the amount of dmg dealt
 */
bool Unit::changeHP(int damage)
{

	m_currentHP -= damage;

	if (m_currentHP <= 0)
	{
		EventBus::instance().publish(new DeathEvent(shared_from_this()));
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Reset ap of the unit to its base value
 *
 */
void Unit::resetAP()
{
	m_currentAP = m_ap;
}

/**
 * update the unit & its sprite.
 *
 */
void Unit::update() {
	if (m_state == STATES::UNITSTATE::RUNNING) {
		move();
	}
	m_state = m_sprite->render(m_state);
	m_spriteHealthBar->render(this->getHp(), this->getCurrentHP(), this->getLevel());

}

/**
 * update the state of the unit, takes current hp into account
 *
 * \param state
 */
void Unit::update(STATES::UNITSTATE state)
{
	m_state = m_sprite->render(state);
	m_spriteHealthBar->render(this->getHp(), this->getCurrentHP(), this->getLevel());
}

void Unit::setState(STATES::UNITSTATE state)
{
	this->m_state = state;
}

STATES::UNITSTATE Unit::getState()
{
	return this->m_state;
}

/**
 * removes the provided amount of ap from a unit
 *
 * \param cost amount of ap to be removed
 */
void Unit::updateAP(int cost)
{
	m_currentAP -= cost;
}

void Unit::levelUp()
{
	this->m_level++;
	if (this->m_level > 3)
	{
		this->m_level = 3;
	}
	else {
		//adds 10% to each value for every level
		this->m_hp = m_hp * (1.0f + (((float)m_level - 1) / 10.0f));
		this->m_currentHP = m_currentHP * (1.0f + (((float)m_level - 1) / 10.0f));
		this->m_dmg = m_dmg * (1.0f + (((float)m_level - 1) / 10.0f));
	}
}

/**
 * moves the unit to target tile
 *
 */
void Unit::setTargetCoordinates(int x, int y)
{
	this->m_targetX = x;
	this->m_targetY = y;

	this->setState(STATES::UNITSTATE::RUNNING);
}

/**
 * moves the unit to target tile
 *
 */
void Unit::move()
{

	int currentX = this->getSprite()->getX();
	int currentY = this->getSprite()->getY();


	int distanceY = 0;
	int distanceX = 0;
	if (m_targetX < currentX) {
		distanceX = this->m_targetX / 64 - currentX / 64 - 1;
	}
	else {
		distanceX = this->m_targetX / 64 - currentX / 64;
	}
	if (m_targetY < currentY) {
		distanceY = (this->m_targetY) / 64 - currentY / 64 - 1;
	}
	else {
		distanceY = (this->m_targetY) / 64 - currentY / 64;
	}

	int newX = currentX;
	int newY = currentY;

	//walk x-axis
	if (distanceX > 0) {
		newX = currentX + m_speed + Timer::instance().GetElapsed();
	}
	else if (distanceX < 0) {
		newX = currentX + (m_speed + Timer::instance().GetElapsed()) * -1;
	}
	//walk y-axis
	else if (distanceY > 0) {
		newY = currentY + m_speed + Timer::instance().GetElapsed();
	}
	else if (distanceY < 0) {
		newY = currentY + (m_speed + Timer::instance().GetElapsed()) * -1;
	}
	else {
		//Ziel erreicht
		EventBus::instance().publish(new UnitMovementFinishedEvent(shared_from_this()));

		std::shared_ptr<FieldTile> tmp = Gamefield::instance().findTileByUnit(shared_from_this());
		if (tmp->hasCopse()) {
			tmp->removeCorpse();
		}
		else {
			tmp->refreshTile();
		}

		return;
	}
	//set the Sprite to new postion
	m_sprite->setPos(newX, newY);
	m_spriteHealthBar->setPos(newX, newY);

	//refresh tiles passed by
	if (m_targetY < currentY && distanceX == 0) {
		currentY += 64;
	}
	if (m_targetX < currentX) {
		currentX += 64;
	}

	if (currentX > (2 * 64 - 1) && currentX < (20 * 64)) {


		std::shared_ptr<FieldTile> tmp = Gamefield::instance().getFieldTileFromXY(currentX, currentY);

		if (tmp) {
			tmp->refreshTile();
		}

		//manage tile refreshing, the next tile needs refreshing too -> blurring
		//different calculation for blue & red units (+/- 64px)
		int tileX = currentX / 64;
		int nextTileX = 0;
		//if unit blue
		if (!this->getColorRed()) {
			nextTileX = currentX + 64;
		}
		// if red
		else {
			nextTileX = currentX - 64;
		}

		if (tileX != nextTileX / 64) {
			tmp = Gamefield::instance().getFieldTileFromXY(nextTileX, currentY);

			if (tmp) {
				tmp->refreshTile();
			}
		}
	}

	else {
		std::shared_ptr<FieldTile> tmp = Gamefield::instance().getSpawnTileFromXY(this->getColorRed(), currentX, currentY);
		if (tmp) {
			tmp->refreshTile();
		}

		int tileX = currentX / 64;
		int nextTileX = 0;
		//if unit blue
		if (!this->getColorRed()) {
			nextTileX = currentX + 64;
		}
		// if red
		else {
			nextTileX = currentX - 64;
		}

		if (tileX != nextTileX / 64) {
			if(nextTileX > (2 * 64 - 1) && nextTileX < (20 * 64)){
				tmp = Gamefield::instance().getFieldTileFromXY(nextTileX, currentY);
			}
			else {
				tmp = Gamefield::instance().getSpawnTileFromXY(this->getColorRed(), nextTileX, currentY);
			}

			if (tmp) {
				tmp->refreshTile();
			}
		}
	}
}


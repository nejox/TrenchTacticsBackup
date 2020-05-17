#include "Unit.h"
#include "DeathEvent.h"

/**
 * Attack the provided target (unit)
 * updates health of target and ap of attacking unit
 *
 * \param target unit that will be attacked
 */
void Unit::attack(std::shared_ptr<Unit> target)
{
	this->m_state = STATES::UNITSTATE::SHOOTING;
	target->changeHP(m_dmg);

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
	this->m_state = STATES::UNITSTATE::SHOOTING;
	target->changeHP(m_dmg);
	updateAP(m_apCostAttack);
}

/**
 * change the hp of the current unit
 * raises deathevent if unit is at or below zero health after health change
 *
 * \param damage the amount of dmg dealt
 */
void Unit::changeHP(int damage)
{
	m_currentHP -= damage;

	if (m_currentHP <= 0)
	{
		EventBus::instance().publish(new DeathEvent(this->getptr()));
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
 * update the unit in the sense of updating its sprite.
 *
 */
void Unit::update() {
	m_state = m_sprite->render(m_state);
	m_spriteHealthBar->render(this->getHp(), this->getCurrentHP());
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
 * update the state of the unit, takes current hp into account
 *
 * \param state
 */
void Unit::update(STATES::UNITSTATE state)
{
	m_state = m_sprite->render(state);
	m_spriteHealthBar->render(this->getHp(), this->getCurrentHP());
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

/**
 * ????
 *
 */
void Unit::move()
{
	//this->setState(RUNNING);
	//TO DO
	updateAP(m_apCostMove);
}


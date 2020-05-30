#pragma once
#include "Sprite.hpp"

/**
 * Sprite extension to add healthbars to a unit or hq.
 */
class SpriteHealthBar :
	public Sprite
{
public:

	
	/**Initializes HealthBar for HQ
	* Overloaded Constructor
	*/
	SpriteHealthBar();

	/**Initializes HealthBar for Unit 
	* Overloaded Constructor
	* \param ColorRed if Unit is part of team RED
	*/
	SpriteHealthBar(bool ColorRed);

	/**
	*Renders the HealthBar dependent on the current percentage of HP
	* \param maxHP maximum HP of specific object
	* \param currentHP the current HP of the specific object
	*/

	void render(int maxHP, int currentHP);

	/**
*Renders the HealthBar dependent on the current percentage of HP
* \param maxHP maximum HP of specific object
* \param currentHP the current HP of the specific object
* \param level current level of the unit
*/

	void render(int maxHP, int currentHP, int level);




private:
	int m_frameWidth;
	int m_frameHeight;



};
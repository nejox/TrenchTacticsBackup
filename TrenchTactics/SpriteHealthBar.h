#pragma once
#include "Sprite.hpp"

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
	void SpriteHealthBar::render(int maxHP, int currentHP);



private:
	int m_frameWidth;
	int m_frameHeight;

	/**Renders specific frame
	* made private, only to be called by render(int maxHP, int currentHP)
	*/
	void SpriteHealthBar::render(int frame);
};
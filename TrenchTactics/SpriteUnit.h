#pragma once
#ifndef SPRITE_UNIT
#define SPRITE_UNIT
#include <map>
#include "Sprite.hpp"
#include "UnitTypes.h"

namespace STATES
{
	enum UNITSTATE {
		STANDING_NEUTRAL,
		STANDING,
		SHOOTING,
		RUNNING
	};
	static const UNITSTATE All[] = { STANDING_NEUTRAL, STANDING, SHOOTING, RUNNING };

	enum BUTTONSTATE {
		NORMAL,
		PRESSED,
		DEACTIVATED
	};
}

class SpriteUnit :
	public Sprite
	//std::enable_shared_from_this<SpriteUnit>
{
public:

	SpriteUnit(bool colourRed, TYPES::UnitType type);
	void render();
	STATES::UNITSTATE render(STATES::UNITSTATE changedState);



private:
	//SpriteUnit() {};
	bool m_colourRed;
	STATES::UNITSTATE m_defaultState;
	STATES::UNITSTATE m_currentState;

	float m_fcurrentPhase;

	int m_numFrames;		// Anzahl der Animationsphasen
	int m_frameWidth;		// Breite einer Animationsphase
	int m_frameHeight;		// H�he einer Animationsphase

	std::map<STATES::UNITSTATE, string> animations;

	void load(const string sFilename, int frameWidth, int frameHeight);
	void render(int frame);

};


#endif
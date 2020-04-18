#pragma once
#include "Timer.hpp"

/// <summary>
/// IRenderer interface to achieve capsulation
/// </summary>
class IRenderer
{
public:

	virtual bool init(int ScreenWidth, int ScreenHeight,
		int ColorDepth, bool bFullscreen) = 0;
	virtual void clearScreen() = 0;
	virtual void destroy() = 0;
	virtual void updateTimer() = 0;
	virtual void renderTile() = 0; //TODO: Rect tileRect as parameter
	virtual void renderHQ() = 0;
	virtual void startAnimation() = 0; //TODO: Unit* unit as parameter

	virtual ~IRenderer() {}

private:
	CTimer* timer;

};
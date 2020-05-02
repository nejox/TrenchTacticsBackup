#include "FieldTile.h"

void FieldTile::removeUnit()
{
	this->unit = nullptr;
	if (this->getTerrain() == TERRAINTYPE::SPAWNTERRAIN) {
		this->getSprite()->render();
	}
	else {
		this->getSprite()->render();
	}

}

void FieldTile::setUnit(std::shared_ptr<Unit> unit)
{
	if (unit) {
		unit.get()->getSprite().get()->setPos(this->getPosX(), this->getPosY());
		this->unit = unit;
		this->unit->getSprite().get()->render();
	}

}


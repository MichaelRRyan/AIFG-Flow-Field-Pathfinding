#include "Cell.h"

void ff::Cell::setToImpassable()
{
	cost = IMPASSABLE_COST;
	integrationCost = IMPASSABLE_INTEGRATION_COST;
}

void ff::Cell::setToUndefined()
{
	cost = UNDEFINED_COST;
}

bool ff::Cell::isPassable() const
{
	return cost != IMPASSABLE_COST;
}

bool ff::Cell::isDefined() const
{
	return cost != UNDEFINED_COST;
}

#ifndef FLOW_FIELD_CELL_H
#define FLOW_FIELD_CELL_H

#include <limits>
#include "Vector2u.h"

namespace ff
{
	unsigned const UNDEFINED_COST{ std::numeric_limits<unsigned>::max() - 1u };
	unsigned const IMPASSABLE_COST{ std::numeric_limits<unsigned>::max() };
	float const IMPASSABLE_INTEGRATION_COST{ std::numeric_limits<float>::max() };

	class Cell
	{
	public:

		unsigned cost;
		float integrationCost;
		Vector2u bestNeighbour;

		void setToImpassable();
		void setToUndefined();

		bool isPassable() const;
		bool isDefined() const;
	};
}

#endif // !FLOW_FIELD_CELL_H

#ifndef FLOW_FIELD_H
#define FLOW_FIELD_H

#include <vector>
#include <queue>
#include <list>
#include <iostream>

#include "Cell.h"
#include "Vector2u.h"

namespace ff
{
	class FlowField
	{
	public:

		FlowField(size_t t_width, size_t t_height);

		// Setters.
		void setGoal(Vector2u const& t_cell, bool t_generate = true);
		void setWall(Vector2u const& t_cell, bool t_generate = true);
		void clearCell(Vector2u const& t_cell, bool t_generate = true);

		void setGoal(unsigned t_x, unsigned t_y, bool t_generate = true);
		void setWall(unsigned t_x, unsigned t_y, bool t_generate = true);
		void clearCell(unsigned t_x, unsigned t_y, bool t_generate = true);

		// Getters.
		Cell const & getCell(unsigned t_x, unsigned t_y) const;
		Cell const & getCell(Vector2u const& t_cell) const;
		std::vector<std::vector<Cell>> const & getCells() const;

		size_t getWidth() const;
		size_t getHeight() const;

		// Flow Field functionality.
		std::list<Vector2u> const* getPathToGoal(Vector2u const& t_startPos);
		void generate();

	private:

		void setNeighboursCosts(Vector2u t_cell, Vector2u t_goal, 
								std::queue<Vector2u> & t_costSetupQueue);

		void createFlowField();
		void setBestNeighbour(Vector2u const & t_cellPos);

		bool isWithinBounds(unsigned t_x, unsigned t_y);
		bool isWithinBounds(int t_x, int t_y);

		std::vector<std::vector<Cell>> m_cells;

		Vector2u m_goal;

	};
}

#endif // !FLOW_FIELD_H

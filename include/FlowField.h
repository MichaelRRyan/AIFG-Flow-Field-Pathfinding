#ifndef FLOW_FIELD_H
#define FLOW_FIELD_H

#include <vector>
#include <queue>
#include <iostream>

namespace ff
{
	unsigned const WALL_COST{ std::numeric_limits<unsigned>::max() };
	float const WALL_INTEGRATION_COST{ std::numeric_limits<float>::max() };

	struct Vector2u
	{
		unsigned x;
		unsigned y;
	};

	struct Cell
	{
		unsigned cost;
		float integrationCost;
		Vector2u bestNeighbour;
	};

	class FlowField
	{
	public:

		FlowField(size_t t_width, size_t t_height);

		void setGoal(unsigned t_x, unsigned t_y, bool t_generate = true);
		void setGoal(Vector2u const & t_cell, bool t_generate = true);

		void setWall(unsigned t_x, unsigned t_y, bool t_generate = true);
		void setWall(Vector2u const& t_cell, bool t_generate = true);

		void clearCell(unsigned t_x, unsigned t_y, bool t_generate = true);
		void clearCell(Vector2u const& t_cell, bool t_generate = true);

		void generate();

		Cell const & getCell(unsigned t_x, unsigned t_y) const;
		Cell const & getCell(Vector2u const& t_cell) const;

		std::vector<std::vector<Cell>> const & getCells() const;

		size_t getWidth() const;
		size_t getHeight() const;

	private:

		void setNeighboursCosts(Vector2u t_cell, Vector2u t_goal);
		void createFlowField();
		Vector2u getBestNeighbour(Vector2u t_cell);

		std::vector<std::vector<Cell>> m_cells;
		std::queue<Vector2u> m_costSetupQueue;

		Vector2u m_goal;

	};
}

#endif // !FLOW_FIELD_H

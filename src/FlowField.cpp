#include "FlowField.h"

using namespace ff;

FlowField::FlowField(size_t t_width, size_t t_height)
{
	// Sets the width and height of the cell grid.
	m_cells.resize(t_width);
	for (auto& row : m_cells) row.resize(t_height);
}

void FlowField::setGoal(unsigned t_x, unsigned t_y)
{
	// If the new goal position is within the bounds of the cost field.
	if (t_x < m_cells.size() && t_y < m_cells.at(0).size())
	{
		m_cells.at(t_x).at(t_y).cost = 0;
		m_goal = { t_x, t_y };
	}
}

void FlowField::setWall(unsigned t_x, unsigned t_y)
{
	// If the new wall position is within the bounds of the cost field.
	if (t_x < m_cells.size() && t_y < m_cells.at(0).size())
	{
		m_cells.at(t_x).at(t_y).cost = WALL_COST;
		m_cells.at(t_x).at(t_y).integrationCost = WALL_INTEGRATION_COST;
	}
}

void FlowField::generate()
{
	// Resets all non-wall cells to 0.
	for (auto & row : m_cells)
		for (auto & cell : row)
			if (cell.cost != WALL_COST) cell.cost = 0u;

	m_costSetupQueue.push(m_goal);

	while (!m_costSetupQueue.empty())
	{
		Vector2u cell = m_costSetupQueue.front();
		m_costSetupQueue.pop();

		setNeighboursCosts(cell, m_goal);
	}

	createFlowField();
}

std::vector<std::vector<Cell>> const& FlowField::getCells() const
{
	return m_cells;
}

size_t FlowField::getWidth() const
{
	return m_cells.size();
}

size_t FlowField::getHeight() const
{
	if (m_cells.empty()) return 0;

	return m_cells.at(0).size();
}

void FlowField::setNeighboursCosts(Vector2u t_cell, Vector2u t_goal)
{
	for (int direction = 0; direction < 9; ++direction)
	{
		if (direction == 4) continue; // Skip index 4 as refers to ourselves.

		// Works out the neighbours x and y using the neighbours algorithm.
		int x = t_cell.x + (direction / 3) - 1;
		int y = t_cell.y + (direction % 3) - 1;

		// Checks the x and y are within the flow field bounds.
		if (x >= 0 && y >= 0 && x < m_cells.size() && y < m_cells.at(x).size())
		{
			// Continues if this cell has already been checked or is the goal.
			if (m_cells.at(x).at(y).cost != 0 || (t_goal.x == x && t_goal.y == y)) continue;

			// Works out the cost of the cell.
			unsigned cost = m_cells.at(t_cell.x).at(t_cell.y).cost + 1;
			m_cells.at(x).at(y).cost = cost;

			// Work out integration cost.
			Vector2u distVec = { t_goal.x - x, t_goal.y - y };
			float distance = sqrt(pow(static_cast<float>(distVec.x), 2.0f) +
								  pow(static_cast<float>(distVec.y), 2.0f));

			m_cells.at(x).at(y).integrationCost = static_cast<float>(cost) * 100.0f + distance;

			// Adds the cell to the queue.
			m_costSetupQueue.push({ static_cast<unsigned>(x), 
									static_cast<unsigned>(y) });
		}
	}
}

void FlowField::createFlowField()
{
	for (unsigned x = 0; x < m_cells.size(); ++x)
	{
		for (unsigned y = 0; y < m_cells.at(x).size(); ++y)
		{
			Vector2u node = getBestNeighbour({ x, y });
			m_cells.at(x).at(y).bestNeighbour = { node.x, node.y };
		}
	}
}

Vector2u FlowField::getBestNeighbour(Vector2u t_tile)
{
	int bestDir = -1;
	float bestDirValue = 0.0f;

	for (int direction = 0; direction < 9; ++direction)
	{
		if (direction == 4) continue; // Skip 4 - 4 refers to ourselves.

		int x = t_tile.x + (direction / 3) - 1; // Neighbour col.
		int y = t_tile.y + (direction % 3) - 1; // Neighbour row.

		// Checks the bounds.
		if (x >= 0 && x < m_cells.size() &&
			y >= 0 && y < m_cells.at(x).size())
		{
			if (bestDir == -1 || m_cells.at(x).at(y).integrationCost < bestDirValue)
			{
				bestDir = direction;
				bestDirValue = m_cells.at(x).at(y).integrationCost;
			}
		}
	}

	return Vector2u{ t_tile.x + (bestDir / 3) - 1,
				     t_tile.y + (bestDir % 3) - 1 };
}

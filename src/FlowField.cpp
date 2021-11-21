#include "FlowField.h"

using namespace ff;

///////////////////////////////////////////////////////////////////////////////
FlowField::FlowField(size_t t_width, size_t t_height)
{
	// Sets the width and height of the cell grid.
	m_cells.resize(t_width);
	for (auto& row : m_cells) row.resize(t_height);
}

///////////////////////////////////////////////////////////////////////////////
void ff::FlowField::setGoal(Vector2u const& t_cell, bool t_generate)
{
	setGoal(t_cell.x, t_cell.y, t_generate);
}

///////////////////////////////////////////////////////////////////////////////
void ff::FlowField::setWall(Vector2u const& t_cell, bool t_generate)
{
	setWall(t_cell.x, t_cell.y, t_generate);
}

///////////////////////////////////////////////////////////////////////////////
void ff::FlowField::clearCell(Vector2u const& t_cell, bool t_generate)
{
	clearCell(t_cell.x, t_cell.y, t_generate);
}

///////////////////////////////////////////////////////////////////////////////
void FlowField::setGoal(unsigned t_x, unsigned t_y, bool t_generate)
{
	if (!isWithinBounds(t_x, t_y)) return;
	m_goal = { t_x, t_y };
	if (t_generate) generate();
}

///////////////////////////////////////////////////////////////////////////////
void FlowField::setWall(unsigned t_x, unsigned t_y, bool t_generate)
{
	if (!isWithinBounds(t_x, t_y)) return;
	m_cells.at(t_x).at(t_y).setToImpassable();
	m_cells.at(t_x).at(t_y).bestNeighbour = { t_x, t_y };
	if (t_generate) generate();
}

///////////////////////////////////////////////////////////////////////////////
void ff::FlowField::clearCell(unsigned t_x, unsigned t_y, bool t_generate)
{
	if (!isWithinBounds(t_x, t_y)) return;
	m_cells.at(t_x).at(t_y).setToUndefined();
	if (t_generate) generate();
}

///////////////////////////////////////////////////////////////////////////////
Cell const& ff::FlowField::getCell(unsigned t_x, unsigned t_y) const
{
	return m_cells.at(t_x).at(t_y);
}

///////////////////////////////////////////////////////////////////////////////
Cell const& ff::FlowField::getCell(Vector2u const& t_cell) const
{
	return m_cells.at(t_cell.x).at(t_cell.y);
}

///////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<Cell>> const& FlowField::getCells() const
{
	return m_cells;
}

///////////////////////////////////////////////////////////////////////////////
size_t FlowField::getWidth() const
{
	return m_cells.size();
}

///////////////////////////////////////////////////////////////////////////////
size_t FlowField::getHeight() const
{
	if (m_cells.empty()) return 0;

	return m_cells.at(0).size();
}

///////////////////////////////////////////////////////////////////////////////
std::list<Vector2u> const* ff::FlowField::getPathToGoal(Vector2u const& t_startPos)
{
	// Returns nullptr if the new wall position is outside the bounds of the cost field.
	if (!isWithinBounds(t_startPos.x, t_startPos.y)) return nullptr;

	// If the start is impassable or the goal, returns nullptr.
	if (!getCell(t_startPos).isPassable() && t_startPos == m_goal) return nullptr;

	// Creates a new empty path.
	std::list<Vector2u>* path = new std::list<Vector2u>();

	path->push_back(getCell(t_startPos).bestNeighbour);

	while (path->back() != m_goal)
		path->push_back(getCell(path->back()).bestNeighbour);

	return path;
}

///////////////////////////////////////////////////////////////////////////////
void FlowField::generate()
{
	// Resets all non-wall cells to the undefined cell cost.
	for (auto& row : m_cells)
		for (auto& cell : row)
			if (cell.isPassable()) cell.cost = UNDEFINED_COST;

	// Sets up the goal cell.
	Cell & goal = m_cells.at(m_goal.x).at(m_goal.y);
	goal.cost = 0;
	goal.integrationCost = 0.0f;
	goal.bestNeighbour = m_goal;

	// Creates a queue and adds the goal.
	std::queue<Vector2u> costSetupQueue;
	costSetupQueue.push(m_goal);

	// Loops while the queue isn't empty, setting the cost of each cell's neighbour.
	while (!costSetupQueue.empty())
	{
		Vector2u cell = costSetupQueue.front();
		costSetupQueue.pop();
		setNeighboursCosts(cell, m_goal, costSetupQueue);
	}

	// Creates the flow field with the newly generated integration cost.
	createFlowField();
}

///////////////////////////////////////////////////////////////////////////////
void FlowField::setNeighboursCosts(Vector2u t_cell, Vector2u t_goal,
								   std::queue<Vector2u> & t_costSetupQueue)
{
	for (int direction = 0; direction < 9; ++direction)
	{
		if (direction == 4) continue; // Skip index 4 as refers to ourselves.

		// Works out the neighbours x and y using the neighbours algorithm.
		int x = t_cell.x + (direction / 3) - 1;
		int y = t_cell.y + (direction % 3) - 1;

		if (isWithinBounds(x, y))
		{
			// Continues if this cell has already been defined or is the goal.
			if (m_cells.at(x).at(y).isDefined() || (t_goal.x == x && t_goal.y == y)) continue;

			// Works out the cost of the cell.
			unsigned cost = m_cells.at(t_cell.x).at(t_cell.y).cost + 1;
			m_cells.at(x).at(y).cost = cost;

			// Work out integration cost.
			float distX = static_cast<float>(t_goal.x) - x;
			float distY = static_cast<float>(t_goal.y) - y;
			float distance = sqrt(distX * distX + distY * distY);

			m_cells.at(x).at(y).integrationCost = static_cast<float>(cost) * 100.0f + distance;

			// Adds the cell to the queue.
			t_costSetupQueue.push({ static_cast<unsigned>(x), 
									static_cast<unsigned>(y) });
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
void FlowField::createFlowField()
{
	for (unsigned x = 0; x < m_cells.size(); ++x)
	{
		for (unsigned y = 0; y < m_cells.at(x).size(); ++y)
		{
			if (m_cells.at(x).at(y).isPassable()) setBestNeighbour({ x, y });
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
void FlowField::setBestNeighbour(Vector2u const & t_cellPos)
{
	Cell & cell = m_cells.at(t_cellPos.x).at(t_cellPos.y);
	float lowestCost = std::numeric_limits<float>::max();

	for (int direction = 0; direction < 9; ++direction)
	{
		if (direction == 4) continue; // Skip 4 - 4 refers to ourselves.

		int x = t_cellPos.x + (direction / 3) - 1; // Neighbour x.
		int y = t_cellPos.y + (direction % 3) - 1; // Neighbour y.

		// Checks the bounds.
		if (isWithinBounds(x, y))
		{
			if (m_cells.at(x).at(y).integrationCost < lowestCost)
			{
				lowestCost = m_cells.at(x).at(y).integrationCost;
				cell.bestNeighbour = { static_cast<unsigned>(x), 
									   static_cast<unsigned>(y) };
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
bool ff::FlowField::isWithinBounds(unsigned t_x, unsigned t_y)
{
	return t_x < m_cells.size() && t_y < m_cells.at(t_x).size();
}

///////////////////////////////////////////////////////////////////////////////
bool ff::FlowField::isWithinBounds(int t_x, int t_y)
{
	return t_x >= 0 && t_x < m_cells.size() &&
		   t_y >= 0 && t_y < m_cells.at(t_x).size();
}

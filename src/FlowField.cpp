#include "FlowField.h"

using namespace ff;

ff::FlowField::FlowField(int t_width, int t_height)
{
	// Sets the width and height of the weights container.
	m_costField.resize(t_width);
	for (auto & row : m_costField) row.resize(t_height);
}

void ff::FlowField::setGoal(int t_x, int t_y)
{
	// If the new goal position is within the bounds of the cost field.
	if (t_x > 0 && t_x < m_costField.size() &&
		t_y > 0 && t_y < m_costField.at(0).size())
	{
		m_costField.at(t_x).at(t_y) = 0;
		m_costSetupQueue.push({ t_x, t_y });

		while (!m_costSetupQueue.empty())
		{
			Node2D node = m_costSetupQueue.front();
			m_costSetupQueue.pop();

			setNeighboursCosts(node.x, node.y);
		}

		// Goal has been overwritten in the process, set it back to 0.
		m_costField.at(t_x).at(t_y) = 0;
	}
}

std::vector<std::vector<int8_t>> const& ff::FlowField::getCostField() const
{
	return m_costField;
}

void ff::FlowField::setNeighboursCosts(int t_x, int t_y)
{
	for (int direction = 0; direction < 9; ++direction)
	{
		if (direction == 4) continue; // Skip 4 - 4 refers to ourselves.

		int x = t_x + (direction / 3) - 1; // Neighbour col.
		int y = t_y + (direction % 3) - 1; // Neighbour row.

		// Checks the bounds.
		if (x >= 0 && x < m_costField.size() &&
			y >= 0 && y < m_costField.at(x).size())
		{
			if (m_costField.at(x).at(y) != 0) continue;

			m_costField.at(x).at(y) = m_costField.at(t_x).at(t_y) + 1;
			m_costSetupQueue.push({ x, y });
		}
	}
}

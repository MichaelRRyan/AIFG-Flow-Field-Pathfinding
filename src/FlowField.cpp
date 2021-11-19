#include "FlowField.h"

using namespace ff;

ff::FlowField::FlowField(size_t t_width, size_t t_height)
{
	// Sets the width and height of the cost field.
	m_costField.resize(t_width);
	for (auto & row : m_costField) row.resize(t_height);

	// Sets the width and height of the integration field.
	m_integrationField.resize(t_width);
	for (auto& row : m_integrationField) row.resize(t_height);

	// Sets the width and height of the flow field.
	m_flowField.resize(t_width);
	for (auto& row : m_flowField) row.resize(t_height);
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
			Node2i node = m_costSetupQueue.front();
			m_costSetupQueue.pop();

			setNeighboursCosts(node, { t_x, t_y });
		}

		// Goal has been overwritten in the process, set it back to 0.
		m_costField.at(t_x).at(t_y) = 0;
		m_integrationField.at(t_x).at(t_y) = 0.0f;

		createFlowField();
	}
}

std::vector<std::vector<int8_t>> const& ff::FlowField::getCostField() const
{
	return m_costField;
}

std::vector<std::vector<float>> const& ff::FlowField::getIntegrationField() const
{
	return m_integrationField;
}

std::vector<std::vector<Node2i>> const& ff::FlowField::getFlowField() const
{
	return m_flowField;
}

size_t ff::FlowField::getWidth() const
{
	return m_costField.size();
}

size_t ff::FlowField::getHeight() const
{
	if (m_costField.empty()) return 0;

	return m_costField.at(0).size();
}

void ff::FlowField::setNeighboursCosts(Node2i t_tile, Node2i t_goal)
{
	for (int direction = 0; direction < 9; ++direction)
	{
		if (direction == 4) continue; // Skip 4 - 4 refers to ourselves.

		int x = t_tile.x + (direction / 3) - 1; // Neighbour col.
		int y = t_tile.y + (direction % 3) - 1; // Neighbour row.

		// Checks the bounds.
		if (x >= 0 && x < m_costField.size() &&
			y >= 0 && y < m_costField.at(x).size())
		{
			if (m_costField.at(x).at(y) != 0) continue;

			int8_t cost = m_costField.at(t_tile.x).at(t_tile.y) + 1;
			m_costField.at(x).at(y) = cost;

			Node2i distVec = { t_goal.x - x, t_goal.y - y };
			float distance = sqrt(pow(static_cast<float>(distVec.x), 2.0f) +
								  pow(static_cast<float>(distVec.y), 2.0f));

			m_integrationField.at(x).at(y) = static_cast<float>(cost * 100) + distance;
			m_costSetupQueue.push({ x, y });
		}
	}
}

void ff::FlowField::createFlowField()
{
	for (int x = 0; x < m_integrationField.size(); ++x)
	{
		for (int y = 0; y < m_integrationField.at(x).size(); ++y)
		{
			Node2i node = getBestNeighbour({ x, y });
			m_flowField.at(x).at(y) = { node.x - x, node.y - y };
		}
	}
}

Node2i ff::FlowField::getBestNeighbour(Node2i t_tile)
{
	int bestDir = -1;
	float bestDirValue = 0.0f;

	for (int direction = 0; direction < 9; ++direction)
	{
		if (direction == 4) continue; // Skip 4 - 4 refers to ourselves.

		int x = t_tile.x + (direction / 3) - 1; // Neighbour col.
		int y = t_tile.y + (direction % 3) - 1; // Neighbour row.

		// Checks the bounds.
		if (x >= 0 && x < m_integrationField.size() &&
			y >= 0 && y < m_integrationField.at(x).size())
		{
			if (bestDir == -1 || m_integrationField.at(x).at(y) < bestDirValue)
			{
				bestDir = direction;
				bestDirValue = m_integrationField.at(x).at(y);
			}
		}
	}

	return Node2i{ t_tile.x + (bestDir / 3) - 1,
				   t_tile.y + (bestDir % 3) - 1 };
}

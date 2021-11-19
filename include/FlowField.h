#ifndef FLOW_FIELD_H
#define FLOW_FIELD_H

#include <vector>
#include <queue>
#include <iostream>

namespace ff
{
	struct Node2i
	{
		int x;
		int y;
	};

	class FlowField
	{
	public:

		FlowField(size_t t_width, size_t t_height);

		void setGoal(int t_x, int t_y);

		std::vector<std::vector<int8_t>> const& getCostField() const;
		std::vector<std::vector<float>> const & getIntegrationField() const;
		std::vector<std::vector<Node2i>> const & getFlowField() const;

		size_t getWidth() const;
		size_t getHeight() const;

	private:

		void setNeighboursCosts(Node2i t_tile, Node2i t_goal);
		void createFlowField();
		Node2i getBestNeighbour(Node2i t_tile);

		std::vector<std::vector<int8_t>> m_costField;
		std::vector<std::vector<float>> m_integrationField;
		std::vector<std::vector<Node2i>> m_flowField;

		std::queue<Node2i> m_costSetupQueue;

	};
}

#endif // !FLOW_FIELD_H

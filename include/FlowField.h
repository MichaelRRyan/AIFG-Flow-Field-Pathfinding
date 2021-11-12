#ifndef FLOW_FIELD_H
#define FLOW_FIELD_H

#include <vector>
#include <queue>
#include <iostream>

namespace ff
{
	class FlowField
	{
	public:

		FlowField(int t_width, int t_height);

		void setGoal(int t_x, int t_y);

		std::vector<std::vector<int8_t>> const & getCostField() const;

	private:

		struct Node2D
		{
			int x;
			int y;
		};

		void setNeighboursCosts(int t_x, int t_y);

		std::vector<std::vector<int8_t>> m_costField;

		std::queue<Node2D> m_costSetupQueue;

	};
}

#endif // !FLOW_FIELD_H

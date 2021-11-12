#ifndef FLOW_FIELD_H
#define FLOW_FIELD_H

#include <vector>

namespace ff
{
	class Node2f
	{
	public:

		float x;
		float y;

		Node2f() = default;

		Node2f(float t_x, float t_y) :
			x{ t_x }, y{ t_y } { }
	};

	class FlowField
	{
	public:

		FlowField(int t_width, int t_height);

		std::vector<std::vector<int8_t>> const & getCostField() const;

	private:

		std::vector<std::vector<int8_t>> m_costField;

	};
}

#endif // !FLOW_FIELD_H

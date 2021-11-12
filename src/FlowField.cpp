#include "FlowField.h"

using namespace ff;

ff::FlowField::FlowField(int t_width, int t_height)
{
	// Sets the width and height of the weights container.
	m_costField.resize(t_width);
	for (auto & row : m_costField) row.resize(t_height);
}

std::vector<std::vector<int8_t>> const& ff::FlowField::getCostField() const
{
	return m_costField;
}

#ifndef FLOW_FIELD_VECTOR2U_H
#define FLOW_FIELD_VECTOR2U_H

namespace ff 
{
	class Vector2u
	{
	public:
		unsigned x;
		unsigned y;

		bool operator==(Vector2u const& t_right) const;
		bool operator!=(Vector2u const& t_right) const;

	};
}

#endif // !FLOW_FIELD_VECTOR2U_H

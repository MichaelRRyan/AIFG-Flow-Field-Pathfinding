#include "Vector2u.h"

bool ff::Vector2u::operator==(Vector2u const& t_right) const
{
    return x == t_right.x && y == t_right.y;
}

bool ff::Vector2u::operator!=(Vector2u const& t_right) const
{
    return x != t_right.x || y != t_right.y;
}

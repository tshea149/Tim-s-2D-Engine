/* author: Tim */
#include "Handle.h"

HandleType Handle::getType() const
{
	return type;
}

bool Handle::operator==(const Handle h)
{
	if (this->index == h.index)
	{
		if (this->counter == h.counter)
		{
			if (this->type == h.type)
				return true;
		}
	}
	return false;
}

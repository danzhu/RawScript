#pragma once

#include "Primitive.h"

namespace RawScript
{
	typedef Primitive<bool> Bool;

	namespace Primitives
	{
		void InitializeBoolType(Library *lib);
		Object *BoolToString(Runtime * rt, Object *obj, Args& args);
	}
}
#pragma once

#include "Function.h"

namespace RawScript
{
	struct OperatorDefinition
	{
		Function *defaultOperation;
		std::string method;

		static Object *Equals(Runtime *rt, Object *obj, Args &args);
	};
}
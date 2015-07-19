#include "Operator.h"

#include "Utilities.h"
#include "Bool.h"
#include "Runtime.h"
#include "Library.h"

using namespace RawScript;

Object * RawScript::OperatorDefinition::Equals(Runtime * rt, Object * obj, Args & args)
{
	return new Bool(rt->library->GetType("bool"), obj == args[0]);
}

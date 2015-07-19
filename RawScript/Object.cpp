#include "Object.h"

#include "Type.h"
#include "Utilities.h"
#include "String.h"
#include "Function.h"
#include "Exceptions.h"

using namespace RawScript;

RawScript::Object::Object(Type * t) : type(t)
{
}

Object * RawScript::Object::InvokeMethod(Runtime * rt, std::string id, Args & args)
{
	Function *method = type->GetMethod(id);
	if (!method)
		throw RuntimeException("Method '" + id + "' does not exist on type '" + type->name + "'");
	return method->Invoke(rt, this, args);
}

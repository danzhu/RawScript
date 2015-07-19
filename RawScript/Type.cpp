#include "Type.h"

#include "String.h"
#include "Runtime.h"
#include "Function.h"
#include "Library.h"

using namespace RawScript;

RawScript::Type::Type()
{
}

RawScript::Type::Type(std::string name) : Scope(name)
{
}

void RawScript::Type::SetMethod(std::string id, Function * fn)
{
	if (fn->name.empty())
		fn->name = id;
	methods[id] = fn;
}

Function * RawScript::Type::GetMethod(std::string id)
{
	if (methods.find(id) != methods.end())
		return methods[id];
	else
		return nullptr;
}

void RawScript::Type::InitializeType(Library * lib)
{
	lib->type->type = lib->type;
	lib->type->methods["ToString"] = new Function(lib->function, Type::ToString);
}

Object * RawScript::Type::ToString(Runtime * rt, Object * obj, Args & args)
{
	Type *t = (Type *)obj;
	return new String(rt->library->function, "type " + t->name);
}

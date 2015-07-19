#include "Bool.h"

#include "Library.h"
#include "Type.h"
#include "Runtime.h"
#include "String.h"

using namespace RawScript;

void RawScript::Primitives::InitializeBoolType(Library * lib)
{
	Type *t = new Type();
	t->SetMethod("ToString", new Function(lib->function, BoolToString));
	lib->AddType("bool", t);
}

Object * RawScript::Primitives::BoolToString(Runtime * rt, Object * obj, Args & args)
{
	Bool *b = (Bool *)obj;
	return new String(rt->library->GetType("string"), b->value ? "true" : "false");
}

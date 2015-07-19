#include "Function.h"

#include "Type.h"
#include "Library.h"
#include "Runtime.h"
#include "String.h"

using namespace RawScript;

RawScript::Function::Function(Type * t, CFunction fn, std::string name)
	: Object(t), function(fn), name(name)
{
}

Object * RawScript::Function::Invoke(Runtime * rt, Object * obj, Args & args)
{
	return function(rt, obj, args);
}

void RawScript::Function::InitializeType(Library * lib)
{
	Type *& fn = lib->function;
	fn->type = lib->type;
	fn->SetMethod("ToString", new Function(fn, ToString));
	fn->SetObject("()", new Function(fn, Call));
}

Object * RawScript::Function::Call(Runtime * rt, Object * obj, Args & args)
{
	Function *fn = (Function *)obj;
	return fn->function(rt, nullptr, args);
}

Object * RawScript::Function::ToString(Runtime * rt, Object * obj, Args & args)
{
	Function *fn = (Function *)obj;
	return new String(rt->library->GetType("string"), "function " + fn->name);
}

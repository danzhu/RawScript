#include "Runtime.h"

#include "Exceptions.h"
#include "Int.h"
#include "Scope.h"
#include "Script.h"
#include "Operation.h"
#include "Type.h"
#include "Function.h"
#include "String.h"

using namespace RawScript;

RawScript::Runtime::Runtime(Library * lib) : library(lib)
{
	globals = new Scope();
}

Object *RawScript::Runtime::GetObject(std::string id)
{
	return globals->GetObject(id);
}

Object *RawScript::Runtime::Execute(Script script)
{
	return script.content->Execute(this);
}

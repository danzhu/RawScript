#include "Scope.h"

#include "Exceptions.h"

using namespace RawScript;

RawScript::Scope::Scope() : Object(nullptr), members()
{
	// TODO: Add type for scope
}

RawScript::Scope::Scope(std::string name) : Object(nullptr), name(name)
{
}

Object *& RawScript::Scope::GetObject(std::string id)
{
	// Search in the current scope
	if (members.find(id) != members.end())
		return members[id];
	// Do the same thing in parent scope
	if (parent)
		return parent->GetObject(id);
	// If no parent (current scope is at top level), no object is found, throw
	throw RuntimeException("Identifier '" + id + "' not found in the current scope");
}

void RawScript::Scope::SetObject(std::string id, Object *val)
{
	members[id] = val;
}

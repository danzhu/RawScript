#pragma once

#include <map>
#include <vector>

namespace RawScript
{
	class Object;
	class Scope;
	class Script;
	class Type;
	class Library;

	class Runtime
	{
	public:
		Library *library;
		Scope *globals;

		Runtime(Library *lib);
		Object *GetObject(std::string id);
		Object *Execute(Script script);
	};
}
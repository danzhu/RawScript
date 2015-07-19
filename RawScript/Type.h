#pragma once

#include <string>
#include <map>
#include "Object.h"
#include "Scope.h"

namespace RawScript
{
	class Function;
	class Library;

	class Type : public Scope
	{
		std::map<std::string, Function *> methods;
	public:
		Function *constructor;

		Type();
		Type(std::string name);
		void SetMethod(std::string id, Function *fn);
		Function *GetMethod(std::string id);

		static void InitializeType(Library *lib);
		static Object *ToString(Runtime *rt, Object *obj, Args &args);
	};
}
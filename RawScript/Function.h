#pragma once

#include <string>
#include "Object.h"

namespace RawScript
{
	class Object;
	class Runtime;
	class Operation;
	class Library;

	typedef Object *(*CFunction)(Runtime *rt, Object *obj, Args &args);

	class Function : public Object
	{
	protected:
		CFunction function;
	public:
		std::string name;

		Function(Type *t, CFunction fn, std::string name = "");
		Object *Invoke(Runtime *rt, Object *obj, Args &args);

		static void InitializeType(Library *lib);
		static Object *Call(Runtime *rt, Object *obj, Args &args);
		static Object *ToString(Runtime *rt, Object *obj, Args &args);
	};
}
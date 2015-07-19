#pragma once

#include <string>

namespace RawScript
{
	class String;
	class Type;
	class Runtime;
	template<typename T>
	class Array;
	class Object;

	typedef Array<Object *> Args;

	class Object
	{
	public:
		Type *type;

		Object(Type *t);
		Object *InvokeMethod(Runtime *rt, std::string id, Args &args);
	};
}
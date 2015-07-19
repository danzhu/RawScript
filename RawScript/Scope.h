#pragma once

#include <map>
#include "Object.h"

namespace RawScript
{
	class Scope : public Object
	{
	protected:
		std::map<std::string, Object *> members;
	public:
		Scope *parent;
		std::string name;

		Scope();
		Scope(std::string name);
		Object *&GetObject(std::string id);
		void SetObject(std::string id, Object *val);
	};
}
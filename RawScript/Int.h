#pragma once

#include "Primitive.h"

namespace RawScript
{
	typedef Primitive<int> Int;

	namespace Primitives
	{
		void InitializeIntType(Library *lib);
		Object *IntConstructor(Runtime * rt, Object * obj, Args & args);
		Object *IntToString(Runtime * rt, Object *obj, Args& args);
	}

	class IntParser : public LiteralParser
	{
		Type *type;

		bool IsDigit(char c);
	public:
		IntParser(Type *t);
		virtual bool Tokenize(std::string s, unsigned int &pos);
		virtual Object *Parse(Token token, Library *lib);
	};
}
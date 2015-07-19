#pragma once

#include <string>
#include "Object.h"
#include "ConstantParser.h"

namespace RawScript
{
	struct Token;

	class String : public Object
	{
	public:
		std::string value;

		String(Type *t, std::string s);

		static void InitializeType(Library *lib);
		static Object *ToString(Runtime *rt, Object *obj, Args &args);
	};

	class StringParser : public LiteralParser
	{
		Type *type;
	public:
		StringParser(Type *type);
		virtual bool Tokenize(std::string s, unsigned int &pos);
		virtual Object *Parse(Token token, Library *lib);
	};
}
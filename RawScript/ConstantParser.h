#pragma once

#include <string>

namespace RawScript
{
	struct Token;
	class Object;
	class Library;

	class LiteralParser
	{
	public:
		// Return # of chars the constant requires. 0 if failed
		virtual bool Tokenize(std::string s, unsigned int &pos) = 0;
		// Parse a token (in string form) to an object
		virtual Object *Parse(Token token, Library *lib) = 0;
	};
}
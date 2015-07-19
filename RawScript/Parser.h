#pragma once

#include <string>
#include "Tokenizer.h"

namespace RawScript
{
	class Operation;
	class Script;
	class Library;
	template<typename T>
	class Array;
	class Code;

	class Parser
	{
		Tokenizer tokenizer;
		Library *library;

		Operation *Value();
		void Arguments(Array<Operation *> &args);
		Operation *Term();
		Operation *Binary(unsigned int level);
		Operation *Expression();
		Operation *Statement();
		Code *ParseCode();
	public:
		Parser(Library *lib);
		Script Parse(std::string source);
	};
}
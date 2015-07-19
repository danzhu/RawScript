#pragma once

#include <map>
#include <vector>
#include "Function.h"
#include "Operator.h"

namespace RawScript
{
	struct Token;
	class LiteralParser;

	class Library
	{
	protected:
		std::vector<std::map<std::string, OperatorDefinition>> operators;
		std::map<std::string, Type *> types;
		std::vector<LiteralParser *> literals;
	public:
		Type *type;
		Type *function;
		OperatorDefinition call;

		Library();
		// Operator
		void AddOperator(std::string op, unsigned int pre = 0, OperatorDefinition def = {});
		OperatorDefinition GetOperator(std::string op);
		std::string MatchOperator(std::string s, unsigned int &pos);
		bool IsOperatorLevel(unsigned int l, std::string op);
		unsigned int MaxPrecedence();
		// Type
		void AddType(std::string id, Type *t);
		Type *GetType(std::string id);
		// Literal Parser
		void AddLiteralParser(LiteralParser *parser);
		Object *ParseLiteral(Token t);
		int TokenizeLiteral(std::string s, unsigned int &pos);
	};

	class StandardLibrary : public Library
	{
	public:
		StandardLibrary();
	};
}
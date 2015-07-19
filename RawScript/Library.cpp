#include "Library.h"

#include "String.h"
#include "Int.h"
#include "Bool.h"
#include "Tokenizer.h"
#include "Type.h"

using namespace RawScript;

RawScript::Library::Library()
{
	type = new Type("type");
	function = new Type("function");
	Type::InitializeType(this);
	Function::InitializeType(this);

	call.method = "()";
}

void RawScript::Library::AddOperator(std::string op, unsigned int pre, OperatorDefinition def)
{
	while (operators.size() <= pre)
		operators.push_back(std::map<std::string, OperatorDefinition>());
	operators[pre][op] = def;
}

OperatorDefinition RawScript::Library::GetOperator(std::string op)
{
	for (auto i = operators.begin(); i != operators.end(); i++)
	{
		if (i->find(op) != i->end())
			return (*i)[op];
	}
	return OperatorDefinition{};
}

std::string RawScript::Library::MatchOperator(std::string s, unsigned int & pos)
{
	std::string lastMatch{};
	unsigned int start = pos++;
	// Extend the operator string one char each time
	for (; pos <= s.length(); pos++)
	{
		unsigned int len = pos - start;
		// Extact string for better performance
		std::string op = s.substr(start, len);
		// Count matches
		unsigned int count = 0;
		for (auto i = operators.begin(); i != operators.end(); i++)
		{
			for (auto j = i->begin(); j != i->end(); j++)
			{
				// Find partial match
				if (j->first.substr(0, len) == op)
				{
					// Find exact match
					if (j->first.length() == len)
						lastMatch = op;
					count++;
				}
			}
		}
		// Search until no match is found
		if (count > 0)
			continue;
		else
			break;
	}
	// If no match, restore position
	if (lastMatch.empty())
		pos = start;
	// Else, move position back (due to last pos++)
	else
		pos--;
	// Only / no match found, return last match
	return lastMatch;
}

bool RawScript::Library::IsOperatorLevel(unsigned int l, std::string op)
{
	auto level = operators[l];
	return level.find(op) != level.end();
}

unsigned int RawScript::Library::MaxPrecedence()
{
	return operators.size() - 1;
}

void RawScript::Library::AddType(std::string id, Type * t)
{
	if (t->name.empty())
		t->name = id;
	t->type = type;
	types[id] = t;
}

Type * RawScript::Library::GetType(std::string id)
{
	if (types.find(id) == types.end())
		return nullptr;
	return types[id];
}

void RawScript::Library::AddLiteralParser(LiteralParser * parser)
{
	literals.push_back(parser);
}

Object * RawScript::Library::ParseLiteral(Token t)
{
	return literals[t.constId]->Parse(t, this);
}

int RawScript::Library::TokenizeLiteral(std::string s, unsigned int & pos)
{
	for (unsigned int i = 0; i < literals.size(); i++)
		if (literals[i]->Tokenize(s, pos))
		{
			return i;
		}
	return -1;
}

RawScript::StandardLibrary::StandardLibrary()
{
	String::InitializeType(this);
	Primitives::InitializeIntType(this);
	Primitives::InitializeBoolType(this);

	AddOperator("(");
	AddOperator(")");
	AddOperator(".");
	AddOperator(",");
	AddOperator("*", 1, { nullptr, "*" });
	AddOperator("/", 1, { nullptr, "/" });
	AddOperator("+", 2, { nullptr, "+" });
	AddOperator("-", 2, { nullptr, "-" });
	AddOperator("==", 3, { new Function(function, OperatorDefinition::Equals), "==" });
}

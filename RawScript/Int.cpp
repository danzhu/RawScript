#include "Int.h"

#include "Runtime.h"
#include "Type.h"
#include "Utilities.h"
#include "String.h"
#include "Function.h"
#include "Runtime.h"
#include "Scope.h"
#include "Exceptions.h"
#include "Library.h"

using namespace RawScript;

void RawScript::Primitives::InitializeIntType(Library * lib)
{
	Type *t = new Type();
	t->SetObject("+", new Function(lib->function, Add<Int>));
	t->SetObject("-", new Function(lib->function, Subtract<Int>));
	t->SetObject("*", new Function(lib->function, Multiply<Int>));
	t->SetObject("/", new Function(lib->function, Divide<Int>));
	t->SetMethod("ToString", new Function(lib->function, IntToString));
	lib->AddType("int", t);
	lib->AddLiteralParser(new IntParser(t));
}

Object * RawScript::Primitives::IntConstructor(Runtime * rt, Object * obj, Args & args)
{
	std::string val = ((String *)args[0])->value;
	int value = 0;

	// Parse int
	auto i = val.begin();
	bool negative;
	if (negative = *i == '-')
		i++;
	for (; i != val.end(); i++)
	{
		if (!isdigit(*i))
			throw RuntimeException("Unrecognized constant format");
		value *= 10;
		value += *i - '0';
	}
	if (negative)
		value *= -1;

	return new Int((Type *)obj, value);
}

Object *RawScript::Primitives::IntToString(Runtime * rt, Object *obj, Args& args)
{
	int i = ((Int *)obj)->value;

	bool negative;
	if (negative = i < 0)
		i *= -1;

	std::string s{};
	while (i > 0)
	{
		s = (char)(i % 10 + '0') + s;
		i /= 10;
	}
	// Treat 0 and negative
	if (s.length() == 0)
		s = "0";
	else if (negative)
		s = '-' + s;

	// TODO: Simplify
	return new String{ rt->library->GetType("string"), s };
}

bool RawScript::IntParser::IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

RawScript::IntParser::IntParser(Type * t) : type(t)
{
}

bool RawScript::IntParser::Tokenize(std::string s, unsigned int & pos)
{
	if (!IsDigit(s[pos]))
		return false;
	pos++;
	while (IsDigit(s[pos]))
		pos++;
	return true;
}

Object * RawScript::IntParser::Parse(Token token, Library * lib)
{
	int value = 0;
	auto i = token.value.begin();
	bool negative;
	if (negative = *i == '-')
		i++;
	for (; i != token.value.end(); i++)
	{
		if (!isdigit(*i))
			throw CompilationException("Unrecognized constant format", token);
		value *= 10;
		value += *i - '0';
	}
	if (negative)
		value *= -1;
	return new Int(type, value);
}

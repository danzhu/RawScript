#include "String.h"

#include "Type.h"
#include "Library.h"
#include "Tokenizer.h"

using namespace RawScript;

RawScript::String::String(Type *t, std::string s) : Object(t), value(s)
{
}

void RawScript::String::InitializeType(Library * lib)
{
	Type *t = new Type();
	t->type = lib->type;
	t->SetMethod("ToString", new Function(lib->function, ToString));
	lib->AddLiteralParser(new StringParser(t));
	lib->AddType("string", t);
}

Object * RawScript::String::ToString(Runtime * rt, Object * obj, Args & args)
{
	String *s = (String *)obj;
	return new String(s->type, "\"" + s->value + "\"");
}

RawScript::StringParser::StringParser(Type * type) : type(type)
{
}

bool RawScript::StringParser::Tokenize(std::string s, unsigned int & pos)
{
	if (s[pos] != '"')
		return false;
	do
	{
		pos++;
	} while (s[pos] != '"');
	// Go past '"'
	pos++;
	return true;
}

Object * RawScript::StringParser::Parse(Token token, Library * lib)
{
	return new String(type, token.value.substr(1, token.value.length() - 2));
}

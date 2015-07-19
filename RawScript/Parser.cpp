#include "Parser.h"

#include "Exceptions.h"
#include "Operation.h"
#include "Script.h"
#include "Library.h"

using namespace RawScript;

Operation *RawScript::Parser::Value()
{
	Token t = tokenizer.Current();
	Operation *op;
	switch (t.type)
	{
	case TokenType::Constant:
		op = new ConstantOperation(library->ParseLiteral(t));
		break;
	case TokenType::Identifier:
		op = new GetOperation(t.value);
		break;
	case TokenType::Operator:
		if (t.value != "(")
			throw CompilationException("Invalid operator use", t);
		tokenizer.Next();
		op = Expression();
		t = tokenizer.Current();
		if (t.value != ")")
			throw CompilationException("')' expected", t);
		break;
	default:
		throw CompilationException("Value expected", t);
	}
	tokenizer.Next();
	return op;
}

void RawScript::Parser::Arguments(Array<Operation *> & args)
{
	// If contains arguments, parse them
	if (tokenizer.Next().value != ")")
	{
		// TODO: Add more flexibility to # of arguments
		args.items = new Operation *[32];
		while (true)
		{
			args.Insert(Expression());
			if (tokenizer.Current().value != ",")
				break;
			tokenizer.Next();
		}
		Token t = tokenizer.Current();
		if (t.value != ")")
			throw CompilationException("')' expected", t);
	}
	// Remove ')'
	tokenizer.Next();
}

Operation * RawScript::Parser::Term()
{
	Operation *op = Value();
	while (true)
	{
		std::string s = tokenizer.Current().value;
		if (s == ".")
		{
			// Get method / member identifier
			std::string id = tokenizer.Next().value;

			if (tokenizer.Next().value == "(")
			{
				// Method invocation
				MethodOperation *mo = new MethodOperation(op, id);
				Arguments(mo->arguments);
				op = mo;
			}
			else
			{
				// Member access
				op = new MemberOperation(op, id);
			}
		}
		else if (s == "(")
		{
			// Function invocation
			OperatorOperation *oo = new OperatorOperation(library->call, op);
			Arguments(oo->operands);
			op = oo;
		}
		else
			break;
	}
	return op;
}

Operation *RawScript::Parser::Binary(unsigned int level)
{
	Operation *op = level > 1 ? Binary(level - 1) : Term();
	while (true)
	{
		Token t = tokenizer.Current();
		if (!library->IsOperatorLevel(level, t.value))
			break;

		tokenizer.Next();
		Operation *op2 = (level > 1 ? Binary(level - 1) : Term());
		Operation **ops = new Operation *[2]{ op, op2 };
		op = new OperatorOperation(library->GetOperator(t.value), 2, ops);
	}
	return op;
}

Operation *RawScript::Parser::Expression()
{
	return Binary(library->MaxPrecedence());
}

Operation * RawScript::Parser::Statement()
{
	return Expression();
}

Code * RawScript::Parser::ParseCode()
{
	Code *op = new Code();
	// TODO: Add more space
	op->statements.items = new Operation *[128];
	while (tokenizer.Current().type != TokenType::EndOfFile)
	{
		op->statements.Insert(Statement());
	}
	return op;
}

RawScript::Parser::Parser(Library * lib) : library(lib), tokenizer(lib)
{
}

Script RawScript::Parser::Parse(std::string source)
{
	tokenizer.Clear();
	tokenizer.Feed(source);
	Script s{};
	s.content = ParseCode();
	return s;
}

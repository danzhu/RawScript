#include "Exceptions.h"

#include <sstream>

RawScript::CompilationException::CompilationException(std::string message, Token t)
	: exception(message.data()), token(t)
{
}

std::string RawScript::CompilationException::Description() const
{
	std::stringstream ss{};
	ss << "Error at line " << token.line << ", column " << token.column << ": " << what();
	return ss.str();
}

RawScript::RuntimeException::RuntimeException(std::string message)
	: exception(message.data())
{
}

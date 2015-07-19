#pragma once

#include <exception>
#include <string>
#include "Tokenizer.h"

namespace RawScript
{
	class CompilationException : public std::exception
	{
	public:
		Token token;

		CompilationException(std::string message, Token t);
		std::string Description() const;
	};

	class RuntimeException : public std::exception
	{
	public:
		RuntimeException(std::string message);
	};
}
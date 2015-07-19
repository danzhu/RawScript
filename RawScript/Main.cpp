#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"
#include "Runtime.h"
#include "Script.h"
#include "Utilities.h"
#include "String.h"
#include "Exceptions.h"
#include "Library.h"
#include "Scope.h"
#include "Int.h"

using namespace RawScript;

StandardLibrary lib{};
Parser parser{ &lib };
Runtime runtime{ &lib };

Object *Print(Runtime *rt, Object *obj, Args &args)
{
	if (args.length > 0)
	{
		String *s = (String *)args[0];
		std::cout << s->value;
	}
	std::cout << std::endl;
	return nullptr;
}

Object *Exit(Runtime *rt, Object *obj, Args &args)
{
	int code = 0;
	if (args.length > 0)
		code = ((Int *)args[0])->value;
	exit(code);
}

void Interactive()
{
	std::cout << "RawScript 0.0" << std::endl
		<< "Copyright 2015 Daniel Zhu" << std::endl
		<< "> ";
	std::string exp;
	while (std::getline(std::cin, exp))
	{
		try
		{
			Script s = parser.Parse(exp);
			Object *result = runtime.Execute(s);
			if (result)
			{
				String *res = (String *)result->InvokeMethod(&runtime, "ToString", Args());
				std::string str = res->value;
				std::cout << str << std::endl;
			}
		}
		catch (const CompilationException& e)
		{
			for (unsigned int i = 0; i < e.token.column + 1; i++)
				std::cerr << " ";
			for (unsigned int i = 0; i < e.token.value.length(); i++)
				std::cerr << "~";
			std::cerr << std::endl
				<< e.Description() << std::endl
				<< std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		std::cout << "> ";
	}
}

void Execute(const char *name)
{
	std::ifstream input{ name };
	try
	{
		std::stringstream ss{};
		ss << input.rdbuf();
		runtime.Execute(parser.Parse(ss.str()));
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

int main(int argc, const char *argv[])
{
	// Initialize
	runtime.globals->SetObject("print", new Function(lib.function, Print, "print"));
	runtime.globals->SetObject("exit", new Function(lib.function, Exit, "exit"));

	if (argc > 1)
		Execute(argv[1]);
	else
		Interactive();
}
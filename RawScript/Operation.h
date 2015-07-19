#pragma once

#include <string>
#include "Utilities.h"
#include "Operator.h"

namespace RawScript
{
	class Object;
	class Runtime;

	class Operation
	{
	public:
		virtual Object *Execute(Runtime *rt) = 0;
	};

	class MethodOperation : public Operation
	{
	public:
		std::string method;
		Operation *object;
		Array<Operation *> arguments;

		MethodOperation(Operation *obj, std::string id);
		virtual Object *Execute(Runtime *rt);
	};

	class MemberOperation : public Operation
	{
	public:
		Operation *object;
		std::string member;

		MemberOperation(Operation *obj, std::string id);
		virtual Object *Execute(Runtime *rt);
	};

	class OperatorOperation : public Operation
	{
	public:
		OperatorDefinition definition;
		Operation *object;
		Array<Operation *> operands;

		OperatorOperation(OperatorDefinition def, Operation *obj);
		OperatorOperation(OperatorDefinition def, unsigned int opNum, Operation **ops);
		virtual Object *Execute(Runtime *rt);
	};

	class ConstantOperation : public Operation
	{
	public:
		Object *value;

		ConstantOperation(Object *val);
		virtual Object *Execute(Runtime *rt);
	};

	class GetOperation : public Operation
	{
	public:
		std::string identifier;

		GetOperation(std::string id);
		virtual Object *Execute(Runtime *rt);
	};

	class Code
	{
	public:
		Array<Operation *> statements;

		Code();
		Object *Execute(Runtime *rt);
	};
}
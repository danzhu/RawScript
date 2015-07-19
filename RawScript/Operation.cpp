#include "Operation.h"

#include "Type.h"
#include "Runtime.h"
#include "Exceptions.h"

using namespace RawScript;

RawScript::MethodOperation::MethodOperation(Operation *obj, std::string id)
	: method(id), object(obj), arguments()
{
}

Object *RawScript::MethodOperation::Execute(Runtime *rt)
{
	Object *obj = object->Execute(rt);

	Args ops(arguments.length);
	for (unsigned int i = 0; i < arguments.length; i++)
		ops[i] = arguments[i]->Execute(rt);

	return obj->InvokeMethod(rt, method, ops);
}

RawScript::MemberOperation::MemberOperation(Operation * obj, std::string id)
	: object(obj), member(id)
{
}

Object * RawScript::MemberOperation::Execute(Runtime * rt)
{
	// TODO: Implement member access
	throw RuntimeException("Member access not implemented");
}

RawScript::OperatorOperation::OperatorOperation(OperatorDefinition def, Operation *obj)
	: definition(def), object(obj), operands()
{
}

RawScript::OperatorOperation::OperatorOperation(
	OperatorDefinition def, unsigned int opNum, Operation ** ops)
	: definition(def), object(), operands(opNum, ops)
{
}

Object * RawScript::OperatorOperation::Execute(Runtime * rt)
{
	Object *obj{};
	if (object)
		obj = object->Execute(rt);

	Args ops(operands.length);
	for (unsigned int i = 0; i < operands.length; i++)
		ops[i] = operands[i]->Execute(rt);

	Function *fn = (Function *)(object ? obj : ops[0])->type->GetObject(definition.method);
	if (!fn)
		fn = definition.defaultOperation;
	if (!fn)
		throw RuntimeException("Operator not defined");
	return fn->Invoke(rt, object ? obj : nullptr, ops);
}

RawScript::ConstantOperation::ConstantOperation(Object * val) : value(val)
{
}

Object *RawScript::ConstantOperation::Execute(Runtime *rt)
{
	return value;
}

RawScript::GetOperation::GetOperation(std::string id) : identifier(id)
{
}

Object * RawScript::GetOperation::Execute(Runtime * rt)
{
	return rt->GetObject(identifier);
}

RawScript::Code::Code()
{
}

Object * RawScript::Code::Execute(Runtime * rt)
{
	Object *result{};
	for (unsigned int i = 0; i < statements.length; i++)
	{
		result = statements[i]->Execute(rt);
	}
	return result;
}

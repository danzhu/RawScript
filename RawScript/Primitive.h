#pragma once

#include "Object.h"
#include "ConstantParser.h"

namespace RawScript
{
	template<typename T>
	class Primitive : public Object
	{
	public:
		T value;

		Primitive(Type *t, T val) : Object(t), value(val) {}
	};

	namespace Primitives
	{
		template<typename T>
		Object *Add(Runtime *rt, Object *obj, Args &args)
		{
			T *a0 = (T *)args[0];
			T *a1 = (T *)args[1];
			return new T(a0->type, a0->value + a1->value);
		}
		template<typename T>
		Object *Subtract(Runtime *rt, Object *obj, Args &args)
		{
			T *a0 = (T *)args[0];
			T *a1 = (T *)args[1];
			return new T(a0->type, a0->value - a1->value);
		}
		template<typename T>
		Object *Multiply(Runtime *rt, Object *obj, Args &args)
		{
			T *a0 = (T *)args[0];
			T *a1 = (T *)args[1];
			return new T(a0->type, a0->value * a1->value);
		}
		template<typename T>
		Object *Divide(Runtime *rt, Object *obj, Args &args)
		{
			T *a0 = (T *)args[0];
			T *a1 = (T *)args[1];
			return new T(a0->type, a0->value / a1->value);
		}
	}
}
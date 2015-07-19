#pragma once

namespace RawScript
{
	template<typename T>
	class Array
	{
	public:
		T *items;
		unsigned int length;

		Array() : length(0), items(nullptr) {}
		Array(unsigned int len) : Array(len, new T[len]) {}
		Array(unsigned int len, T *items) : length(len), items(items) {}

		~Array()
		{
			if (items != nullptr)
				delete[] items;
		}

		T &operator[](unsigned int index)
		{
			return items[index];
		}

		void Insert(T val)
		{
			items[length++] = val;
		}
	};
}
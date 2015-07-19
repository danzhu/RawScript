#pragma once

#include <string>
#include <vector>

namespace RawScript
{
	class Library;

	enum TokenType
	{
		Identifier,
		Operator,
		Constant,
		Error,
		EndOfLine,
		EndOfFile
	};

	struct Token
	{
		TokenType type;
		std::string value;
		unsigned int line;
		unsigned int column;
		int constId;
	};

	class Tokenizer
	{
		std::vector<Token> tokens;
		unsigned int position;
		Library *library;
	public:
		Tokenizer(Library *lib);
		void Feed(std::string source);

		inline Token Current() const
		{
			return tokens[position];
		}

		inline Token Next(int offset = 1)
		{
			if (!InRange(position + offset))
				return Token{ TokenType::Error };

			position += offset;

			return Current();
		}

		inline Token Peek(int offset = 1) const
		{
			if (!InRange(position + offset))
				return Token{ TokenType::Error };

			return tokens[position + offset];
		}

		inline bool InRange(unsigned int pos) const
		{
			return pos >= 0 && pos < tokens.size();
		}

		inline void Clear()
		{
			position = 0;
			tokens.clear();
		}

		static inline bool IsDigit(char c)
		{
			return c >= '0' && c <= '9';
		}

		static inline bool IsIdentifier(char c)
		{
			return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
		}
	};
}
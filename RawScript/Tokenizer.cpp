#include "Tokenizer.h"

#include "Library.h"
#include "Exceptions.h"

using namespace RawScript;

RawScript::Tokenizer::Tokenizer(Library * lib) : library(lib), tokens()
{
}

void RawScript::Tokenizer::Feed(std::string s)
{
	unsigned int line{ 0 }, startIndex{ 0 };
	unsigned int i = 0;
	while (i < s.length())
	{
		if (s[i] == ' ')
		{
			i++;
			continue;
		}

		if (s[i] == '\n')
		{
			line++;
			startIndex = i;
			i++;
			continue;
		}

		Token t{ TokenType::Error, "", line + 1, i - startIndex + 1 };
		if (IsIdentifier(s[i]))
		{
			t.type = TokenType::Identifier;
			do
			{
				t.value += s[i];
				i++;
			} while (IsIdentifier(s[i]));
		}
		else
		{
			std::string op = library->MatchOperator(s, i);
			if (!op.empty())
			{
				// Operator
				t.type = TokenType::Operator;
				t.value = op;
			}
			else
			{
				// Constant
				unsigned int oldI = i;
				t.constId = library->TokenizeLiteral(s, i);
				if (t.constId < 0)
					throw CompilationException("Unrecognized object literal", t);
				t.type = TokenType::Constant;
				t.value = s.substr(oldI, i - oldI);
			}
		}

		tokens.push_back(t);
	}
	tokens.push_back(Token{ TokenType::EndOfFile, "", line + 1, s.length() - startIndex + 1 });
}

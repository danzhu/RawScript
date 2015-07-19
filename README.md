RawScript 0.0 (Development Version)
===================================

This little language and its interpreter (named RawScript since it's so basic)
is basically a test of what I learned about language parsing and compilation.
It's far from done, and certainly has a lot more flaws than any other finished
product. But since I made it, I'm going to implement any feature I expect in a
language that I own.

Features
--------
The interpreter currently only supports basical one-line expressions. However,
the engine is designed in a way that components are added easily, such as:
- Operators
- Types
- Object literals

Future Designs
--------------
- Common Language Features
  - Statements (if, while, etc)
  - User functions
  - User classes (types)
  - Scopes (namespaces)
- Language Specific Features
  - Type cast (with overloads)
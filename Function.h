#include <math.h>
#include <iostream>
#include <string>
using namespace std;

enum OpCode { ADD, SUB, MUL, DIV, SIN, COS, TAN, ASIN, ACOS, ATAN, EXP };


class Function {
	public:
		Function();
		string to_string();
		int dimension;
		Function differentiate(Variable);
};

class Constant : public function {
	public:
		float val;
		Constant(float);
};

class Variable : public function {
	public:
		string name;
		Variable(string);
};

class BinOp : public Function {
	public:
		Function f1;
		Function f2
		OpCode op;
		BinOp(OpCode, Function, Function);
};


class UnOp : public Function {
	public:
		Function f;
		OpCode op;
		UnOp(OpCode, Function);
};


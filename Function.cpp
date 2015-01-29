Function::Function() {
	dimension = 1; //Default setting
}

Function Function::differentiate(Variable x);

string Function::to_string() { return string("void function"); }
string Constant::to_string() { return to_string(val); }
string Variable::to_string() { return name; }
string BinOp::to_string() {
	switch(op) {
		case(ADD) {return f1.to_string() + " + " + f2.to_string();}
		case(SUB) {return f1.to_string() + " - " + f2.to_string();}
		case(MUL) {return f1.to_string() + " * " + f2.to_string();}
		case(DIV) {return f1.to_string() + " / " + f2.to_string();}
		default: {return string("invalid binary operator"); }
	}
}


Function Constant::differentiate(Variable x) {
	return Constant(0);
}


Function Variable::differentiate(Variable x) {
	if (x.name == name)
		return Constant(1);
	return Constant(0);
}

Function BinOp::differentiate(Variable x) {
	if (op == ADD)
		return BinOp(ADD, f1.differentiate(x), f2.differentiate(x));
	if (op == SUB)
		return BinOp(SUB, f1.differentiate(x), f2.differentiate(x));
	if (op == MUL)
		return BinOp(ADD, 
				BinOp(MUL, f1.differentiate(x), f2),
				BinOp(MUL, f1, f2.differentiate(x)));
	if (op == DIV)
		return BinOp(DIV, 
				BinOp(SUB,
					BinOp(MUL, f2, f1.differentiate(x))
					BinOp(MUL, f1, f2.differentiate(x)))
				BinOp(EXP, f2, Constant(2)))
	if (op == EXP)

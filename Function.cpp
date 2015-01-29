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
	switch(op) {
		case(ADD):
			return BinOp(ADD, f1.differentiate(x), f2.differentiate(x));
		case(SUB):
			return BinOp(SUB, f1.differentiate(x), f2.differentiate(x));
		case(MUL):
			return BinOp(ADD, 
				BinOp(MUL, f1.differentiate(x), f2),
				BinOp(MUL, f1, f2.differentiate(x)));
		case(DIV):
			return BinOp(DIV, 
				BinOp(SUB,
					BinOp(MUL, f2, f1.differentiate(x))
					BinOp(MUL, f1, f2.differentiate(x)))
				BinOp(EXP, f2, Constant(2)));
		case(EXP):
			if (f2.constant(x))
				return BinOp(MUL, f2, BinOp(MUL, f1.differentiate(x),
					BinOp(EXP, f1, Constant(((Constant)f2).val - 1.0))));

			else
				return BinOp(MUL,
					BinOp(EXP, f1, Binop(SUB, f2, Constant(1)))
					BinOp(SUM,
						BinOp(MUL, f2, f1.differentiate(x))
						BinOp(MUL, f1,
							BinOp(MUL, f2.differentiate(x),
								UpOp(LN, f1)))));
		case(LOG):
			if (f1.constant(x))
				return BinOp(DIV, f2.differentiate(x), 
					BinOp(MUL, Constant(log(((Constant)f1).val)), f2));
			else
				return BinOp(DIV,
					BinOP(SUB,
						BinOp(DIV,
							BinOp(MUL, f2.differentiate(x),
								UnOp(LN, f1)), f2),
						BinOp(DIV,
							BinOp(MUL, f1.differentiate(x),
								UnOp(LN, f2)), f1)),
					BinOp(EXP,
						BinOp(LOG, Constant(exp(1)), f1),
						Constant(2)));
		default:
			return Constant(0);
		}
}

Function UnOp::differentiate



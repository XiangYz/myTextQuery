#ifndef EXPR_PARSER_H
#define EXPR_PARSER_H

#include <stack>
#include <string>
#include "Query.h"

class ExprParser
{
public:
	ExprParser(std::string expression);

	Query Parse();

private:
	std::string _post_expr;
	std::string _expr;
	std::string::iterator _iter;

	bool GetToken(std::string& expr, std::string& token);
	void ToPostExpr();
	Query GenQuery();
};



#endif

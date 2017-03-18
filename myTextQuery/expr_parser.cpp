#include "expr_parser.h"

ExprParser::ExprParser(std::string expression)
	:_expr(expression), _iter(expression.begin())
{
}

Query ExprParser::Parse()
{
	ToPostExpr();

	return GenQuery();
}

 bool ExprParser::GetToken(std::string& expr, std::string& token)
{
	std::string word;
	bool res = false;
	while (_iter != expr.end())
	{
		char ch = *_iter++;

		if (ch == '&' || ch == '|' || ch == '~' || ch == '(' || ch == ')')
		{
			if (word.empty())
			{
				char s[5] = { 0 };
				s[0] = ch;
				token = std::string(s);
				return true;
			}
			else
			{
				--_iter;
				token = word;
				return true;
			}
		}
		else if (ch == ' ')
		{
			if (!word.empty())
			{
				token = word;
				return true;
			}
		}
		else
		{
			word.insert(word.end(), ch);
		}
	} // while it != end

	if (!word.empty())
	{
		token = word;
		return true;
	}

	return false;
}

void ExprParser::ToPostExpr()
{
	std::string post_expression;
	std::stack<std::string> trans_stack;
	_iter = _expr.begin();

	while (true)
	{
		std::string word;
		if (!GetToken(_expr, word)) break;

		if (word == "&")
		{
			trans_stack.push(word);

		}
		else if (word == "|")
		{
			trans_stack.push(word);
		}
		else if (word == "~")
		{
			bool has_next = GetToken(_expr, word);
			if (!has_next) throw std::invalid_argument("wrong expression");

			if (word == "(")
			{
				trans_stack.push("~");
				trans_stack.push("(");
			}
			else // ~后面的不是左括号就一定是单词
			{
				post_expression.append(word);
				post_expression.append(" ~ ");
			}

		}
		else if (word == "(")
		{
			trans_stack.push(word);
		}
		else if (word == ")")
		{
			while (!trans_stack.empty())
			{
				std::string top = trans_stack.top();
				trans_stack.pop();
				if (top == "(")
				{
					if (!trans_stack.empty())
					{
						top = trans_stack.top();
						if (top == "~")
						{
							trans_stack.pop();
							post_expression.append("~ ");
						}
					}

					break;
				}

				post_expression.append(top);
				post_expression.append(" ");
			}
		}
		else // 其余情况均作为单词的一部分
		{
			post_expression.append(word);
			post_expression.append(" ");
		}

	} // while true

	  // 栈内还剩余的符号添加到外面
	while (!trans_stack.empty())
	{
		std::string top = trans_stack.top();
		trans_stack.pop();
		post_expression.append(top);
		post_expression.append(" ");

	}

	_post_expr = post_expression;
}

Query ExprParser::GenQuery()
{
	std::string word;
	std::stack<Query> calc_stack;

	_iter = _post_expr.begin();
	while (GetToken(_post_expr, word))
	{
		if (word == "&")
		{
			if (calc_stack.empty()) throw std::invalid_argument("wrong expression");
			Query op1 = calc_stack.top();
			calc_stack.pop();

			if (calc_stack.empty()) throw std::invalid_argument("wrong expression");
			Query op2 = calc_stack.top();
			calc_stack.pop();

			Query res = op1 & op2;
			calc_stack.push(res);

		}
		else if (word == "|")
		{
			if (calc_stack.empty()) throw std::invalid_argument("wrong expression");
			Query op1 = calc_stack.top();
			calc_stack.pop();

			if (calc_stack.empty()) throw std::invalid_argument("wrong expression");
			Query op2 = calc_stack.top();
			calc_stack.pop();

			Query res = op1 | op2;
			calc_stack.push(res);
		}
		else if (word == "~")
		{
			if (calc_stack.empty()) throw std::invalid_argument("wrong expression");
			Query op1 = calc_stack.top();
			calc_stack.pop();

			Query res = ~op1;
			calc_stack.push(res);
		}
		else
		{
			Query q(word);
			calc_stack.push(q);
		}
	} // while post_expression

	if (calc_stack.size() != 1) throw std::invalid_argument("wrong expression");

	Query res = calc_stack.top();
	calc_stack.pop();

	return res;
}

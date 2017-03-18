#ifndef QUERY_RES_H
#define QUERY_RES_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <set>

class QueryResult
{
public:
	typedef std::shared_ptr< std::vector<std::string> > _FILELINES_PTR;
	typedef std::shared_ptr< std::set<size_t> > _WORD_LINENO_PTR;

	QueryResult(std::string expression
		, _FILELINES_PTR file_lines
		, _WORD_LINENO_PTR res_lineno)
		:_expression(expression), _file_lines(file_lines), _res_lineno(res_lineno)
	{

	}

	operator bool()
	{
		if (_res_lineno) return true;

		return false;
	}

	void print()
	{
		std::cout << _expression << " : ";

		if (!_res_lineno)
		{
			std::cout << "not found" << std::endl;
			return;
		}
		std::cout << std::endl;

		for (auto& n : *_res_lineno)
		{
			std::cout << '\t' << n + 1
				<< '\t' << (*_file_lines)[n] << std::endl;
		}
		std::cout << std::endl;
	}

	std::string _expression;
	_FILELINES_PTR _file_lines;
	_WORD_LINENO_PTR _res_lineno;
};



#endif
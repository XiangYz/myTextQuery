#include <iostream>
#include <string>
#include <fstream>
#include "CmdLine.h"
#include "Err.h"
#include "catch.hpp"
#include "Text.h"
#include "WordQuery.h"
#include "QueryResult.h"
#include "QueryBase.h"
#include "BinaryQuery.h"
#include "expr_parser.h"

void ErrExit(std::string err)
{
	std::cerr << err << std::endl;
	exit(-1);
}


void Usage()
{
	std::cout << "myTextQuery -f FileName \"your expression\"" << std::endl;
	exit(-1);
}



int main(int argc, char* argv[])
{

#ifdef _DEBUG
	argc = 2;
	argv[0] = "";
	argv[1] = "-f TextQueryTest.txt";
	//argv[2] = "\"her\"";
#endif

	CmdLine cmd_line_obj;
	Err err = cmd_line_obj.HandleCmdLine(argc, argv);
	if (err)
	{
		Usage();
	}
	if (cmd_line_obj._file_name.empty())
	{
		ErrExit("err: No target file");
	}

#ifdef _DEBUG
	std::cout << cmd_line_obj._file_name << std::endl
		<< cmd_line_obj._query_expression << std::endl << std::endl;
#endif

	std::ifstream ifs(cmd_line_obj._file_name);
	if (!ifs) ErrExit("cannot open target file");
	
	Text file(ifs);

	ifs.close();

#ifdef _DEBUG

	Text::_FILELINES_PTR file_lines_ptr = file.GetFileLines();
	if (file_lines_ptr)
	{
		int i = 1;
		for (auto line : *file_lines_ptr)
		{
			std::cout << i++ << "\t" << line << std::endl;
		}
	}

	
	std::cout << std::endl;

#endif

	if (!cmd_line_obj._query_expression.empty())
	{

		try
		{
			ExprParser expr_parser(cmd_line_obj._query_expression);
			Query q = expr_parser.Parse();
			QueryResult qr = q.query(file);

			qr.print();
		}
		catch (std::invalid_argument& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else
	{
		std::string input_line;
		while (true)
		{
			std::cout << "Input your expression for query: " << std::endl;
			std::getline(std::cin, input_line);
			if (input_line == "q") break;

			try
			{
				ExprParser expr_parser(input_line);
				Query q = expr_parser.Parse();
				QueryResult qr = q.query(file);

				qr.print();
			}
			catch (std::invalid_argument& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}



	return 0;
}
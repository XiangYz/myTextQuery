#ifndef CMD_LINE
#define CMD_LINE

#include <string>
#include "Err.h"

class CmdLine
{
public:
	std::string _file_name;
	std::string _query_expression;

	Err HandleCmdLine(int argc, char* argv[]);
};


#endif
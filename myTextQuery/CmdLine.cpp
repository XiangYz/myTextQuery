#include "CmdLine.h"
#include <stack>

Err CmdLine::HandleCmdLine(int argc, char * argv[])
{
	Err err;
	std::string cmd_line;
	for (int i = 1; i < argc; ++i)
	{
		cmd_line.append(argv[i]);
		cmd_line.append(" ");
	}

	std::string::iterator it = cmd_line.begin();
	while (it != cmd_line.end())
	{
		char ch = *it;
		if (ch == '-')
		{
			if (++it != cmd_line.end())
			{
				if (*it++ == 'f')
				{
					while (it != cmd_line.end() && *it == ' ') ++it;

					while (it != cmd_line.end() && *it != ' ')
					{
						_file_name.insert(_file_name.end(), *it);
						++it;
					}
				}
				else
				{
					err._err = -1;
					err._disp = "unsupported option: " + *(it - 1);
				}
			}
			else
			{
				err._err = -1;
				err._disp = "illegal cmd line";
			}
		} // if ch == '-'
		else if (ch == '"')
		{
			++it;
			while (it != cmd_line.end() && *it != '"')
			{
				if (*it == '\\')
				{
					++it;
					if (it != cmd_line.end() && *it == '"')
						_query_expression.insert(_query_expression.end(), '"');
					else if (*it != '"')
					{
						_query_expression.insert(_query_expression.end(), '\\');
						_query_expression.insert(_query_expression.end(), *it);
						
					}
					else 
						break;

					++it;
				}
				else
					_query_expression.insert(_query_expression.end(), *it++);
			} // while in query_expression

			if (it != cmd_line.end()) ++it;
		}
		else if (ch == ' ')
		{
			++it;
			continue;
		}
		else
		{
			err._err = -1;
			err._disp = "illegal cmd line";
		}

	} // while it != end()

	return err;
}

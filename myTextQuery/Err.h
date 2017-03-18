#ifndef TEXT_QUERY_ERR
#define TEXT_QUERY_ERR

#include <string>

struct Err
{
	int _err;
	std::string _disp;

	Err()
		:_err(0), _disp("")
	{
	}

	operator bool()
	{
		if (!_err) return false;

		return true;
	}
};


#endif

#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include "Text.h"
#include "QueryResult.h"

class QueryBase
{
public:
	virtual QueryResult query(Text& fileobj) = 0;
	virtual std::string disp() = 0;
};





#endif

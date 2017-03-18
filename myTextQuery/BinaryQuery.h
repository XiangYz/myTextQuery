#ifndef BINARY_QUERY_H
#define BINARY_QUERY_H

#include "QueryBase.h"
#include "Query.h"

class BinaryQuery : public QueryBase
{
public:
	BinaryQuery(Query& lhs, Query& rhs)
		:_lhs(lhs), _rhs(rhs){}
	virtual QueryResult query(Text& fileobj) = 0;
	virtual std::string disp() = 0;

protected:
	Query _lhs;
	Query _rhs;
};


#endif

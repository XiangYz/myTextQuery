#ifndef AND_QUERY_H
#define AND_QUERY_H


#include "BinaryQuery.h"
#include "QueryResult.h"
#include "Text.h"
#include "Query.h"

class AndQuery : public BinaryQuery
{
public:
	AndQuery(Query& lhs, Query& rhs);
	virtual QueryResult query(Text& fileobj);
	virtual std::string disp();
};



#endif

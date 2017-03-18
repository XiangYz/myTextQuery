#ifndef OR_QUERY_H
#define OR_QUERY_H


#include "BinaryQuery.h"
#include "QueryResult.h"
#include "Text.h"
#include "Query.h"

class OrQuery : public BinaryQuery
{
public:
	OrQuery(Query& lhs, Query& rhs);
	virtual QueryResult query(Text& fileobj);
	virtual std::string disp();
};



#endif

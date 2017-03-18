#ifndef NOT_QUERY_H
#define NOT_QUERY_H

#include "QueryBase.h"
#include "QueryResult.h"
#include "Text.h"
#include "Query.h"

class NotQuery : public QueryBase
{
public:
	NotQuery(Query& q);
	virtual QueryResult query(Text& fileobj);
	virtual std::string disp();

private:
	Query _qry;
};


#endif

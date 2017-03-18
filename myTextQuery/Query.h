#ifndef QUERY_H
#define QUERY_H

#include "QueryBase.h"
#include "QueryResult.h"
#include "Text.h"
#include <memory>



class Query
{
public:
	Query(std::string word);
	Query(std::shared_ptr<QueryBase> qb_ptr);
	QueryResult query(Text& fileobj);
	std::string disp();

	friend Query operator |(Query& lhs, Query& rhs);
	friend Query operator &(Query& lhs, Query& rhs);
	friend Query operator ~(Query& q);


private:
	std::shared_ptr<QueryBase> _ptr_query_base;


};

Query operator |(Query& lhs, Query& rhs);
Query operator &(Query& lhs, Query& rhs);
Query operator ~(Query& q);


#endif
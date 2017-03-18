#include "Query.h"
#include "WordQuery.h"
#include "OrQuery.h"
#include "AndQuery.h"
#include "NotQuery.h"

Query::Query(std::string word)
	:_ptr_query_base(new WordQuery(word))
{
	
}

Query::Query(std::shared_ptr<QueryBase> qb_ptr)
	:_ptr_query_base(qb_ptr)
{

}

QueryResult Query::query(Text & fileobj)
{
	return _ptr_query_base->query(fileobj);
}

std::string Query::disp()
{
	return _ptr_query_base->disp();
}


Query operator |(Query& lhs, Query& rhs)
{

	std::shared_ptr<QueryBase> ptr_base(new OrQuery(lhs, rhs));
	return Query(ptr_base);
}

Query operator &(Query& lhs, Query& rhs)
{
	std::shared_ptr<QueryBase> ptr_base(new AndQuery(lhs, rhs));
	return Query(ptr_base);
}

Query operator ~(Query& q)
{
	std::shared_ptr<QueryBase> ptr_base(new NotQuery(q));
	return Query(ptr_base);
}

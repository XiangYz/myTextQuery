#include "OrQuery.h"
#include <algorithm>
#include <set>
#include <iterator>

OrQuery::OrQuery(Query& lhs, Query& rhs)
	:BinaryQuery(lhs, rhs)
{
}

QueryResult OrQuery::query(Text & fileobj)
{

	QueryResult qrl = _lhs.query(fileobj);
	QueryResult qrr = _rhs.query(fileobj);

	std::shared_ptr<std::set<size_t> > res_set;
	if (qrl._res_lineno || qrr._res_lineno)
		res_set = std::make_shared<std::set<size_t> >();
	
	if (qrl._res_lineno)
		res_set->insert(qrl._res_lineno->begin(), qrl._res_lineno->end());
	if (qrr._res_lineno)
		res_set->insert(qrr._res_lineno->begin(), qrr._res_lineno->end());


	return  QueryResult(disp(), qrl._file_lines, res_set);
}

std::string OrQuery::disp()
{
	return _lhs.disp() + " | " + _rhs.disp();
}

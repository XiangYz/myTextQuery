#include "AndQuery.h"
#include <algorithm>
#include <iterator>
#include <set>

AndQuery::AndQuery(Query& lhs, Query& rhs)
	:BinaryQuery(lhs, rhs)
{
}

QueryResult AndQuery::query(Text & fileobj)
{
	QueryResult qrl = _lhs.query(fileobj);
	QueryResult qrr = _rhs.query(fileobj);

	std::shared_ptr<std::set<size_t> > res_set;

	if (qrl._res_lineno && qrr._res_lineno)
	{
		res_set = std::make_shared<std::set<size_t> >();

		std::set_intersection(qrl._res_lineno->begin(), qrl._res_lineno->end()
			, qrr._res_lineno->begin(), qrr._res_lineno->end()
			, std::inserter(*res_set, res_set->begin()));
	}


	return  QueryResult(disp(), qrl._file_lines, res_set);
}

std::string AndQuery::disp()
{
	return _lhs.disp() + " & " + _rhs.disp();
}

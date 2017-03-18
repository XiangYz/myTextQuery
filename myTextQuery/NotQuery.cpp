#include "NotQuery.h"
#include "Query.h"

NotQuery::NotQuery(Query & q)
	:_qry(q)
{
}

QueryResult NotQuery::query(Text & fileobj)
{
	QueryResult qr = _qry.query(fileobj);

	std::shared_ptr<std::set<size_t> > res_set;

	if (qr._res_lineno)
	{
		res_set = std::make_shared<std::set<size_t> >();

		size_t size = qr._file_lines->size();
		for (int i = 0; i < size; ++i)
		{
			auto iter = qr._res_lineno->find(i);
			if (qr._res_lineno->end() == iter)
			{
				res_set->insert(i);
			}
		}
	}

	return  QueryResult(disp(), qr._file_lines, res_set);
}

std::string NotQuery::disp()
{
	return "~" + _qry.disp();
}

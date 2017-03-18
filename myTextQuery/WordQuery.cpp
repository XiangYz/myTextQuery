#include "WordQuery.h"

WordQuery::WordQuery(std::string word)
	:_word(word)
{
}

QueryResult WordQuery::query(Text& fileobj)
{
	if (!fileobj)
	{
		return QueryResult(_word, nullptr, nullptr);
	}

	QueryResult::_WORD_LINENO_PTR word_lineno = fileobj.GetWordLinesNo(_word);

	return QueryResult(disp(), fileobj.GetFileLines(), word_lineno);

}

std::string WordQuery::disp()
{
	return _word;
}

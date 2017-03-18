#ifndef WORD_QUERY_H
#define WORD_QUERY_H

#include <string>
#include "QueryResult.h"
#include "Text.h"
#include "QueryBase.h"

class WordQuery : public QueryBase
{
public:
	WordQuery(std::string word);
	virtual QueryResult query(Text& fileobj);
	virtual std::string disp();

private:
	std::string _word;
};


#endif
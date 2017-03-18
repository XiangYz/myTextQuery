#ifndef TEXT_H
#define TEXT_H

#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <memory>
#include <string>

class Text
{
public:
	typedef std::shared_ptr< std::vector<std::string> > _FILELINES_PTR;
	typedef std::shared_ptr< std::set<size_t> > _WORD_LINENO_PTR;

	Text(std::ifstream& ifs);
	_FILELINES_PTR GetFileLines();
	_WORD_LINENO_PTR GetWordLinesNo(std::string word);

	operator bool();

private:
	std::shared_ptr<std::vector<std::string> > DePunc(std::string& word);

private:
	_FILELINES_PTR _ptr_vec_file_line;
	std::map<std::string, _WORD_LINENO_PTR> _map_word_linenos;
};


#endif

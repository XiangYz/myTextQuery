#include "Text.h"
#include <iostream>
#include <sstream>
#include <cctype>

Text::Text(std::ifstream & ifs) try
	:_ptr_vec_file_line(new std::vector<std::string>)
{
	if (!ifs) throw std::invalid_argument("ifs is bad");
	
	std::string line;
	while (std::getline(ifs, line))
	{
		// 记录每一行
		_ptr_vec_file_line->push_back(line);

		std::stringstream ss(line);
		std::string word;
		while (ss >> word)
		{
			std::shared_ptr<std::vector<std::string> > res = DePunc(word);
			for (auto& e : *res)
			{

				_WORD_LINENO_PTR& word_nos = _map_word_linenos[e];
				if (!word_nos)
				{
					word_nos.reset(new std::set<size_t>);
				}
				word_nos->insert(_ptr_vec_file_line->size() - 1);

			}
		}
	}
}
catch(const std::exception& e)
{
	std::cerr << e.what() << std::endl;
	exit(-1);
}

Text::_FILELINES_PTR Text::GetFileLines()
{
	return _ptr_vec_file_line;
}

Text::_WORD_LINENO_PTR Text::GetWordLinesNo(std::string word)
{
	std::map<std::string, _WORD_LINENO_PTR>::iterator it =
		_map_word_linenos.find(word);
	
	if (it != _map_word_linenos.end())
	{
		return it->second;
	}
	else
		return nullptr;
}

Text::operator bool()
{
	if (_ptr_vec_file_line) return true;

	return false;
}

std::shared_ptr<std::vector<std::string> >  Text::DePunc(std::string & word)
{

	std::shared_ptr<std::vector<std::string> > res =
		std::make_shared<std::vector<std::string> >();

	std::string one;
	std::string::iterator it = word.begin();
	while (it != word.end())
	{
		char ch = *it;
		if (std::ispunct(ch))
		{
			if (!one.empty())
			{
				res->push_back(one);
				one.clear();
			}
		}
		else
		{
			one.push_back(ch);
		}

		++it;
	}

	if (!one.empty())
	{
		res->push_back(one);
		one.clear();
	}
	return res;
}

//
// Created by Mike Smith on 2017/3/15.
//

#include <fstream>
#include "charset.h"

Charset::Charset(const std::string &path)
{
	std::ifstream file(path);
	std::string ch;
	
	while (!file.eof())
	{
		file >> ch;
		_charset.insert(ch);
	}
	
	file.close();
}

bool Charset::contain(const std::string &ch) const
{
	return (_charset.count(ch) != 0);
}

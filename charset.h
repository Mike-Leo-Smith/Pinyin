//
// Created by Mike Smith on 2017/3/15.
//

#ifndef PINYIN_CHARSET_H
#define PINYIN_CHARSET_H

#include <set>
#include <string>
#include <iostream>

class Charset
{
private:
	std::set<std::string> _charset;
	
public:
	Charset(const std::string &path);
	bool contain(const std::string &ch) const;
};

#endif  // PINYIN_CHARSET_H

//
// Created by Mike Smith on 2017/3/15.
//

#ifndef PINYIN_SPELL_H
#define PINYIN_SPELL_H

#include <map>
#include <vector>
#include <string>
#include <iostream>

class Spell
{
private:
	std::map<std::string, std::vector<std::string>> _spell_table;
	
public:
	Spell(const std::string &path);
	const std::vector<std::string> operator[](const std::string &spell) const;
};

#endif  // PINYIN_SPELL_H

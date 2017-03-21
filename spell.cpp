//
// Created by Mike Smith on 2017/3/15.
//

#include <fstream>
#include "spell.h"

Spell::Spell(const std::string &path)
{
	std::ifstream file(path);
	std::string curr_spell;
	std::string tmp;
	
	while (!file.eof())
	{
		file >> tmp;
		if (std::isalpha(tmp[0]))
		{
			curr_spell = tmp;
		}
		else
		{
			_spell_table[curr_spell].push_back(tmp);
		}
	}
	
	file.close();
}

const std::vector<std::string> Spell::operator[](const std::string &spell) const
{
	if (_spell_table.count(spell) > 0)
	{
		return _spell_table.at(spell);
	}
	else
	{
		std::vector<std::string> tmp;
		tmp.push_back("_");
		return tmp;
	}
}

//
// Created by Mike Smith on 2017/3/15.
//

#include <fstream>
#include "frequency.h"
#include "charset.h"

Statistics::Statistics(const std::string &word_stat_path, const std::string &phrase_stat_path)
{
	if (word_stat_path != "")
	{
		std::ifstream file(word_stat_path);
		std::string word;
		int freq;
		
		while (!file.eof())
		{
			file >> word >> freq;
			_word_stat[word] = freq;
		}
		file.close();
	}
	
	if (phrase_stat_path != "")
	{
		std::ifstream file(phrase_stat_path);
		std::string w1, w2;
		int freq;
		
		while (!file.eof())
		{
			file >> w1 >> w2 >> freq;
			_phrase_stat[w1][w2] = freq;
		}
		file.close();
	}
}

void Statistics::load(const std::string &path, const Charset &charset, int learning_rate)
{
	std::ifstream file(path);
	std::string prev, curr;
	
	int count = 0;
	
	while (!file.eof())
	{
		if (prev ==  "" || !charset.contain(prev))
		{
			file >> prev;
			continue;
		}
		_word_stat[prev] += learning_rate;
		
		file >> curr;
		if (curr == "" || !charset.contain(curr))
		{
			prev = "";
			continue;
		}
		count++;
		
		if (!(count % 10000))
		{
			std::cout << "Count: " << count << std::endl;
		}
		
		_phrase_stat[prev][curr] += learning_rate;
		prev = curr;
	}
	file.close();
}

void Statistics::save(const std::string &word_stat_path, const std::string &phrase_stat_path) const
{
	std::ofstream word_file(word_stat_path);
	
	for (const auto &word : _word_stat)
	{
		word_file << word.first << " " << word.second << " " << std::endl;
	}
	word_file.close();
	
	std::ofstream phrase_file(phrase_stat_path);
	
	for (const auto &w1 : _phrase_stat)
	{
		for (const auto &w2 : w1.second)
		{
			phrase_file << w1.first << " " << w2.first << " " << w2.second << " ";
		}
		phrase_file << std::endl;
	}
	phrase_file.close();
}

int Statistics::frequency(const std::string &word) const
{
	try
	{
		return _word_stat.at(word);
	}
	catch (std::out_of_range)
	{
		return 0;
	}
}

int Statistics::weight(const std::string &w1, const std::string &w2) const
{
	try
	{
		return _phrase_stat.at(w1).at(w2);
	}
	catch (std::out_of_range)
	{
		return 0;
	}
}
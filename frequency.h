//
// Created by Mike Smith on 2017/3/15.
//

#ifndef PINYIN_FREQUENCY_H
#define PINYIN_FREQUENCY_H

#include <map>
#include <string>
#include "charset.h"

class Statistics
{
private:
	std::map<std::string, std::map<std::string, int>> _phrase_stat;
	std::map<std::string, int> _word_stat;

public:
	Statistics(const std::string &word_stat_path = "", const std::string &phrase_stat_path = "");
	void load(const std::string &path, const Charset &charset, int learning_rate = 1);
	void save(const std::string &word_stat_path, const std::string &phrase_stat_path) const;
	int frequency(const std::string &word) const;
	int weight(const std::string &w1, const std::string &w2) const;
};

#endif  // PINYIN_FREQUENCY_H

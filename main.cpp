#include <iostream>
#include <vector>
#include <cmath>
#include "charset.h"
#include "spell.h"
#include "frequency.h"

std::string spell_to_phrase(const std::vector<std::string> &syllable_list, const Spell &spell, const Statistics &statistics)
{
	if (syllable_list.size() <= 1)
	{
		std::string result;
		
		for (const auto &word : spell[syllable_list[0]])
		{
			if (statistics.frequency(word) >= statistics.frequency(result))
			{
				result = word;
			}
		}
		return result;
	}
	
	struct SearchNode
	{
		std::string prev;
		std::string curr;
		int max_match;
		
		SearchNode(const std::string &current) : curr(current), max_match(0) {}
	};
	
	std::vector<std::vector<SearchNode>> search_table(syllable_list.size());
	auto search_table_iter = search_table.begin();
	
	for (const auto &syllable : syllable_list)
	{
		for (const auto &ch : spell[syllable])
		{
			search_table_iter->push_back(SearchNode(ch));
		}
		search_table_iter++;
	}
	
	auto node_cmp = [&statistics](const struct SearchNode &a, const SearchNode &b) -> bool
	{
		return statistics.frequency(a.curr) < statistics.frequency(b.curr);
	};
	
	for (auto &node_vector : search_table)
	{
		std::sort(node_vector.begin(), node_vector.end(), node_cmp);
	}
	
	for (search_table_iter = search_table.begin() + 1; search_table_iter != search_table.end(); search_table_iter++)
	{
		for (auto &curr_node : *search_table_iter)
		{
			for (const auto &prev_node : *(search_table_iter - 1))
			{
				//int new_match = statistics.weight(prev_node.curr, curr_node.curr) + prev_node.max_match;
				int new_match = (int)log10(statistics.weight(prev_node.curr, curr_node.curr) + 1) + prev_node.max_match;
				
				if (new_match >= curr_node.max_match)
				{
					curr_node.prev = prev_node.curr;
					curr_node.max_match = new_match;
				}
			}
		}
	}
	
	auto node_match_max = search_table.back().cbegin();
	
	for (auto node_iter = search_table.back().cbegin() + 1; node_iter != search_table.back().cend(); node_iter++)
	{
		if (node_iter->max_match > node_match_max->max_match)
		{
			node_match_max = node_iter;
		}
	}
	
	std::vector<std::string> rev_result(syllable_list.size());
	std::string curr_word = node_match_max->curr;
	
	for (auto search_table_rev_iter = search_table.crbegin(); search_table_rev_iter != search_table.crend(); search_table_rev_iter++)
	{
		rev_result.push_back(curr_word);
		for (const auto &node : *search_table_rev_iter)
		{
			if (node.curr == curr_word)
			{
				curr_word = node.prev;
				break;
			}
		}
	}
	
	std::string result;
	
	for (auto result_iter = rev_result.crbegin(); result_iter != rev_result.crend(); result_iter++)
	{
		result += *result_iter;
	}
	
	return result;
}

int main(void)
{
	clock_t t0 = clock();
	Statistics statistics("word-statistics.dat", "phrase-statistics.dat");
	Charset charset("charset-new.dat");
	
	statistics.load("passage.dat", charset, 1000);
	statistics.load("poetry-tang.dat", charset, 300);
	statistics.load("poetry-modern.dat", charset, 300);
	statistics.load("poetry-song.dat", charset, 200);
	statistics.load("poetry-shijing.dat", charset, 100);
	statistics.load("idiom.dat", charset, 400);
	statistics.load("novel.dat", charset, 50);
	statistics.load("addition.dat", charset, 400);
	
	Spell spell("spell-new.dat");
	
	std::cout << "Initialization Time: " << (clock() - t0) / 1000.0f << "ms" << std::endl << std::endl;
	//statistics.save("word-statistics.dat", "phrase-statistics.dat");
	
	while (true)
	{
		std::vector<std::string> syllable_list;
		int c = 0;
		
		while (c != '\n')
		{
			std::string tmp;
			
			std::cin >> tmp;
			
			for (auto &ch : tmp)
			{
				ch = (char)tolower(ch);
			}
			
			if (tmp == "exit")
			{
				return 0;
			}
			
			syllable_list.push_back(tmp);
			c = std::cin.get();
		}
		
		if (syllable_list.back() == " ")
		{
			syllable_list.pop_back();
		}
		
		clock_t t1 = clock();
		std::cout << spell_to_phrase(syllable_list, spell, statistics) << std::endl;
		std::cout << "Elapse Time: " << (clock() - t1) / 1000.0f << "ms" << std::endl << std::endl;
	}
}
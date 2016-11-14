#pragma once
#include "CMatch.hpp"

bool isListValid_bounds(MTermSet Comb);
bool isListValid_bounds_range(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend);
bool isListValid_count(MTermSet Comb);
bool isListValid_count_range(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend);
bool isListValid_bounds(MTermSetCombinatoria &listComb);
bool isListValid_count(MTermSetCombinatoria &listComb);
bool isListValid(MTermSetCombinatoria &listComb);
bool isListValid(MTermSet &Comb);
bool isListValid_range(std::vector<HTerm>::iterator vbegin, std::vector<HTerm>::iterator vend);


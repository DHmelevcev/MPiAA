#pragma once

#include <vector>
#include <set>
#include <algorithm>

bool has_duplicates(const std::vector<int>& data);
bool has_duplicates_set(const std::vector<int>& data);
bool has_duplicates_sort(const std::vector<int>& data);

std::vector<int> get_duplicates(const std::vector<int>& data);
std::vector<int> get_duplicates_set(const std::vector<int>& data);
std::vector<int> get_duplicates_sort(const std::vector<int>& data);
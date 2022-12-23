#include "duplicates.h"

bool has_duplicates(const std::vector<int>& data) {
	for (int i = 0, size = data.size(); i < size - 1; i++) {
		for (int j = i + 1; j < size; j++)
			if (data[i] == data[j])
				return true;
	}
	return false;
}

bool has_duplicates_set(const std::vector<int>& data) {
	std::set<int> my_set;
	for (auto elem : data) {
		int count = my_set.size();
		my_set.insert(elem);
		if (my_set.size() == count)
			return true;
	}
	return false;
}

bool has_duplicates_sort(const std::vector<int>& data) {
	std::vector<int> my_vector = data;
	std::sort(my_vector.begin(), my_vector.end());
	for (int i = 0, j = 1, size = my_vector.size(); j < size; i++, j++)
		if (my_vector[i] == my_vector[j])
			return true;
	return false;
}

std::vector<int> get_duplicates(const std::vector<int>& data) {
	std::vector<int> result;
	for (int i = 0, size = data.size(); i < size - 1; i++) {
		for (int j = i + 1; j < size; j++)
			if (data[i] == data[j]) {
				bool skip = false;
				for (auto elem : result)
					if (data[i] == elem)
						skip = true;
				if (!skip)
					result.push_back(data[i]);
			}
	}
	return result;
}

std::vector<int> get_duplicates_set(const std::vector<int>& data) {
	std::set<int> result;
	std::set<int> my_set;
	for (auto elem : data) {
		int count = my_set.size();
		my_set.insert(elem);
		if (my_set.size() == count)
			result.insert(elem);
	}
	return std::vector<int> (result.begin(), result.end());
}

std::vector<int> get_duplicates_sort(const std::vector<int>& data) {
	std::vector<int> result;
	std::vector<int> my_vector = data;
	std::sort(my_vector.begin(), my_vector.end());
	for (int i = 0, j = 1, size = my_vector.size(), flag = false; j < size; i++, j++) {
		if (my_vector[i] == my_vector[j]) {
			if (!flag) {
				result.push_back(my_vector[j]);
				flag = true;
			}
		}
		else
			flag = false;
	}
	return result;
}
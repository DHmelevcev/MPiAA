#include "hash_functions.h"

std::size_t hash1(const std::string& key) {
	std::size_t hash = 0;
	for (auto elem : key)
		hash += elem;
	return hash;
}

std::size_t hash2(const std::string& key) {
	int a = 31;
	std::size_t hash = 0;
	for (auto i = 0; i < key.size(); i++)
		hash += key[i] * pow(a, i);
	return hash;
}

std::size_t hash3(const std::string& key) {
	int a = 11;
	int b = 23;
	int c = 7;
	std::size_t hash = 0;
	std::vector<int> h(key.size());
	h[0] = c;
	for (auto i = 1; i < h.size(); i++)
		h[i] = (h[i - 1] << a | h[i - 1] >> b) + int(key[i]);
	for (auto elem : h)
		hash += elem;
	return hash;
}
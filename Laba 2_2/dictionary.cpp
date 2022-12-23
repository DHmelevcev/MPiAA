#include "dictionary.h"

Dictionary::Dictionary(int num_of_buckets, HashFunction hash) :
    table(num_of_buckets), hash_function(hash) {
}

Dictionary::~Dictionary() {
}

void Dictionary::set(const std::string& key, const std::string& value) {
    // Insert key-value pair into the dictionary.
    // If such key already exists, replace old value with the new one.
    int pos = abs(int(hash_function(key) % table.size()));
    if (!table[pos].empty())
        for (auto it = table[pos].begin(); it != table[pos].end(); it++)
            if ((*it).first == key) {
                (*it).second = value;
                return;
            }

    table[pos].push_back(std::make_pair(std::string(key), std::string(value)));
}

std::string Dictionary::get(const std::string& key) const {
    // Return value for the key.
    // Return empty string if there is no such key.
    int pos = abs(int(hash_function(key) % table.size()));
    if (!table[pos].empty())
        for (KeyValue elem : table[pos])
            if (elem.first == key)
                return elem.second;

    return "";
}

int Dictionary::size() const {
    // Return size of the dictionary, i.e. number of key-value pairs.    
    int size = 0;
    for (const auto& bucket : table) {
        size += bucket.size();
    }
    return size;
}
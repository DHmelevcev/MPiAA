#include "count_sort.h"

// Return sorted array. 
// All elements of array are assumed to be from [min, max] range.
std::vector<int> count_sort(const std::vector<int>& array, int min, int max) {
    std::vector<int> result;

    std::vector<int> counter(max - min + 1);
    for (int elem : array) {
        counter[elem - min]++;
    }
    
    for (int i = 0; i < max - min + 1; i++)
        for (int j = 0; j < counter[i]; j++)
            result.push_back(i + min);

    return result;
}
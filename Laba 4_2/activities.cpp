#include "activities.h"

std::vector<Activity> get_max_activities(const std::vector<Activity>& activities) {
	// Function must return a maximum-size subset of mutually compatible activities.
	// Each activity is described by its start and finish times: [start, finish), 0 <= start < finish.
	// Activities are compatible if their time intervals don't overlap.
	// Activities may be given in unsorted order and the result may not be sorted too.

	if (activities.size() == 0)
		return {};

	Activity a(-1, -1);
	for (auto elem : activities)
		if (a.start == -1 || elem.finish < a.finish)
			a = elem;

	std::vector<Activity> acts_to_get;
	for (auto elem : activities)
		if (elem.start >= a.finish)
			acts_to_get.push_back(elem);

	std::vector<Activity> result = get_max_activities(acts_to_get);
	result.push_back(a);
	return result;
}

//std::vector<Activity> get_max_activities(const std::vector<Activity>& activities) {
//	// Function must return a maximum-size subset of mutually compatible activities.
//	// Each activity is described by its start and finish times: [start, finish), 0 <= start < finish.
//	// Activities are compatible if their time intervals don't overlap.
//	// Activities may be given in unsorted order and the result may not be sorted too.
//
//	//get all subsets of set
//	std::vector<std::vector<Activity>> v(pow(2, activities.size()));
//	for (size_t i = 0b0; i < v.size(); i++)
//		for (size_t j = 0; j < activities.size(); j++)
//			if (i & 1 << j)
//				v[i].push_back(activities[j]);
//
//	//clear all wrong subsets
//	for (size_t i = 0; i < v.size(); i++)
//		for (size_t j = 0; j != -1 && j < v[i].size(); j++)
//			for (size_t k = j + 1; k < v[i].size(); k++)
//				if (v[i][j].start < v[i][k].finish && v[i][j].finish > v[i][k].start) {
//					v[i].clear();
//					j = -2; break;
//				}
//
//	std::vector<Activity> result;
//
//	//select longest subset
//	for (auto it = v.begin(); it < v.end(); it++)
//		if (it->size() > result.size())
//			result = *it;
//
//	return result;
//}
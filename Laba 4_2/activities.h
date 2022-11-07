#pragma once

#include "activity.h"

#include <vector>
#include <algorithm>

// Get a maximum-size subset of mutually compatible activities.
std::vector<Activity> get_max_activities(const std::vector<Activity>& activities);
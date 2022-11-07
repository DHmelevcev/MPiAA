#pragma once

#include "point.h"

#include <vector>
#include <algorithm>

// Find the closest pair of points from given points.
std::pair<Point, Point> closest_pair_between(std::vector<Point>& points, int l, int r, int m, double d);
std::pair<Point, Point> closest_pair_rec(std::vector<Point>& points, int l, int r);
std::pair<Point, Point> closest_pair(const std::vector<Point>& points);
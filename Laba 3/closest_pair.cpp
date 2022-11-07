#include "closest_pair.h"

#include <stdexcept>

using namespace std;

//std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
//	// Return the closest pair of points from given points.
//	// Order of points in the result doesn't matter.
//	// If there are fewer than 2 points, throw an exception.
//
//	if (points.size() < 2) {
//		throw invalid_argument("Not enough points");
//	}
//
//	auto result = std::make_pair(Point(), Point());
//	double closest_distance = -1;
//
//	for (int i = 0; i < points.size() - 1; i++)
//		for (int j = i + 1; j < points.size(); j++)
//			if (closest_distance == -1 or points[i].distance(points[j]) < closest_distance) {
//				closest_distance = points[i].distance(points[j]);
//				result.first = points[i];
//				result.second = points[j];
//			}
//
//	return result;
//}

std::pair<Point, Point> closest_pair_between(std::vector<Point>& points, int l, int r, int m, double d) {
	auto result = std::make_pair(Point(), Point());

	vector<Point> pstripe;
	double Xm = points[m].x;

	for (int i = l; i < r; i++) {
		double Xi = points[i].x;
		if (abs(Xi - Xm) < d)
			pstripe.push_back(points[i]);
	}

	sort(pstripe.begin(), pstripe.end(), [](Point& a, Point& b) { return a.y < b.y; });

	double closest_distance = -1;

	for (int i = 1; i < pstripe.size(); i++)
		for (int j = i - 1; j >= 0; j--) {
			double Yi = pstripe[i].y;
			double Yj = pstripe[j].y;
			if ((Yi - Yj) >= d)
				break;
			if (closest_distance == -1 or pstripe[i].distance(pstripe[j]) < closest_distance) {
				closest_distance = pstripe[i].distance(pstripe[j]);
				result.first = pstripe[i];
				result.second = pstripe[j];
			}
		}
	
	return result;
}

std::pair<Point, Point> closest_pair_rec(std::vector<Point>& points, int l, int r) {
	auto result = std::make_pair(Point(), Point());

	if (r - l <= 3) {
		double closest_distance = -1;

		for (int i = l; i < r - 1; i++)
			for (int j = i + 1; j < r; j++)
				if (closest_distance == -1 or points[i].distance(points[j]) < closest_distance) {
					closest_distance = points[i].distance(points[j]);
					result.first = points[i];
					result.second = points[j];
				}

		return result;
	}
	else {
		sort(points.begin() + l, points.begin() + r);
		int m = (l + r) / 2;
		
		auto pl = closest_pair_rec(points, l, m);
		auto pr = closest_pair_rec(points, m, r);

		double d = min(pl.first.distance(pl.second), pr.first.distance(pr.second));

		auto pb = closest_pair_between(points, l, r, m, d);

		if (pl.first.distance(pl.second) < pr.first.distance(pr.second))
			result = pl;
		else
			result = pr;
		if (result.first.distance(result.second) < pb.first.distance(pb.second))
			return result;
		else
			return pb;
	}
}

std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
	// Return the closest pair of points from given points.
	// Order of points in the result doesn't matter.
	// If there are fewer than 2 points, throw an exception.

	if (points.size() < 2) {
		throw invalid_argument("Not enough points");
	}

	vector<Point> points_copy = points;

	return closest_pair_rec(points_copy, 0, points_copy.size());
}
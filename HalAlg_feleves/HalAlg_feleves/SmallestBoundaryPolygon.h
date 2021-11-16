#pragma once
#include <vector>
#include <string>

const float PI = 3.14159265358979f;

class Point
{
public:
	float x;
	float y;
};

class SmallestBoundaryPolygon
{
protected:
	std::vector<Point> points;

	float distanceFromLine(Point lp1, Point lp2, Point p);
	float outerDistanceToBoundary(std::vector<Point> solution);
	float lengthOfBoundary(std::vector<Point> solution);

	float objective(std::vector<Point> solution);
	float constraint(std::vector<Point> solution);
public:
	void loadPointsFromFile(std::string fileName);
	void savePointsToFile(std::string fileName, std::vector<Point> points, std::vector<Point> boundarypoints, Point centroid);
};
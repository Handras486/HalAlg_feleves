#include "SmallestBoundaryPolygon.h"
#include <fstream>
#include <math.h>

using namespace std;

//
// Basic IO
//
void SmallestBoundaryPolygon::loadPointsFromFile(string fileName) {
	ifstream fpoints(fileName);
	while (!fpoints.eof()) {
		Point pnt;
		fpoints >> pnt.x;
		fpoints >> pnt.y;
		points.push_back(pnt);
	};
	fpoints.close();
}

void SmallestBoundaryPolygon::savePointsToFile(string fileName, vector<Point> points, vector<Point> boundarypoints, Point centroid) {

	string filepath = "../Logs/" + fileName;

	ofstream fpoints(filepath);

	//pontok
	for (Point pnt : points) {
		fpoints << "point(" << pnt.x << "|" << pnt.y <<" \"p\" )"<< endl;    
	};
	fpoints << endl;

	//körhatár pontok és vonalak
	for (Point pnt : boundarypoints) {
		fpoints << "point(" << pnt.x << "|" << pnt.y << " \"b\" )" << endl;
	};
	fpoints << endl;
	for (size_t i = 0; i < boundarypoints.size(); i++)
	{
		fpoints << "lineseg(" << boundarypoints[i].x << "|" << boundarypoints[i].y << " " << boundarypoints[(i+1) % boundarypoints.size()].x 
			<< "|" << boundarypoints[(i+1) % boundarypoints.size()].y << ")" << endl;
	}
	fpoints << endl;

	//középpont
	fpoints << "point(" << centroid.x << "|" << centroid.y << " \"c\" )" << endl;

	fpoints.close();
}

//
// Helper functions
//

//egy pont egy egyenestõl való távolsága
float SmallestBoundaryPolygon::distanceFromLine(Point lp1, Point lp2, Point p) {
	// https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
	return ((lp2.y - lp1.y) * p.x - (lp2.x - lp1.x) * p.y + lp2.x * lp1.y - lp2.y * lp1.x) / sqrt(pow(lp2.y - lp1.y, 2) + pow(lp2.x - lp1.x, 2));
}

// bal oldal(rossz oldal) = negatív érték; jobb oldal = pozitív ; visszadja a poligonon kívüli pontok távolságának összegét
float SmallestBoundaryPolygon::outerDistanceToBoundary(vector<Point> solution) {
	float sum_min_distances = 0;

	for (unsigned int pi = 0; pi < points.size(); pi++) {
		float min_dist;
		for (unsigned int li = 0; li < solution.size(); li++) {
			float act_dist = distanceFromLine(solution[li], solution[(li + 1) % solution.size()], points[pi]);
			if (li == 0 || act_dist < min_dist)
				min_dist = act_dist;
		}
		if (min_dist < 0)
			sum_min_distances += -min_dist;
	}
	return sum_min_distances;                
}

//körbefoglaló poligon kerülete 
float SmallestBoundaryPolygon::lengthOfBoundary(vector<Point> solution) {
	float sum_length = 0;

	for (unsigned int li = 0; li < solution.size() - 1; li++) {
		Point p1 = solution[li];
		Point p2 = solution[(li + 1) % solution.size()];
		sum_length += sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
	}
	return sum_length;
}

//célfüggvény

//
// Objective functions
//
float SmallestBoundaryPolygon::objective(std::vector<Point> solution)
{
	return lengthOfBoundary(solution);
}

//megszorítás, ha negatív érték, pontok a poligonon kívül vannak, 0 -> minden pont a poligonon belül

float SmallestBoundaryPolygon::constraint(std::vector<Point> solution)
{
	return -outerDistanceToBoundary(solution);
}
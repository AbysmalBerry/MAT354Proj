#pragma once
#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <utility>
#include <vector>


#define CIRCLERADIUS 10
#define MIN_DISTANCE_BETWEEN 20.0f
struct Polygon
{
	std::vector<
		std::pair<Vector2, Vector2>
	> m_polygon;
};



class MainManager
{
private:
	Vector2 m_centerPos;

	int m_numberOfPoints;

	bool m_valueBoxInput = false;


	bool m_generateNewPoints = true;

	bool m_generateConvexHull = false;



	//List of points
	std::vector<Vector2> m_points;
	std::vector<Vector2> m_convexHullList;
public:

	//Other functions
	void GeneratePoints();
	void GenerateLinesBetweenPoints(Vector2 a, Vector2 b, Color color = BLUE);
	void GenerateConvexHull();











	//Main Functions
	MainManager();

	void Initialize();

	void Update();

	void Draw();

	void DrawGUI();

	void Clear();


	//
};


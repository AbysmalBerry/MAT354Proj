#pragma once
#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <utility>
#include <vector>


#define CIRCLERADIUS 10
#define MIN_DISTANCE_BETWEEN 10.0f
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




	//List of points
	std::vector<Vector2> m_points;
public:

	//Other functions
	void GeneratePoints();













	//Main Functions
	MainManager();

	void Initialize();

	void Update();

	void Draw();

	void DrawGUI();

	void Clear();


	//
};


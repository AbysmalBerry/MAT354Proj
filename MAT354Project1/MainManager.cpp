#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include "raygui.h"
#include "MainManager.h"
#include "raymath.h"

//Generate Points
void MainManager::GeneratePoints()
{

    m_points.clear();

    for (int i = 0; i < m_numberOfPoints; ++i)
    {
        Vector2 createNewPoint = Vector2{ static_cast<float>(rand() % GetScreenWidth()), static_cast<float>(rand() % GetScreenHeight() ) };

        if (m_points.empty())
        {
            m_points.push_back(createNewPoint);
        }
        else
        {
            bool temp = false;
            //Check and make sure the points are not near each other
            for (int j = 0; j < m_points.size(); ++j)
            {
                if (Vector2Distance(createNewPoint, m_points[j]) < MIN_DISTANCE_BETWEEN)
                {
                    temp = true; --i;
                    break;
                }

            }
            if(!temp)
                m_points.push_back(createNewPoint);
        }
    }


}

void MainManager::GenerateLinesBetweenPoints(Vector2 a, Vector2 b, Color color )
{
    DrawLineV(a, b, color);
}

void MainManager::GenerateConvexHull()
{
    m_convexHullList.clear();
    //Variable
    std::vector<Vector2> toBeCheckedList = m_points;


    //Get lowest y
    Vector2 lowestVertex = m_points[0];
    for (auto& i : m_points)
    {
        if (i.y < lowestVertex.y)
            lowestVertex = i;
    }

    Vector2 lineVector = Vector2{ 1.0f , 0.0f };

    Vector2 currentVertex = lowestVertex;
    //Remove Lowest 
    //toBeCheckedList.erase(std::find(toBeCheckedList.begin(), toBeCheckedList.end(), lowestVertex));

    do
    {
        float maxAngle = 0;
        Vector2 maxVertex = currentVertex;

        for (auto& vertex : toBeCheckedList)
        {
            Vector2 vec = Vector2Subtract(vertex, currentVertex);
            float angle = acosf(Vector2DotProduct(vec, lineVector) / (Vector2Length(vec) * Vector2Length(lineVector)));
            if (angle > maxAngle)
            {
                maxAngle = angle;
                maxVertex = vertex;
            }
            else if (angle == maxAngle)
            {
                if (Vector2Distance(currentVertex, vertex) > Vector2Distance(currentVertex, maxVertex))
                {
                    maxAngle = angle;
                    maxVertex = vertex;
                }
            }
        }

        m_convexHullList.push_back(maxVertex);
        if(!toBeCheckedList.empty())
            toBeCheckedList.erase(std::find(toBeCheckedList.begin(), toBeCheckedList.end(), maxVertex));


        lineVector = Vector2Subtract(currentVertex , maxVertex);
        currentVertex = maxVertex;

    } while (currentVertex != lowestVertex);


}

MainManager::MainManager()
{
    m_centerPos = Vector2{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
    m_numberOfPoints = 4;
}

void MainManager::Initialize()
{
    GeneratePoints();
}

void MainManager::Update()
{


}

void MainManager::Draw()
{

    for (Vector2 temp : m_points)
    {
        DrawCircleV(temp, CIRCLERADIUS, RED);
    }

    if (m_generateConvexHull)
    {
        for (int i = 0; i < m_convexHullList.size() - 1; ++i)
        {
            GenerateLinesBetweenPoints(m_convexHullList[i], m_convexHullList[i + 1]);
        }
        GenerateLinesBetweenPoints(m_convexHullList[0], m_convexHullList[m_convexHullList.size() - 1]);
    }


}

void MainManager::DrawGUI()
{
    if (GuiValueBox(Rectangle{ 50, 10, 100, 25 }, "Points : ", &m_numberOfPoints, 0, std::numeric_limits<int>::max(), m_valueBoxInput))
    {
        m_valueBoxInput = !m_valueBoxInput;
    }


    if (GuiButton(Rectangle{ 10, 40, 100, 25 }, "Generate Points"))
    {
        GeneratePoints();
    }


    if (GuiButton(Rectangle{ 10, 75, 125, 25 }, "Generate Convex Hull"))
    {
        GenerateConvexHull();
        std::cout << m_convexHullList.size() << std::endl;
        m_generateConvexHull = !m_generateConvexHull;
    }
}


void MainManager::Clear()
{
	std::cout << "Clear" << std::endl;
}

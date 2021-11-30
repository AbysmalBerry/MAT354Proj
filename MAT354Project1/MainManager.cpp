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
    m_convexHullList.clear();
    m_points.clear();

    for (int i = 0; i < m_numberOfPoints; ++i)
    {
        Vector2 createNewPoint = Vector2{ static_cast<float>(rand() % (GetScreenWidth() -  225) + 200), static_cast<float>(rand() % (GetScreenHeight() - 50) + 25 ) };

        if (m_points.empty())
        {
            m_points.push_back(createNewPoint);
        }
        else
        {
            bool temp = false;
            int counter = 0;
            //Check and make sure the points are not near each other
            for (int j = 0; j < m_points.size(); ++j)
            {
                if (Vector2Distance(createNewPoint, m_points[j]) < MIN_DISTANCE_BETWEEN)
                {
                    temp = true; --i;
                    break;
                }

                counter++;
                if (counter > 50)
                {
                    break;
                }
            }
            if (!temp)
            {
                m_points.push_back(createNewPoint);
                counter = 0;
            }
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

    if (m_points.size() <= 2)
    {
        return;
    }
    else
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
            if (!toBeCheckedList.empty())
                toBeCheckedList.erase(std::find(toBeCheckedList.begin(), toBeCheckedList.end(), maxVertex));


            lineVector = Vector2Subtract(currentVertex, maxVertex);
            currentVertex = maxVertex;

        } while (currentVertex != lowestVertex);

    }
}

MainManager::MainManager()
{
    m_centerPos = Vector2{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
    m_numberOfPoints = 0;
}

void MainManager::Initialize()
{
    GeneratePoints();
}

void MainManager::Update()
{
    if (IsMouseButtonPressed(0))
    {
        Vector2 test = GetMousePosition();
        if(test.x > 200)
            m_points.push_back(test);
    }

    if (IsKeyPressed(KEY_P))
    {
        ToggleFullscreen();
    }

}

void MainManager::Draw()
{

    for (Vector2 temp : m_points)
    {
        DrawCircleV(temp, CIRCLERADIUS, RED);
    }

    if (m_generateConvexHull)
    {
        if (m_convexHullList.size() > 0)
        {
            for (int i = 0; i < m_convexHullList.size() - 1; ++i)
            {
                GenerateLinesBetweenPoints(m_convexHullList[i], m_convexHullList[i + 1]);
            }
            GenerateLinesBetweenPoints(m_convexHullList[0], m_convexHullList[m_convexHullList.size() - 1]);
        }

        if (m_points.size() == 2)
        {
            DrawLine((int)m_points[0].x, (int)m_points[0].y, (int)m_points[1].x, (int)m_points[1].y, BLUE);
        }
    }


    DrawLine(175, 0, 175, GetScreenHeight(), BLACK);
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
        m_generateConvexHull = !m_generateConvexHull;
    }
}


void MainManager::Clear()
{
	std::cout << "Clear" << std::endl;
}

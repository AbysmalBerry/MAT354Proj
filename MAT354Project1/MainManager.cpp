#include <iostream>
#include <limits>
#include <cstdlib>
#include "raygui.h"
#include "MainManager.h"
#include "raymath.h"

//Generate Points
void MainManager::GeneratePoints()
{
    if (m_generateNewPoints)
    {
        m_points.clear();

        for (int i = 0; i < m_numberOfPoints; ++i)
        {
            Vector2 createNewPoint = Vector2{ static_cast<float>(rand() % GetScreenWidth()), static_cast<float>(rand() % GetScreenHeight()) };

            //Check and make sure the points are not near each other
            for (int j = 0; j < m_points.size(); ++j)
            {
                if (Vector2Distance(createNewPoint, m_points[j]) > MIN_DISTANCE_BETWEEN)
                {
                    m_points.push_back(createNewPoint);
                }
            }
        }
       
        m_generateNewPoints = false;
    }
}

MainManager::MainManager()
{
    m_centerPos = Vector2{(float)GetScreenWidth()/2, (float)GetScreenHeight()/2};
    m_numberOfPoints = 4;
}

void MainManager::Initialize()
{
	std::cout << "Initialize" << std::endl;
    GeneratePoints();
    std::cout << m_centerPos.x << "  " << m_centerPos.y << std::endl;
}

void MainManager::Update()
{
    //DrawText("Update", 10, 30, 20, DARKGRAY);


}

void MainManager::Draw()
{


   // DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);
    //DrawCircleV(m_centerPos, CIRCLERADIUS, RED);

    for (Vector2 temp : m_points)
    {
        DrawCircleV(temp, CIRCLERADIUS, RED);
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
        m_generateNewPoints = true;
    }

}


void MainManager::Clear()
{
	std::cout << "Clear" << std::endl;
}

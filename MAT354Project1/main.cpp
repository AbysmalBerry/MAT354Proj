#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "extras/raygui.h"
#include <iostream>
#include <vector>
#include <utility>
#include <memory>

#include "MainManager.h"


//(0,0) : Top-Left Corner
int main()
{

    // Initialization
       //--------------------------------------------------------------------------------------
    static const int WINDOW_SCREENWIDTH = 800;
    static const int WINDOW_SCREENHEIGHT = 450;

    bool showGUI = true;

    InitWindow(WINDOW_SCREENWIDTH, WINDOW_SCREENHEIGHT, "MAT354 Project");
    std::unique_ptr<MainManager> mainManager = std::make_unique<MainManager>();
    mainManager->Initialize();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mainManager->Update();
        //----------------------------------------------------------------------------------


        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw
        //----------------------------------------------------------------------------------
        mainManager->Draw();
        //----------------------------------------------------------------------------------

        // Draw GUI
        //----------------------------------------------------------------------------------

        if (IsKeyPressed(KEY_O))
            showGUI = !showGUI;

        if(showGUI)
            mainManager->DrawGUI();
        //----------------------------------------------------------------------------------
        EndDrawing();
    }
    mainManager->Clear();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;


}
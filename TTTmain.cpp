// #include "core.h"
#include "TTTGame.hpp"

int main()
{
    // Game Data/State Init ---------------------------------------------------------------
    Game game;
    game.window->InitializeWindow();
    
    // Main Game Loop ----------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        //Update Input
        game.input->UpdateInput(game.window, game.time);
        game.time->UpdateTime();

        // Raylib Draw Scope
        BeginDrawing();
            ClearBackground(WHITE);
            //If statement meant to switch between Main Menu Screen and Main Game Screen
            if (game.menu == 'm')
                game.MainMenu();
            else
            {
                game.MainGameState();
                //DrawText("Noice", 500, 500, 14, BLACK);
            }
        EndDrawing();
        
    }

    // De-Initialization -------------------------------------------------------------------
    CloseWindow();      // Close window and OpenGL context

    return 0;
}
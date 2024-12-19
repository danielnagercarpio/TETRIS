#include "C:\raylib\raylib\src\raylib.h" 
#include "game.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() 
{
    Color darkBlue = {44,44,127,255};
    InitWindow(300,600, "raylib Tetris");
    // How fast the game will run. 60 is the number of frames per seconds. 
    // If we don't specify this, the computer will run as fast as it can,
    // and it can vary between computers. We fix it to be equitative between computers
    SetTargetFPS(60);
    Game game = Game();

    while(WindowShouldClose() == false) // While windows should close; while windows is not closed; while window is opened
    {
        game.HandleInput();
        if(EventTriggered(0.02)){
            game.MoveBlockDown(); // Game Loop is executed 60 times per second
        }
        BeginDrawing(); // CREATES A blank canvas
        ClearBackground(darkBlue); // Clear background and set the color of the background
        game.Draw();
        EndDrawing(); // ENDS the canvas drawing       
    }

    CloseWindow();
}
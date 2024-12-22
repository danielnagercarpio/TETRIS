#include "C:\raylib\raylib\src\raylib.h" 
#include "game.h"
#include <iostream>

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
    Vector2 mousePoint = { 0.0f, 0.0f };
    Color darkBlue = {44,44,127,255};
    InitWindow(500,620, "DOZOM TETRIS");
    // How fast the game will run. 60 is the number of frames per seconds. 
    // If we don't specify this, the computer will run as fast as it can,
    // and it can vary between computers. We fix it to be equitative between computers
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Font fontPayToWin = LoadFontEx("Font/monogram.ttf", 44, 0, 0);

    Game game = Game();

    float currentTime = GetTime();

    float changeToElectricColorTime = currentTime + 10.0; // ten second timer
    float resetColorTime; // ten second timer
    bool resetColor = true;
    bool btnPayToWin;

    while(WindowShouldClose() == false) // While windows should close; while windows is not closed; while window is opened
    {
        mousePoint = GetMousePosition();
        btnPayToWin = false;
        UpdateMusicStream(game.music);
        game.HandleInput(CheckCollisionPointRec(mousePoint, {320, 415,170,180}));
        if(EventTriggered(0.5)){
            game.MoveBlockDown(); // Game Loop is executed 60 times per second
            currentTime = GetTime();
        }
        
        BeginDrawing(); // CREATES A blank canvas

        if(game.IsJActive())
        {
            ClearBackground(electricBlue);
        } 

         // Clear background and set the color of the background
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);

        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if(game.gameOver)
        {
            DrawTextEx(font,"GAMEOVER", {320, 450}, 38, 2, WHITE);
        }
        DrawRectangleRounded({320, 55,170,60}, 0.3, 6, lightBlue);
        char scoreText[10];

        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);


        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215,170,180}, 0.3, 6, lightBlue);
        DrawRectangleRounded({320, 415,170,180}, 0.3, 6, lightBlue);
        DrawTextEx(fontPayToWin, " PAY TO \n   WIN", {320+34/2, 450}, 38, 2, WHITE);
        game.Draw();
        EndDrawing(); // ENDS the canvas drawing       
    }

    CloseWindow();
}
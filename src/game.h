#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    ~Game();
    int GetTimeCounter();
    int IncrementTimeCounter();
    int ResetTimeCounter();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool IsJActive();
    bool gameOver;
    int score;
    Music music;

private:
    Grid grid;
    int timeCounter = 0;
    std::vector<Block> GetAllBlocks();
    Block GetRandomBlock();
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    bool JActive;
    void rotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int movedDownPoints);
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
};
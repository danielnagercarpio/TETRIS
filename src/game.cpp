#include "game.h"
#include <random>
#include <iostream>


Game::Game()
{
    grid = Grid(); // Creates a grid (20 * 10) -> 200 cells size
    blocks = GetAllBlocks(); // Returns all types of blocks (I, L, etc.)
    currentBlock = GetRandomBlock(); // Current block is a blockType
    nextBlock = GetRandomBlock(); // Next block is a blockType
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/08 - Puta.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    JActive = false;
    timeCounter = 0;
    active = false;
}


Game::~Game() // Create destructor
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

int Game::GetTimeCounter()
{
    return timeCounter;
}

int Game::IncrementTimeCounter()
{
    timeCounter++;
}

int Game::ResetTimeCounter()
{
    timeCounter++;
}

void Game::PayToWin()
{
    score = 99999;
}

Block Game::GetRandomBlock() // This function returns a random block defined in blocks
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size(); // blocks.size at this moment is the number of block types, then the operation is:
    //int randomIndex =  // blocks.size at this moment is the number of block types, then the operation is:
    // rand() returns a value between 0 and 32767 granted or higher
    // randomIndex = 105 % 6 = 3; then picks the number 3
    Block block = blocks[randomIndex]; // The block picked is between 0 and maxBlock size - 1
    blocks.erase(blocks.begin() + randomIndex); // Remove the block located in (Po + randomIndex); Removes the block recently assigned to block.
    return block; // Return the block erased
}

std::vector<Block> Game::GetAllBlocks() // Returns all types of blocks
{
    return {IBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock(), LDBlock(), RDBlock()}; 
}

void Game::Draw()
{
    grid.Draw(); // Draw the grid
    currentBlock.Draw(11, 11); // offsetX and offsetY; Are the margins where starts to draw
    switch(nextBlock.id)
    {
        case 3:
            nextBlock.Draw(255,290);
            break;
        case 4:
            nextBlock.Draw(255,280);
            break;
        default:
            nextBlock.Draw(270,270);
            break;
    }
}

void Game::HandleInput(bool btnPayToWin)
{
    int keyPressed = GetKeyPressed(); // Get key pressed with raylib
    if (btnPayToWin) {
        grid.ClearDownGrid(currentBlock.GetCenterPositionY()+3);
        score = 99999;
    }
    if(gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    switch(keyPressed)
    {
        case KEY_J:
            if (JActive)
            {
                JActive = false;
            } else {
                JActive = true;
            }
            break;
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1);
            break;
        case KEY_UP:
            rotateBlock();
            break;            
   }
}

void Game::MoveBlockLeft()
{
    if(!gameOver) { // if the game is not over
        currentBlock.Move(0, -1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if(!gameOver) { // if the game is not over
        currentBlock.Move(0, 1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if(!gameOver) { // if the game is not over
        currentBlock.Move(1, 0);
        int collisionX = currentBlock.GetCenterPositionX();
        int collisionY = currentBlock.GetCenterPositionY()+4;

        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
        if (grid.IsRowFilled(collisionY) && !active)
        {
            std::cout << "CLEARED" << collisionX << "," << collisionY;
            grid.ClearDownGrid(collisionY);
            active = true;
        }
    }
//    grid.Print();
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int movedDownPoints)
{
    switch(linesCleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
        case 3:
            score += 500;
        default:
            break;
    }

    score += movedDownPoints;
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        if(grid.IsCellOutSide(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

bool Game::IsJActive()
{
    return JActive;
}

void Game::rotateBlock()
{
    currentBlock.Rotate();
    if(IsBlockOutside())
    {
        currentBlock.UndoRotation();
    } else {
        PlaySound(rotateSound);
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if(rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        if(grid.IsCellEmpty(item.row, item.column) == false)
        {   
            return false;
        }
    }
    return true;
}

#include "grid.h"
#include <iostream>

Grid::Grid()
{
    offsetX = 11;
    offsetY = 11;
    numRows = 20;
    numCols = 10;
    cellSize = 30; // in px, size
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize() // Creates a grid (20 * 10) -> 200 cells
{
    for(int row = 0; row < numRows; row++)
    {
        for(int column = 0; column < numCols; column++)
        {
            grid[row][column] = 0;
        }
    }
}

void Grid::Print() 
{
    for(int row = 0; row < numRows; row++)
    {
        for(int column = 0; column < numCols; column++)
        {
            std::cout << grid[row][column] << " ";
        }        
        std::cout << std::endl;
    }
}

void Grid::ClearDownGrid(int row)
{
    for(int r = row; r < numRows; r++) {
        for(int column = 0; column < numCols; column++)
        {
            grid[r][column] = 0;
        }
    }
    

}

bool Grid::IsRowFilled(int row) 
{
    for(int column = 0; column < numCols; column++)
    {
        if(grid[row][column] != 0 && row < numRows)
        {
            std::cout << "row" << row;
            return true;
        }
    }
    return false;
}




std::vector<Color> Grid::GetCellColors()
{
    Color darkGrey = {26, 31, 40, 255};
    Color green = {47, 230, 23, 255};
    Color red = {232, 18, 18, 255};
    Color orange = {226, 116, 17, 255};
    Color yellow = {237, 234, 4, 255};
    Color purple = {166, 0, 247, 255};
    Color cyan = {21, 204, 209, 255};
    Color blue = {13, 64, 216, 255};

    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}

void Grid::Draw()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int column = 0; column < numCols; column++)
        {
            int cellValue = grid[row][column];
//            DrawRectangle(posX, posY, width, height, color);
            DrawRectangle(column * cellSize+offsetX, row * cellSize+offsetY, cellSize-1, cellSize-1, colors[cellValue]); // modyfied to 11 (padding + 1)
        }
    }
}

bool Grid::IsCellOutSide(int row, int column)
{
    if(row >= 0 && row < numRows && column >= 0 && column < numCols)
    {
        return false;
    }    
    return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if(grid[row][column] == 0)
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int row = numRows - 1; row >= 0; row--)
    {
        if(IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;

}

bool Grid::IsRowFull(int row)
{
    for(int column = 0; column < numCols; column++)
    {
        if(grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int column = 0; column < numCols; column++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for(int column = 0; column < numCols; column++)
    {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }

}

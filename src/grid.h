#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public: 
    Grid();
    void Initialize();
    void Print();
    std::vector<Color> GetCellColors();
    void Draw();
    bool IsCellOutSide(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    int grid[20][10]; // int array with 20 rows and 10 columns
private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};
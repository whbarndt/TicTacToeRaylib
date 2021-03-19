#pragma once
#include <tuple>
#include "raylib.h"

struct Tile
{
    // Texture data
    Vector2 origin = { 0 };
    Vector2 dimensions = { 0 };
    Color color = WHITE; //{ 255, 255, 225, 255 };
    Color tile_border = BLACK; //{ 0, 0, 0, 255 };
    Texture2D sprite = { 0 };

    char status = ' ';
};

class Board
{
public:
    // Board data
    static const int dim_of_board = 5;
    static const int size_of_tile = 100; //Pixel Coordinates
    Tile board[dim_of_board][dim_of_board];
    Vector2 boardoffset = { 700, 100 };

    Board();
    ~Board();

    void drawBoard();
    char ifWinFound();
    std::tuple<int, int> ifInARow();
    bool ifDrawFound();
};



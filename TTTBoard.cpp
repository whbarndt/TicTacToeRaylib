//Struct to store the Tile data for my Tic Tac Toe Board
#include "TTTBoard.hpp"

// Initialization of Board class
Board::Board()
{
    for (int row = 0; row < dim_of_board; row++)
    {
        for (int column = 0; column < dim_of_board; column++)
        {
            board[row][column].origin = Vector2{ (float)(size_of_tile * row), (float)(size_of_tile * column) };
            board[row][column].dimensions = Vector2{ (float)size_of_tile, (float)size_of_tile };
            board[row][column].status = ' ';
            
        }
    }
}

Board::~Board() {}

// Function for drawing the board
void Board::drawBoard() 
{
    for (int row = 0; row < dim_of_board; row++)
    {
        for (int column = 0; column < dim_of_board; column++)
        {
            DrawRectangle(board[row][column].origin.x + boardoffset.x, board[row][column].origin.y + boardoffset.y, board[row][column].dimensions.x, board[row][column].dimensions.y, board[row][column].color);
            DrawRectangleLines(board[row][column].origin.x + boardoffset.x, board[row][column].origin.y + boardoffset.y, board[row][column].dimensions.x, board[row][column].dimensions.y, board[row][column].tile_border);
            if (board[row][column].status == 'x')
                board[row][column].sprite = LoadTexture("X.png");
            if (board[row][column].status == 'o')
                board[row][column].sprite = LoadTexture("O.png");
            DrawTexture(board[row][column].sprite, board[row][column].origin.x + boardoffset.x, board[row][column].origin.y + boardoffset.y, WHITE);
        }
    }
};

//Function that returns the character (x or o) of the winner
//Only win conditions I implemented were: Horizontal, Vertical, and Diagonal 5-in-a-rows
char Board::ifWinFound()
{
    unsigned int i, j = 0;

    //Check for horizonal row win.
    for (i = 0; i < dim_of_board; i++)
    {
        for (j = 1; j < dim_of_board; j++)
        {
            if (board[i][0].status != ' ' && board[i][0].status == board[i][j].status)
            {
                if (j == 4)
                    return board[i][0].status;
            }
            else
                break;
        }
    }

    //Check for vertical column win.
    for (j = 0; j < dim_of_board; j++)
    {
        for (i = 1; i < dim_of_board; i++)
        {
            if (board[0][j].status != ' ' && board[0][j].status == board[i][j].status)
            {
                if (i == 4)
                    return board[0][j].status;
            }
            else
                break;
        }
    }

    //Check for diagonal win.
    for (i = 1; i < dim_of_board; i++)
    {
        if (board[0][0].status != ' ' && board[0][0].status == board[i][i].status)
        {
            if (i == 4)
                return board[0][0].status;
        }
        else
            break;
    }
    for (i = 1; i < dim_of_board; i++)
    {
        if (board[4][0].status != ' ' && board[4][0].status == board[4 - i][i].status)
        {
            if (i == 4)
                return board[4][0].status;
        }
        else
            break;
    }
    return ' ';
}

//Function that returns a tuple of the x's and o's that are in a row. 
//Couldn't get this working properly yet...
std::tuple<int, int> Board::ifInARow()
{
    unsigned int i, j = 0;
    std::tuple<int, int> InRow;
    int xinrow = 0;
    int oinrow = 0;

    //Check for horizontal adjacency
    for (i = 0; i < dim_of_board; i++)
    {
        int inarow = 0;
        for (j = 0; j < dim_of_board; j++)
        {
            if (board[i][j].status != ' ' && board[i][j].status == board[i][j + 1].status)
            {
                inarow++;
                if (board[i][j].status == 'x')
                {
                    if (inarow == 1)
                        xinrow++;
                    if (inarow == 2)
                        xinrow += 2;
                    if (inarow == 3)
                        xinrow += 5;
                }
                if (board[i][j].status == 'o')
                {
                    if (inarow == 1)
                        oinrow++;
                    if (inarow == 2)
                        oinrow += 2;
                    if (inarow == 3)
                        oinrow += 5;
                }
            }
        }
    }

    //Check for vertical column win.
    for (j = 0; j < dim_of_board; j++)
    {
        int inarow = 0;
        for (i = 1; i < dim_of_board; i++)
        {
            if (board[i][j].status != ' ' && board[i][j].status == board[i + 1][j].status)
            {
                inarow++;
                if (board[i][j].status == 'x')
                {
                    if (inarow == 1)
                        xinrow++;
                    if (inarow == 2)
                        xinrow += 2;
                    if (inarow == 3)
                        xinrow += 5;
                }
                if (board[i][j].status == 'o')
                {
                    if (inarow == 1)
                        oinrow++;
                    if (inarow == 2)
                        oinrow += 2;
                    if (inarow == 3)
                        oinrow += 5;
                }
            }
        }
    }

    //Check for diagonal win.
    //Starting at top left
    int inarow = 0;
    for (i = 0; i < dim_of_board; i++)
    {
        if (board[i][i].status != ' ' && board[i][i].status == board[i++][i++].status)
        {
            inarow++;
            if (board[i][i].status == 'x')
            {
                if (inarow == 1)
                    xinrow++;
                if (inarow == 2)
                    xinrow += 2;
                if (inarow == 3)
                    xinrow += 5;
            }
            if (board[i][i].status == 'o')
            {
                if (inarow == 1)
                    oinrow++;
                if (inarow == 2)
                    oinrow += 2;
                if (inarow == 3)
                    oinrow += 5;
            }
        }
    }
    // Starting at bottom right
    inarow = 0;
    for (i = 0; i < dim_of_board; i++)
    {
        if (board[4 - i][i].status != ' ' && board[4 - i][i].status == board[4 - i + 1][i + 1].status)
        {
            inarow++;
            if (board[i][i].status == 'x')
            {
                if (inarow == 1)
                    xinrow++;
                if (inarow == 2)
                    xinrow += 2;
                if (inarow == 3)
                    xinrow += 5;
            }
            if (board[i][i].status == 'o')
            {
                if (inarow == 1)
                    oinrow++;
                if (inarow == 2)
                    oinrow += 2;
                if (inarow == 3)
                    oinrow += 5;
            }
        }
    }
    InRow = std::make_tuple(xinrow, oinrow);
    return InRow;
}

//Function that returns a bool if a draw has been reached.
bool Board::ifDrawFound()
{
    for (int i = 0; i < dim_of_board; i++)
    {
        for (int j = 0; j < dim_of_board; j++)
        {
            if (board[i][j].status == ' ')
                return false;
        }
    }
    return true;
}
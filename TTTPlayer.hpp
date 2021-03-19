#pragma once
#include "TTTBoard.hpp"
#include <chrono>

//Class that holds important Player data (Used for Human and AI)
class Player
{
public:
    //Struct to store AI move (used for both Minimax and Random)
    struct AiMove
    {
        int row = 0;
        int column = 0;
        int score = 0;

        AiMove() {};
        // Used for MiniMax
        AiMove(int _row, int _column, int _score) : row(_row), column(_column), score(_score) {};
        // Used for MonteCarlo
        AiMove(int _row, int _column) : row(_row), column(_column) {};
    };
    
    // Representing ones character
    char character = ' ';
    // Minimax variable, used for alternating
    bool maximizingplayer = false;
    // AIflag variable, was going to be used more but now just used for the getAIPlayer function
    bool AIflag = false;

    Player();
    Player(char _character, bool _AIflag);

    //Minimax Functions
    int Eval(Board board);
    AiMove Minimax(Board board, int depth, int prevrow, int prevcolumn, unsigned int* boardssearch);

    //Function that returns a Random Move for the AI
    AiMove RandomBotMove(Tile TTTB[5][5]);
};
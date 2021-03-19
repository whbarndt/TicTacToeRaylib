#include "TTTPlayer.hpp"

Player::Player() {};

Player::Player(char _character, bool _AIflag) : character(_character), AIflag(_AIflag) {};

//My evaluation function. Not the best eval function but it technically works.
//All it does is checks for wins and for characters that are in a row.
int Player::Eval(Board board)
{
    int board_eval = 0;
    char otherplayer = (character == 'x') ? ('o') : ('x');
    if (board.ifWinFound() == character)
        board_eval += 15;
    else if (board.ifWinFound() == otherplayer)
        board_eval += -15;
    else if (board.ifDrawFound())
        return 0;
    if (character == 'x')
    {
        board_eval += std::get<0>(board.ifInARow());
        board_eval -= std::get<1>(board.ifInARow());
    }
    else
    {
        board_eval -= std::get<0>(board.ifInARow());
        board_eval += std::get<1>(board.ifInARow());
    }
    return board_eval;
}

//My Minimax function.
Player::AiMove Player::Minimax(Board board, int depth, int prevrow, int prevcolumn, unsigned int* boardssearch)
{
    //Base Case
    if (depth == 0 || board.ifWinFound() == true || board.ifDrawFound() == true)
        return AiMove(prevrow, prevcolumn, Eval(board));

    if (maximizingplayer == true)
    {
        AiMove maxEval(prevrow, prevcolumn, -99999);
        //Perform Temp move, then pass Board
        for (int row = 0; row < board.dim_of_board; row++)
        {
            for (int column = 0; column < board.dim_of_board; column++)
            {
                if (board.board[row][column].status == ' ')
                {
                    Board temp_board;
                    std::copy(&board.board[0][0], &board.board[0][0] + board.dim_of_board * board.dim_of_board, &temp_board.board[0][0]);
                    temp_board.board[row][column].status = character;
                    maximizingplayer = false;
                    *boardssearch += 1;
                    AiMove move = Minimax(temp_board, depth - 1, row, column, boardssearch);
                    if (move.score > maxEval.score)
                    {
                        maxEval.row = row;
                        maxEval.column = column;
                        maxEval.score = move.score;
                    }
                    else 
                        continue;
                }
            }
        }
        return maxEval;
    }
    else
    {
        AiMove minEval(prevrow, prevcolumn, 99999);
        //Perform Temp move, then pass Board
        for (int row = 0; row < board.dim_of_board; row++)
        {
            for (int column = 0; column < board.dim_of_board; column++)
            {
                if (board.board[row][column].status == ' ')
                {
                    Board temp_board;
                    std::copy(&board.board[0][0], &board.board[0][0] + board.dim_of_board * board.dim_of_board, &temp_board.board[0][0]);
                    temp_board.board[row][column].status = (character == 'x') ? ('o') : ('x');
                    maximizingplayer = true;
                    *boardssearch += 1;
                    AiMove move = Minimax(temp_board, depth - 1, row, column, boardssearch);
                    if (move.score < minEval.score)
                    {
                        minEval.row = row;
                        minEval.column = column;
                        minEval.score = move.score;
                    }
                    else
                        continue;
                }
            }
        }
        return minEval;
    }
};

//Function that returns a Random Move for the AI
Player::AiMove Player::RandomBotMove(Tile TTTB[5][5])
{
    while (true)
    {
        unsigned int i = rand() % 5;
        unsigned int j = rand() % 5;

        if (TTTB[i][j].status == ' ')
            return AiMove(i, j, 999);
        else
            DrawText("Bot made invalid move: retrying", 500, 300, 14, BLACK);
    }
};

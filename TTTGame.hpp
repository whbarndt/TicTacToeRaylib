#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <tuple>
#include <algorithm>

#include "TTTBoard.hpp"
#include "TTTRender.hpp"
#include "TTTPlayer.hpp"
#include "TTTTime.hpp"
#include "TTTInput.hpp"
#include "TTTMCTS.hpp"

//Class that holds most of the important game data.
//Should've connected many of my functions down below to this class but just didn't feel like I had time.
class Game
{
public:
    //Game State Variables
    Player* current_player = nullptr;
    unsigned int total_turns = 0;
    bool winfound = false;
    Player* winner = nullptr;
    // Input
    char game_type = ' ';
    char pick_player_turn = '0';
    std::string board_pos;
    // Saved Game
    std::vector<std::string> gamesave;
    // AI Boards Searched
    unsigned int boardssearched = 0;
    // Window Manager
    char menu = 'm'; //'m' for main menu and 'g' for main game loop

    // Instantiated Player Objects
    Player *player1;
    Player *player2;

    Board *board;
    Window *window;
    Time *time;
    Input *input;

    // Initialization of MCTS AI
    MCTS MCTS;

    Player* getHumanPlayer()
    {
        if (player1->AIflag == false)
            return player1;
        else if (player2->AIflag == false)
            return player2;
        else
            return nullptr;
    }
    Player* getAIPlayer()
    {
        if (player1->AIflag == false)
            return player2;
        else
            return player1;
    }

    Game();
    ~Game();
    
    void MainMenu();
    void MainGameState();

    // My replay game functions
    void SaveMove(Player player, unsigned int row, unsigned int column);
    void SaveGame();

};
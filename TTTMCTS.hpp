#pragma once
#include "TTTPlayer.hpp"
#include "TTTMCTSNode.hpp"
#include <chrono>
#include <algorithm>

class MCTS
{
public:
    MCTSNode rootNode;
    const unsigned int max_iter = 500;
    const double max_time = 5.0;
    
    int boardspersec = 0;

    char nextNodeChar(char player);
    char Rollout(MCTSNode* next_node);
    void updateNodes(MCTSNode* node, char winner);

    MCTSNode* selection();
    MCTSNode* expansion(MCTSNode* node);
    char simulation(MCTSNode* node);
    void backpropogation(MCTSNode* node, char winner);
    Player::AiMove findNextMove(Board _board, char _player_char, unsigned int &boardssearched);

    MCTS();
    ~MCTS();
};


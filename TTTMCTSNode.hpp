#pragma once
#include <vector>
#include <math.h>

#include "TTTPlayer.hpp"
#include "TTTBoard.hpp"

class MCTSNode
{
public:
    Player::AiMove move{999,999};
    Board boardstate;
    char player_char;

    MCTSNode* parent = nullptr;
    std::vector<MCTSNode*> children;
    std::vector<Player::AiMove> availablemoves;

    int node_visits = 0;
    int wins = 0;

    float calcUCT();
    void setAvailableMoves();
    bool isFullyExpanded();
    MCTSNode* getBestChildChoice();
    MCTSNode* getChildWithBestScore();
    
    
    void update(char player);

    MCTSNode();
    MCTSNode(Board _boardstate, char _nodes_player);
    MCTSNode(Board _boardstate, char _nodes_player, Player::AiMove _move, MCTSNode* _parent);
    ~MCTSNode();
};



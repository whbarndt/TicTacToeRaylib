#include "TTTMCTSNode.hpp"

MCTSNode::MCTSNode() {  };

MCTSNode::MCTSNode(Board _boardstate, char _nodes_player) : boardstate(_boardstate), player_char(_nodes_player) { this->setAvailableMoves(); };

MCTSNode::MCTSNode(Board _boardstate, char _nodes_player, Player::AiMove _move, MCTSNode* _parent)
{
	this->boardstate = _boardstate;
	this->parent = _parent;
	this->move = _move;
	this->boardstate.board[_move.row][_move.column].status = _nodes_player;
	this->player_char = _nodes_player;
	this->setAvailableMoves();
};

MCTSNode::~MCTSNode() {};

// Function that calculates the UCT
float MCTSNode::calcUCT()
{
	if (this->node_visits == 0)
		return 0.0;

	return this->wins / (float)this->node_visits + 1.44 * sqrt(log((this->parent == nullptr) ? 0 : this->parent->node_visits) / this->node_visits);
};

// Function that returns a vector containing all available moves with respect to current board
void MCTSNode::setAvailableMoves()
{
	// Possible States
    for (unsigned int row = 0; row < this->boardstate.dim_of_board; row++)
    {
        for (unsigned int column = 0; column < this->boardstate.dim_of_board; column++)
        {
            if (this->boardstate.board[row][column].status == ' ')
            {
				this->availablemoves.push_back(Player::AiMove(row,column));
			}
		}
	}
};

// Checks if the current node is fully expanded
bool MCTSNode::isFullyExpanded()
{
	return this->availablemoves.size() == this->children.size();
}

// Function that returns the best child based upon nodes' UCT
MCTSNode* MCTSNode::getBestChildChoice()
{
	MCTSNode* bestchild = this;
	int current_best = this->calcUCT();

	for(MCTSNode* child : this->children)
		if(child->calcUCT() > current_best)
		{
			current_best = child->calcUCT();
			bestchild = child;
		}

	return bestchild;
};

// Function that returns the child with the best score (node visits)
MCTSNode* MCTSNode::getChildWithBestScore()
{
	MCTSNode* bestchild = nullptr;
	int current_best = 0;

	for(MCTSNode* child : this->children)
		if(child->node_visits > current_best)
		{
			current_best = child->node_visits;
			bestchild = child;
		}

	return bestchild;
};
#include "TTTMCTS.hpp"

MCTS::MCTS() {};

MCTS::~MCTS() {};

// Changes next nodes char based on current char
char MCTS::nextNodeChar(char player)
{
    if (player == 'x')
        return 'o';
    else if (player == 'o')
        return 'x';
    else 
        return ' ';
}

// Selection function; Loops through each child of the root and returns the one with the greatest UCT
MCTSNode* MCTS::selection()
{
    MCTSNode* current_node = &rootNode;
    while (!current_node->children.size() == 0) 
    {
        current_node = current_node->getBestChildChoice();
        if(current_node == current_node->getBestChildChoice())
            break;
    }
    return current_node;
};

// Expansion function; Expands based off of selected node
MCTSNode* MCTS::expansion(MCTSNode* node)
{
    // Returns node if it's an end game node
    if (node->children.size() >= node->availablemoves.size())
		return node; 

    // Switches the player_char to the next turns char
    char next_node_char = nextNodeChar(node->player_char);

    // Creates a new random child, adds it to the current nodes children, then returns the newly added child
    MCTSNode* newchild = new MCTSNode(node->boardstate, next_node_char, node->availablemoves[rand() % node->availablemoves.size()], node);
	node->children.push_back(newchild);
	return node->children.back();
};

// My Rollout function that returns the char 
char MCTS::Rollout(MCTSNode* node)
{
	if (node->boardstate.ifWinFound() != ' ')
		return node->boardstate.ifWinFound();
	if (node->boardstate.ifDrawFound())
		return 'd';

    // Creates a temp_node for rolled out game
    MCTSNode temp_node{node->boardstate, node->player_char};
    char current_char = node->player_char;

	for (unsigned int i = 0; i < node->availablemoves.size(); i++)
	{        
        // Picks a random move and places it on the board
        int randommoveindex = rand() % temp_node.availablemoves.size();
        Player::AiMove randommove = temp_node.availablemoves[randommoveindex];
        temp_node.boardstate.board[randommove.row][randommove.column].status = current_char;

        // Resets the temp_nodes available moves
        temp_node.availablemoves.clear();
        temp_node.setAvailableMoves();

        current_char = nextNodeChar(current_char);

		if (temp_node.boardstate.ifWinFound() != ' ')
			break;
        if (temp_node.boardstate.ifDrawFound())
		    return 'd';
	}

	return temp_node.boardstate.ifWinFound();
}

// My simulation function
char MCTS::simulation(MCTSNode* node)
{
    if (node->boardstate.ifWinFound() != ' ')
		return node->boardstate.ifWinFound();
    if (node->boardstate.ifDrawFound())
		return 'd';

	return Rollout(node);
};

// My update node function
void MCTS::updateNodes(MCTSNode* node, char winner)
{
	node->node_visits += 10;

	if (winner == node->player_char) // Or in this context, the previous node
		node->wins += 10;

	else if (winner == 'd')
		node->wins += 5;

}

// My backpropogation function, loops up to the parent and updates the nodes on the way
void MCTS::backpropogation(MCTSNode* node, char winner)
{
    MCTSNode* currentNode = node;

	while (currentNode != nullptr)
	{
		updateNodes(currentNode, winner);
		currentNode = currentNode->parent;
	}
};

// Function to find next AI move 
Player::AiMove MCTS::findNextMove(Board _board, char _player_char, unsigned int &boardssearched) 
{
     // Copying given board and player_char to root node
    std::copy(&_board.board[0][0], &_board.board[0][0] + _board.dim_of_board * _board.dim_of_board, &rootNode.boardstate.board[0][0]);
    rootNode.player_char = _player_char;
    rootNode.availablemoves.clear();
    rootNode.children.clear();
    rootNode.setAvailableMoves();
    
    // Start of timer and max interations
    double start = GetTime();
    double end = 0.0;
    double time_span = 0.0;
    unsigned int iter = 0;

    //Loops to find next best move
    while (time_span < max_time || iter == max_iter) // 15 Seconds
    {
        // Selection
        MCTSNode* bestNode = selection();
        // Expansion
        MCTSNode* expanded_node = expansion(bestNode);
        // Simulation
        char winner = simulation(expanded_node);
        // Update
        backpropogation(expanded_node, winner);

        // Used for timing
        end = GetTime();
		time_span = end - start;
        iter++;
        boardssearched++;
        if(iter == max_iter)
            boardspersec = boardssearched/end;        
    }
    boardspersec = boardssearched/end;
    // Get child move with most visits
    Player::AiMove bestmove; 
    bestmove.row = rootNode.getChildWithBestScore()->move.row;
    bestmove.column = rootNode.getChildWithBestScore()->move.column;

    return bestmove;
};


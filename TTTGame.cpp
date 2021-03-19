#include "TTTGame.hpp"

Game::Game()
{
	player1 = new Player();
	player2 = new Player();
	
	player1->character = 'x';
	player2->character = 'o';

	current_player = player1;

	board = new Board();
	window = new Window();
	time = new Time();
	input = new Input();
};

Game::~Game() 
{
	delete player1;
	delete player2;
	delete board;
	delete window;
	delete time;
	delete input;
}

// Main Menu
void Game::MainMenu()
{
	if (game_type == ' ') // Nothing has been selected yet
	{
		DrawText("Welcome to Tic Tac Toe 5 in a Row!", 500, 200, 14, BLACK);
		DrawText("What would you like to do?", 500, 250, 14, BLACK);
		DrawText("Type '1' to Play vs a Bot", 500, 300, 14, BLACK);
		DrawText("Type '2' to Watch Two Bots Play each other", 500, 350, 14, BLACK);
		DrawText("Type '3' to Playback a previous game using a logged file", 500, 400, 14, BLACK);

		input->DrawTextBox();

		// Checks if the Enter key has been pressed
		if(IsKeyPressed(KEY_ENTER))
		{
			game_type = input->tb.choice[0];
			strcpy(input->tb.choice,"\0");
		}
	}

	// HUMAN VS AI GAME
	if (game_type == '1')
	{
		DrawText("Who's Going First? (Type '1' for Human; '2' for Bot):", 500, 300, 14, BLACK);
		input->DrawTextBox();
		
		// Checks if the Enter key has been pressed
		if(IsKeyPressed(KEY_ENTER))
		{
			pick_player_turn = input->tb.choice[0];
			strcpy(input->tb.choice,"\0");
		}

		// Initializes the players turns
		if (pick_player_turn == '1' || pick_player_turn == '2')
		{
			if (pick_player_turn == '1')
			{
				player1->AIflag = false;
				player2->AIflag = true;
				player2->maximizingplayer = true;
				menu = 'g';
			}
			else
			{
				player1->AIflag = true;
				player1->maximizingplayer = true;
				player2->AIflag = false;
				menu = 'g';
			}
		}
		else
			DrawText("ERROR: Please type in valid choice", 550, 100, 14, BLACK);
	}
	
	// AI VS AI GAME
	else if (game_type == '2')
	{
		player1->AIflag = true;
		player1->maximizingplayer = true;
		player2->AIflag = true;
		player2->maximizingplayer = true;

		menu = 'g';
	}

	// WATCH A REPLAY OF A PREVIOUS GAME USING A LOG FILE
	else if (game_type == '3')
	{
		DrawText("Sorry, this didn't get implemented fully...", 500, 250, 14, BLACK);
		DrawText("Please exit out of the application", 500, 300, 14, BLACK);

		//menu = 'g';
	}
}

//My main game loop function:
void Game::MainGameState()
{
	////////////////////////////////////////////////////////////////////////////////////
	// Main Game Loop //////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	// HUMAN VS AI GAME //////////////////////////////////////////////

	if (game_type == '1')
	{
		//Draw Board
		board->drawBoard();
		
		if (current_player == getHumanPlayer())
		{
			// Init for tile choices
			char board_pos[2];
			int row = 0;
			int column = 0;
			
			input->tb.textBox.x = 50;
			input->tb.textBox.y = 500;

			// Game Dialogue
			DrawText("It is the Human's turn", 50, 200, 12, BLACK);
			DrawText("Please choose where you would like place", 50, 250, 12, BLACK);
			DrawText("Format:('12'); where the first number is the column and the second number is the row", 50, 300, 12, BLACK);
			DrawText("Numbers range from (1) to (size of board) on both axis (top right is the origin)", 50, 350, 12, BLACK);

			input->DrawTextBox();
			
			DrawText("Previous Player's Boards Searched: ", 50, 400, 14, BLACK);
			DrawText(std::to_string(boardssearched).c_str(), 325, 400, 14, BLACK);

			DrawText("Previous Player's Boards/Sec: ", 50, 450, 14, BLACK);
			DrawText(std::to_string(MCTS.boardspersec).c_str(), 325, 450, 14, BLACK);

			// Checks if the Enter key has been pressed
			if(IsKeyPressed(KEY_ENTER))
			{
				strcpy(board_pos, input->tb.choice);
				strcpy(input->tb.choice,"\0");

				row = board_pos[0] - '0';
				column = board_pos[1] - '0';

				if (row >= 1 && row <= 5 && column >= 1 && column <= 5)
				{
					if (board->board[row - 1][column - 1].status == ' ')
					{
						board->board[row - 1][column - 1].status = getHumanPlayer()->character;
						current_player = getAIPlayer();
					}
					else
						DrawText("ERROR: Please choose an empty tile", 50, 600, 14, BLACK);
				}
				else
				{
					DrawText("ERROR: Please choose a place within the boundaries", 50, 600, 14, BLACK);
				}				
				board->drawBoard();
				//SaveMove(row, column);
			}	
		}
		else
		{
			board->drawBoard();
			DrawText("It is the Bot's turn", 500, 200, 14, BLACK);

			boardssearched = 0;
			MCTS.boardspersec = 0;

			// Using MCTS as the bot: ///////////////////////////////////////////////////////////////////////////
			Player::AiMove hopefully_good_move = MCTS.findNextMove(*board, player1->character, boardssearched);
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			
			// Using Minimax as the bot: ///////////////////////////////////////////////////////////////////////
			//unsigned int start = GetTime();
			//Player::AiMove decent_move = player1->Minimax(*board, 5, 2, 2, &boardssearched);
			//unsigned int end = GetTime();
			//unsigned int time_lapse = start - end;

			//DrawText("Boards Searched: ", 50, 250, 14, BLACK); 
			//DrawText(std::to_string(boardssearched).c_str(), 200, 250, 14, BLACK);
			//boardssearched = 0;

			//DrawText("Previous Player's Boards/Sec: ", 50, 450, 14, BLACK);
			//DrawText(std::to_string(boardssearched/time_lapse).c_str(), 325, 450, 14, BLACK);
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			
			// Using Random moves as the bot:
			//Player::AiMove rand_bot_move = RandomBotMove(game.TicTacToeBoard);
			
			//board->board[decent_move.row][decent_move.column].status = getAIPlayer()->character;
			board->board[hopefully_good_move.row][hopefully_good_move.column].status = getAIPlayer()->character;
			
			//SaveMove(rand_bot_move.row, rand_bot_move.column);
			current_player = getHumanPlayer();
		}
	}

	// AI VS AI GAME //////////////////////////////////////////////

	else if (game_type == '2')
	{
		//Draw Board
		board->drawBoard();
		if (current_player == player1)
		{
			DrawText("It is Player 1's turn", 50, 200, 14, BLACK);

			// Using MCTS as the bot: ///////////////////////////////////////////////////////////////////////
			// Text to display previous players board statistics
			DrawText("Previous Player's Boards Searched: ", 50, 400, 14, BLACK);
			DrawText(std::to_string(boardssearched).c_str(), 325, 400, 14, BLACK);

			DrawText("Previous Player's Boards/Sec: ", 50, 450, 14, BLACK);
			DrawText(std::to_string(MCTS.boardspersec).c_str(), 325, 450, 14, BLACK);

			// Resets the stats for next call
			boardssearched = 0;
			MCTS.boardspersec = 0;
			
			Player::AiMove hopefully_good_move = MCTS.findNextMove(*board, player1->character, boardssearched);
			/////////////////////////////////////////////////////////////////////////////////////////////////////

			// Using Minimax as the bot: ///////////////////////////////////////////////////////////////////////
			//unsigned int start = GetTime();
			//Player::AiMove decent_move = player1->Minimax(*board, 5, 2, 2, &boardssearched);
			//unsigned int end = GetTime();
			//unsigned int time_lapse = start - end;

			//DrawText("Boards Searched: ", 50, 250, 14, BLACK); 
			//DrawText(std::to_string(boardssearched).c_str(), 200, 250, 14, BLACK);
			//boardssearched = 0;

			//DrawText("Previous Player's Boards/Sec: ", 50, 450, 14, BLACK);
			//DrawText(std::to_string(boardssearched/time_lapse).c_str(), 325, 450, 14, BLACK);
			/////////////////////////////////////////////////////////////////////////////////////////////////////

			// Using Random moves as the bot:
			//Player::AiMove rand_bot_move = RandomBotMove(game.TicTacToeBoard);
			
			
			board->board[hopefully_good_move.row][hopefully_good_move.column].status = 'x';
			//board->board[decent_move.row][decent_move.column].status = 'x';
			//board->board[rand_bot_move.row][rand_bot_move.column].status = 'x';

			current_player = player2;
			
			//Player::Player tempplayer('x');
			//SaveMove(tempplayer, rand_bot_move.row, rand_bot_move.column);
		}
		else
		{
			DrawText("It is Player 2's turn", 50, 200, 14, BLACK);

			// Using MCTS as the bot: ///////////////////////////////////////////////////////////////////////
			// Text to display previous players board statistics
			//DrawText("Previous Player's Boards Searched: ", 50, 400, 14, BLACK);
			//DrawText(std::to_string(boardssearched).c_str(), 325, 400, 14, BLACK);

			//DrawText("Previous Player's Boards/Sec: ", 50, 450, 14, BLACK);
			//DrawText(std::to_string(MCTS.boardspersec).c_str(), 325, 450, 14, BLACK);

			// Resets the stats for next call
			//boardssearched = 0;
			//MCTS.boardspersec = 0;
			
			//Player::AiMove hopefully_good_move = MCTS.findNextMove(*board, player2->character, boardssearched);
			/////////////////////////////////////////////////////////////////////////////////////////////////////

			// Using Minimax as the bot: ///////////////////////////////////////////////////////////////////////
			unsigned int start = GetTime();
			Player::AiMove decent_move = player2->Minimax(*board, 5, 2, 2, &boardssearched);
			unsigned int end = GetTime();
			unsigned int time_lapse = start - end;

			DrawText("Boards Searched: ", 50, 250, 14, BLACK); 
			DrawText(std::to_string(boardssearched).c_str(), 200, 250, 14, BLACK);
			boardssearched = 0;

			DrawText("Previous Player's Boards/Sec: ", 50, 450, 14, BLACK);
			//DrawText(std::to_string(boardssearched/time_lapse).c_str(), 325, 450, 14, BLACK);
			/////////////////////////////////////////////////////////////////////////////////////////////////////

			// Using Random moves as the bot:
			//Player::AiMove rand_bot_move = RandomBotMove(game.TicTacToeBoard);
			
			
			//board->board[hopefully_good_move.row][hopefully_good_move.column].status = 'o';
			board->board[decent_move.row][decent_move.column].status = 'o';
			//board->board[rand_bot_move.row][rand_bot_move.column].status = 'o';

			current_player = player1;
			
			//Player::Player tempplayer('o');
			//SaveMove(tempplayer, rand_bot_move.row, rand_bot_move.column);
		}
	}

	//WATCH A REPLAY OF A PREVIOUS GAME USING A LOG FILE

	else if (game_type == '3')
	{
		//Draw Board
		board->drawBoard();
		std::string line;
		//std::ifstream myfile;
		DrawText("Please input the file of the game you would like to playback.", 50, 200, 14, BLACK);
		
		/*std::string input_file;
		// INPUT
		myfile.open(input_file);
		if (myfile.good())
			break;
		else
			DrawText("Invalid File. Please Try Again", 500, 250, 14, BLACK);
		//REPLAY PAST GAME USING LOG
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				std::cout << line << '\n';
			}
			myfile.close();
		}
		else
			std::cout << "Unable to open file";
		*/
	}
	else
		DrawText("Please select a valid option", 50, 200, 14, BLACK);

	total_turns++;

	// Checks for winner
	if (board->ifWinFound() != ' ')
	{
		if (board->ifWinFound() == player1->character)
			winner = &*player1;
		else
			winner = &*player2;
		winfound = true;
	}
	// Checks for draw found
	if (board->ifDrawFound() == true)
	{
		board->drawBoard();
		DrawText("The game ended in a tie!", 50, 400, 14, BLACK);
		DrawText("Thanks for playing!", 50, 450, 14, BLACK);
		DrawText("Please exit application to start another game", 50, 500, 14, BLACK);
		game_type = 'f';
	}
	// Tells winner and ends game
	if (winfound)
	{
		board->drawBoard();
		std::string winnertitle = (winner->AIflag == false) ? ("Human!") : ("Bot...");
		DrawText("And the winner is the ", 50, 400, 14, BLACK);
		DrawText("Please exit application to start another game", 50, 450, 14, BLACK);
		game_type = 'f';
	}
}

//Function that combines the players character and their moves to a single string (which will be used in the replay feature that I didn't get to create)
//Then will append three dashes to the string to use as a delimeter for the replay function.
//After the dashes, there will be the log in plain text that people can read back.
void Game::SaveMove(Player player, unsigned int row, unsigned int column)
{
    std::string ccharacter = std::to_string(player.character);
    std::string crow = std::to_string(row);
    std::string ccolumn = std::to_string(column);
    std::string tempstring;
    tempstring.append(crow);
    tempstring.append(ccolumn);
    tempstring.append("---");
    tempstring.append(ccharacter);
    tempstring.append(" played on row ");
    tempstring.append(crow);
    tempstring.append(" and on column ");
    tempstring.append(ccolumn);
    gamesave.push_back(tempstring);
}

//My save game function. Not fully implemented yet...
//Will loop through the vector of moves I made and save them to a file
void Game::SaveGame()
{
    while (true)
    {
        std::cout << "Would you like to save this game?" << std::endl;
        std::cout << "Type '1' for Yes or '2' for No" << std::endl;
        char save_game;
        std::cin >> save_game;
        if (save_game == '1' || save_game == '2')
        {
            if (save_game == '1')
            {

            }
            else
            {

            }
            break;
        }
        else
            std::cout << "ERROR: Please select a valid option" << std::endl;
    }
}
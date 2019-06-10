#include "GameManager.h"


void GameManager::simulateGame() {
	int playerTurn = 0;

	while (!gameOver) {
		agent->makeDecision(players[playerTurn]->rack, boardManager, scoreManager, tileLookup);

		// FIXME: remove comment when move class is added and integrated
		// players[playerTurn]->playerScore += scoreManager->computeMoveScore(move);


		// Increment turn with wrap around
		playerTurn = (playerTurn + 1) % playerCount;
	}
}

GameManager::GameManager(TileLookUp* tileLookUp, int playerCount, string playerNames[])
{
	cout << "Game Manager Initialising Components..." << endl;
	// Capture the parameters
	this->tileLookup = tileLookUp;
	this->playerCount = playerCount;
	this->gameOver = false;
	// Initialise the board, score manager and AI
	cout << "Initialising Board, Score Manager and Agent..." << endl;
	boardManager = new Board();
	scoreManager = new ScoreManager(boardManager, tileLookUp);
	agent = new AI();

	// Allocate a space for every player
	cout << "Initialising Players..." << endl;
	players = new Player*[playerCount];

	// Initialise players with names
	for (int i = 0; i < playerCount; i++)
		players[i] = new Player(playerNames[i]);

	cout << "Initialisation Complete. Game starting..." << endl;
}


GameManager::~GameManager()
{
	delete boardManager;
	for (int i = 0; i < playerCount; i++)
		delete players[i];
	delete players;
}

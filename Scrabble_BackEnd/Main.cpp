//#include <iostream>
//#include "GameManager.h"
//#include "Logger.h"
//using namespace std;
//
//int main()
//{
//	string * playerNames;
//	int playerCount = 2;
//
//	cout << " Welcome to Scrabby-Doo " << endl;
//	playerNames = new string[playerCount];
//	playerNames[0] = "Player";
//	playerNames[1] = "Enemy";
//
//	Player ** players = new Player*[playerCount];
//
//	for (int i = 0; i < playerCount; i++) {
//		players[i] = new Player(playerNames[i]);
//	}
//	/*
//	Rack* r = new Rack();
//	r->addTile('A');
//	r->addTile('N');
//	r->addTile('B');
//	r->addTile('S');
//	r->addTile('D');
//	r->addTile('E');
//	r->addTile('F');
//	char c[] = { 'G','Z','Y','X' };
//	ProbabilityManager * Pm = new ProbabilityManager();
//	Board *B = new Board();
//	Move* M = new Move();
//	Play *P = new Play();
//	P->set_Coordinates(make_pair(2, 3));
//	P->set_Letter('A', 1);
//	M->addPlay(*P);
//	B->commitMove(*M);
//	P->set_Coordinates(make_pair(4,5));
//	P->set_Letter('Z', 2);
//	Move* z = new Move();
//	z->addPlay(*P);
//	Board V = Board::commitMoveSim(*z, *B);
//	/*Square list[15][15];
//	list[7][4].letter = 'L';
//	list[7][5].letter = 'A';
//	list[7][7].letter = 'C';
//	list[7][8].letter = 'I';
//	list[7][9].letter = 'S';
//	list[7][10].letter = 'E';
//	//Rack  *rack = new Rack();
//	//rack->addTile('I');
//	//ProbabilityManager * Pm = new ProbabilityManager();*/
//	int  selectedMoveIndex;
//
//	cout << "Initialising TileLookup...";
//	TileLookUp * TL = new TileLookUp();
//	cout << "Done" << endl;
//
//
//	cout << "Building GADDAG..." << endl;
//	Gaddag *g = new Gaddag("../Text/SOWPODS.txt");
//	cout << "Done" << endl;
//
//	PreEndGameManager * preEndMan = new PreEndGameManager(TL, g);
//	ProbabilityManager * PM = new ProbabilityManager();
//
//
//	cout << "Initialising Board and Bag..." << endl;
//	Board * b = new Board();
//	//b->computeCrossSets(g->root);
//	BagOfLetters * bag = new BagOfLetters();
//	cout << "Done" << endl;
//
//
//	cout << "Distributing Racks..." << endl;
//
//
//	for (int i = 0; i < playerCount; i++) {
//		players[i]->rack = new Rack();
//		//players[i]->rack->addTile('[');
//		while (players[i]->rack->list.size() < RACK_SIZE) {
//			players[i]->rack->addTile(bag->draw());
//		}
//	}
//	cout << "Done" << endl;
//	MidGameManager * midMan = new MidGameManager(TL, g);
//	Logger logger;
//	
//	int turn = 0;
//	while (1) {
//		logger.DisplayRack(players[1]->rack);
//		logger.DisplayBoard(b);
//		logger.DisplayRack(players[0]->rack);
//		int playerTurn = turn % playerCount;
//		vector <Move> MoveList;
//		g->findWords(players[playerTurn]->rack->getRackTiles(), MoveList, b);
//		if (MoveList.size() == 0) {
//			turn++;
//			continue;
//		}
//		if (bag->getSize() > 7 || !bag->hasLetters()) {
//			 selectedMoveIndex = midMan->getBestMove(MoveList, players[playerTurn]->rack, b);
//		}
//		else {
//			cout << " PreEnd" << endl;
//			selectedMoveIndex = preEndMan->Blocking(&MoveList, players[playerTurn]->rack, b, PM);
//		}
//		
//		cout << "Move Chosen: ";
//		logger.PrintMove(&MoveList[selectedMoveIndex]);
//		playMove moveStruct;
//		b->formatMyMove(MoveList[selectedMoveIndex], moveStruct);
//		logger.PrintMoveStruct(moveStruct);
//		b->commitMove(MoveList[selectedMoveIndex]);
//		b->computeCrossSets(g->root);
//		players[playerTurn]->rack->commitMove(&MoveList[selectedMoveIndex]);
//		while (players[playerTurn]->rack->list.size() < RACK_SIZE) {
//			if (!bag->hasLetters())break;
//			players[playerTurn]->rack->addTile(bag->draw());
//		}
//
//		system("pause");
//		turn++;
//	}
//
///*	//	cout << (M->Plays.begin())->Letter << endl;
//
//	//	MonteCarlo * M = new MonteCarlo(r,c,Pm);
//	// M->simulation(100);
//
//	//	 Utilities * u =new  Utilities();
//
//	Intiating  instance tileLookUp from TileLookUp class
//
//	//TileLookUp * tileLookUp = new TileLookUp();
//	//GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
//	//gameManager->simulateGame();
//	cout << "finished" << endl;*/
//		system("pause");
//		return 0;
//	}

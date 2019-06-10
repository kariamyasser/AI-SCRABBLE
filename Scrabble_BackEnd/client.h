#pragma once
#include <stdio.h>
#include "easywsclient.h"
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <assert.h>
#include <string>
#include "enums.h"
#include"structs.h"
#include <iostream>
#include <string>
#include <memory>
using easywsclient::WebSocket;
using namespace std;
class Client
{
private:
	States state;

	vector<uint8_t> encodeInitState(string name);
	vector<uint8_t> encodeTiles(vector<char>v);

public:
	Client();
	void setState(States s);
	States getState();


	void sendInitState(shared_ptr<WebSocket> ws, string name);
	void sendPass(shared_ptr<WebSocket> ws);
	void sendExchange(shared_ptr<WebSocket> ws, vector<char> tiles);
	void sendPlay(shared_ptr<WebSocket> ws, playMove play);
	void sendNoChallenge(shared_ptr<WebSocket> ws);
	void sendChallenge(shared_ptr<WebSocket> ws);
	readyStruct_formated decodeReadyState(std::vector<uint8_t>& message);
	fromatedTime decodeTime(std::vector<uint8_t>& message);
	vector<char>decodeTiles(std::vector<uint8_t>& message);
	void decodeChallengeRejected(std::vector<uint8_t>& message, vector<char>&tiles, uTime&time);
	void decodeIdleExchange(std::vector<uint8_t>& message, int &count, uTime&time);
	endMove decodeEndGame(std::vector<uint8_t>& message);
	player2Move_formated decodePlay(std::vector<uint8_t>& message);
	~Client();
};


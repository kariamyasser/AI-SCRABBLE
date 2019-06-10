#include "Client.h"
#include"functions.h"
#include <intrin.h>

Client::Client()
{
	state = States::INIT;
}
void Client::setState(States s)
{
	this->state = s;
}
States Client::getState()
{
	return this->state;
}

vector<uint8_t> Client::encodeInitState(string name)
{
	vector<uint8_t> playerName;
	playerName.clear();
	playerName.push_back(MessageTypes::NAME);
	playerName.resize(name.length() + 1);
	memcpy(playerName.data() + 1, name.data(), name.length());
	return playerName;
}
vector<uint8_t> Client::encodeTiles(vector<char>v)
{
	vector<int>result = convertToNumbers(v);
	vector<uint8_t> tiles(result.begin(), result.end());
	return tiles;
}

void Client::sendInitState(shared_ptr<WebSocket> ws, string name)
{
	ws->sendBinary(encodeInitState(name));
}
readyStruct_formated Client::decodeReadyState(std::vector<uint8_t>& message)
{
	readyStruct ready;
	readyStruct_formated ready_formated;
	unsigned int bufferOffset = 0;

	memcpy(&ready.type, message.data() + bufferOffset, sizeof(ready.type));
	bufferOffset += sizeof(ready.type);
	ready_formated.type = int(ready.type);
	cout << "type: " << int(ready.type) << endl;

	memcpy(&ready.order, message.data() + bufferOffset, sizeof(ready.order));
	bufferOffset += sizeof(ready.order);
	ready_formated.order = int(ready.order);
	cout << "Order: " << int(ready.order) << endl;

	ready.tiles.resize(7);
	memcpy(ready.tiles.data(), message.data() + bufferOffset, 7);
	bufferOffset += ready.tiles.size();
	vector<int> v(ready.tiles.begin(), ready.tiles.end());
	ready_formated.tiles = convertToletters(v);

	cout << "number of tiles: " << ready.tiles.size() << endl;
	cout << "tiles recieved: ";
	displayVector<int>(v);
	cout << "tiles recieved: ";
	displayVector<char>(ready_formated.tiles);

	ready.board.resize(225);
	memcpy(ready.board.data(), message.data() + bufferOffset, 225);
	bufferOffset += ready.board.size();
	vector<int> v2(ready.board.begin(), ready.board.end());
	vector<char>board = convertToletters(v2);

	int count = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			ready_formated.board[i][j] = board[count];
			cout << ready_formated.board[i][j] << " ";
			count++;
		}
		cout << endl;
	}

	memcpy(&ready.score, message.data() + bufferOffset, sizeof(ready.score));
	bufferOffset += sizeof(ready.score);
	ready_formated.score = int(_byteswap_ulong(ready.score));
	cout << "myscore: " << ready.score << endl;

	memcpy(&ready.opponentScore, message.data() + bufferOffset, sizeof(ready.opponentScore));
	bufferOffset += sizeof(ready.opponentScore);
	ready_formated.opponentScore = int(_byteswap_ulong(ready.opponentScore));
	cout << "OpponentScore: " << ready.opponentScore << endl << endl;

	memcpy(&ready.playerTime, message.data() + bufferOffset, sizeof(ready.playerTime));
	bufferOffset += sizeof(ready.playerTime);
	ready_formated.playerTime = int(_byteswap_ulong(ready.playerTime));
	cout << "myTime: " << ready.playerTime << endl;
	cout << "my_real_time" << ' ' << timeFormat(ready_formated.playerTime) << endl << endl;

	memcpy(&ready.totalTime, message.data() + bufferOffset, sizeof(ready.totalTime));
	bufferOffset += sizeof(ready.totalTime);
	ready_formated.totalTime = int(_byteswap_ulong(ready.totalTime));
	cout << "totalTime: " << ready.totalTime << endl;
	cout << "my_real_total_time" << ' ' << timeFormat(ready_formated.totalTime) << endl << endl;

	return ready_formated;

}

void Client::sendPass(shared_ptr<WebSocket> ws)
{
	vector<uint8_t> pass;

	pass.push_back(MessageTypes::PASS);
	ws->sendBinary(pass);
}
void Client::sendNoChallenge(shared_ptr<WebSocket> ws)
{
	vector<uint8_t> noChallenge;

	noChallenge.push_back(MessageTypes::NO_CHALLENGE);
	ws->sendBinary(noChallenge);

}
void Client::sendChallenge(shared_ptr<WebSocket> ws)
{
	vector<uint8_t> challenge;

	challenge.push_back(MessageTypes::CHALLENGE);
	ws->sendBinary(challenge);

}
void Client::sendExchange(shared_ptr<WebSocket> ws, vector<char> tiles)
{
	vector<uint8_t> exchange;
	vector<uint8_t> utiles = this->encodeTiles(tiles);
	exchange.push_back(MessageTypes::EXCHANGE);
	exchange.insert(exchange.end(), utiles.begin(), utiles.end());
	ws->sendBinary(exchange);
}
void Client::sendPlay(shared_ptr<WebSocket> ws, playMove play)
{
	uint8_t Scol = play.Scolumn;
	uint8_t Srow = play.Srow;
	uint8_t dir = play.direction;
	INT32 myScore = (INT32)play.score;

	vector<uint8_t> utiles = this->encodeTiles(play.tiles);
	vector<uint8_t> uplay = { MessageTypes::PLAY,Scol,Srow,dir };
	uplay.insert(uplay.end(), utiles.begin(), utiles.end());
	uplay.push_back(myScore >> 24);
	uplay.push_back((myScore >> 16) & 255);
	uplay.push_back((myScore >> 8) & 255);
	uplay.push_back(myScore & 255);
	vector<int>test(uplay.begin(), uplay.end());
	displayVector<int>(test);
	ws->sendBinary(uplay);
}

fromatedTime Client::decodeTime(std::vector<uint8_t>& message)
{
	uTime time;
	fromatedTime t;
	int playTime, totalTime;
	unsigned int bufferOffset = 1;
	memcpy(&time.playerTime, message.data() + bufferOffset, sizeof(time.playerTime));
	bufferOffset += sizeof(time.playerTime);
	playTime = int(_byteswap_ulong(time.playerTime));
	t.playTime = to_string(playTime);
	cout << "from invalid myTime: " << time.playerTime << endl;

	memcpy(&time.totalTime, message.data() + bufferOffset, sizeof(time.totalTime));
	totalTime = int(_byteswap_ulong(time.totalTime));
	t.totalTime = to_string(totalTime);
	bufferOffset += sizeof(time.totalTime);
	cout << "totalTime: " << time.totalTime << endl;
	return t;

}
vector<char> Client::decodeTiles(std::vector<uint8_t>& message)
{
	vector<uint8_t>utiles(7);
	vector<char>tiles(7);
	unsigned int bufferOffset = 1;

	memcpy(utiles.data(), message.data() + bufferOffset, 7);
	vector<int> v(utiles.begin(), utiles.end());
	tiles = convertToletters(v);

	cout << "number of tiles: " << tiles.size() << endl;
	cout << "tiles recieved: ";
	displayVector<char>(tiles);
	return tiles;
}
void Client::decodeChallengeRejected(std::vector<uint8_t>& message, vector<char>&tiles, uTime&time) {

	vector<uint8_t>utiles(7);
	unsigned int bufferOffset = 1;

	memcpy(utiles.data(), message.data() + bufferOffset, 7);
	vector<int> v(utiles.begin(), utiles.end());
	tiles = convertToletters(v);
	bufferOffset += tiles.size();

	memcpy(&time.playerTime, message.data() + bufferOffset, sizeof(time.playerTime));
	bufferOffset += sizeof(time.playerTime);


	memcpy(&time.totalTime, message.data() + bufferOffset, sizeof(time.totalTime));
	bufferOffset += sizeof(time.totalTime);

}

void Client::decodeIdleExchange(std::vector<uint8_t>& message, int &count, uTime&time)
{
	unsigned int bufferOffset = 1;
	uint8_t ucount;
	memcpy(&ucount, message.data() + bufferOffset, 1);
	bufferOffset += sizeof(ucount);
	count = (int)ucount;

	memcpy(&time.playerTime, message.data() + bufferOffset, sizeof(time.playerTime));
	bufferOffset += sizeof(time.playerTime);


	memcpy(&time.totalTime, message.data() + bufferOffset, sizeof(time.totalTime));
	bufferOffset += sizeof(time.totalTime);
}

player2Move_formated Client::decodePlay(std::vector<uint8_t>& message)
{
	player2Move umove;
	player2Move_formated move;
	unsigned int bufferOffset = 1;
	int size = message.size();
	memcpy(&umove.Scolumn, message.data() + bufferOffset, sizeof(umove.Scolumn));
	bufferOffset += sizeof(umove.Scolumn);
	move.Scolumn = int(umove.Scolumn);
	cout << "type: " << move.Scolumn << endl;

	memcpy(&umove.Srow, message.data() + bufferOffset, sizeof(umove.Srow));
	bufferOffset += sizeof(umove.Srow);
	move.Srow = int(umove.Srow);
	cout << "Order: " << move.Srow << endl;

	memcpy(&umove.direction, message.data() + bufferOffset, sizeof(umove.direction));
	bufferOffset += sizeof(umove.direction);
	move.direction = int(umove.direction);
	cout << "Order: " << move.direction << endl;

	umove.tiles.resize(7);
	memcpy(umove.tiles.data(), message.data() + bufferOffset, 7);
	bufferOffset += umove.tiles.size();
	vector<int> v(umove.tiles.begin(), umove.tiles.end());
	move.tiles = convertToletters(v);

	cout << "number of tiles: " << umove.tiles.size() << endl;
	cout << "tiles recieved: ";
	displayVector<int>(v);
	cout << "tiles recieved: ";
	displayVector<char>(move.tiles);

	memcpy(&umove.score, message.data() + bufferOffset, sizeof(umove.score));
	bufferOffset += sizeof(umove.score);
	move.score = int(_byteswap_ulong(umove.score));
	cout << "score: " << move.score << endl;

	memcpy(&umove.challengeTime, message.data() + bufferOffset, sizeof(umove.challengeTime));
	bufferOffset += sizeof(umove.challengeTime);
	move.challengeTime = to_string(int(_byteswap_ulong(umove.challengeTime)));
	cout << "ChallengeTime: " << move.challengeTime << endl;

	memcpy(&umove.time.playerTime, message.data() + bufferOffset, sizeof(umove.time.playerTime));
	bufferOffset += sizeof(umove.time.playerTime);
	move.time.playTime = to_string(int(_byteswap_ulong(umove.time.playerTime)));
	cout << "playerTime: " << move.time.playTime << endl;


	memcpy(&umove.time.totalTime, message.data() + bufferOffset, sizeof(umove.time.totalTime));
	bufferOffset += sizeof(umove.time.totalTime);
	move.time.totalTime = to_string(int(_byteswap_ulong(umove.time.totalTime)));
	cout << "totalTime: " << move.time.totalTime << endl;

	return move;
}

endMove Client::decodeEndGame(std::vector<uint8_t>& message)
{
	endMove end;
	unsigned int bufferoffset = 1;
	memcpy(&end.reason, message.data() + bufferoffset, sizeof(end.reason));
	end.reason = (EndReasons)end.reason;
	cout << end.reason << endl;
	bufferoffset += sizeof(end.reason);

	memcpy(&end.score, message.data() + bufferoffset, 4);
	bufferoffset += 4;
	end.score = int(_byteswap_ulong(end.score));
	cout << "myscore: " << end.score << endl;

	memcpy(&end.opponentScore, message.data() + bufferoffset, 4);
	bufferoffset += 4;
	end.opponentScore = int(_byteswap_ulong(end.opponentScore));
	cout << "OpponentScore: " << end.opponentScore << endl;
	return end;
}

Client::~Client()
{
}

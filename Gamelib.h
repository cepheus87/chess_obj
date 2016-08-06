#ifndef _GAMELIB_H
#define _GAMELIB_H

#include <string>

using namespace std;

enum ConnectorErCode {
	CONNECTOR_NO_ERROR,
	CONNECTOR_DISCONNECTING_PENDING = 0x80000001,
	CONNECTOR_TOO_MANY_PLAYERS,
	CONNECTOR_P_TIMEOUT,
	CONNECTOR_V_TIMEOUT,
	CONNECTOR_CONNECT_WRITE_FAILED,
	CONNECTOR_CONNECT_WRITE_FAILED1,
	CONNECTOR_CONNECT_READ_FAILED,
	CONNECTOR_NOT_CONNECTED,
	CONNECTOR_NOT_YOUR_TURN,
	CONNECTOR_YOU_SHOULD_SEND,
	CONNECTOR_NOT_FOR_USE,
	CONNECTOR_RECEIVE_TIMEOUT,
	CONNECTOR_ALREADY_CONNECTED,
	CONNECTOR_REMOVE_DATA,
	CONNECTOR_WRITE_DATA_ERROR,
	CONNECTOR_WAITFOR_TIMEOUT,
	CONNECTOR_REMOVE_FAILED,
};

const int SEM_TIMEOUT = 5;
const int WAITING_TIMEOUT = 30;
const int DISCONNECT_TIMEOUT = 15;
const int REMOVE_TIMEOUT = 5;
const int RECEIVE_TIMEOUT = 3 * 60;

class Connector {
public:
	ConnectorErCode errCode;

	Connector() :
			errCode(CONNECTOR_NO_ERROR), connected(false) {
	}

	int connect();
	void disconnect();
	bool waitForConnection();
	bool send(const string&);
	bool receive(string& data);

	void reset();

private:
	int id;
	bool connected;
	bool myTurn;

	void p();
	void v();

	int readVal(const char[]);
	void writeVal(const char[], int);
	bool readStr(const char[], string&);
	bool writeStr(const char[], const string&);
	void removeFile(const char[]);
};

#endif // _GAMELIB_H


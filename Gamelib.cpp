#include "Gamelib.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>

static int TIMEOUT_VALUE = 1;


static const char semFilename[]   = "semfile.dat";          // semaphore file
static const char idsFilename[]   = "idsfile.dat";          
static const char dataFilename1[] = "dataForPlayer1.dat";   
static const char dataFilename2[] = "dataForPlayer2.dat";


void Connector::removeFile(const char filename[])
{
	ifstream f;
	
    f.open(filename, ios::in);       // open stream 'f' in an input mode
    if (f.is_open()) {
		f.close();
				
		int cnt = 0;
		do {                                
			if (remove(filename) == 0) 
				return;

			sleep(TIMEOUT_VALUE);                
		} while (++cnt < REMOVE_TIMEOUT);
		errCode = CONNECTOR_REMOVE_FAILED;
	}
 }

void Connector::reset()
{
	removeFile(semFilename);
	removeFile(idsFilename);
	removeFile(dataFilename1);
	removeFile(dataFilename2);
	
	errCode = CONNECTOR_NO_ERROR;
}

int Connector::connect() 
{ 
    if (connected) 
        errCode = CONNECTOR_ALREADY_CONNECTED;  // cannot connect twice 
    else {
        p();
        int value = readVal(idsFilename);
        if (errCode == CONNECTOR_NO_ERROR) {
            if (value == 0) {                   // no players registered so far
                id = 1;
                writeVal(idsFilename, id);      // update idsFile
            } else if (value == 1) {            // player 1 registered
                id = 2;
                writeVal(idsFilename, id);      // update idsFile
            } else if (value < 0)               // player 2 has disconnect
                errCode = CONNECTOR_DISCONNECTING_PENDING;   
            else                                // two players already connected
                errCode = CONNECTOR_TOO_MANY_PLAYERS;   
        }
        v();

        if (errCode == CONNECTOR_NO_ERROR) {
            connected = true; 
            myTurn = (id == 1);
        }
    }
    return (errCode != CONNECTOR_NO_ERROR) ? errCode : id;      // all error codes are greater than 0x80000000
} 

bool Connector::waitForConnection()
{
    if (!connected) 
        errCode = CONNECTOR_NOT_CONNECTED;
    else if (id == 2)                       // player 2 tries to use this method which is illegal
        errCode = CONNECTOR_NOT_FOR_USE;
    else {
        int value;
        int cnt = 0;
        do {                                // wait until player 2 change the value in the file idsFile to 2
            sleep(TIMEOUT_VALUE);
            p();
            value = readVal(idsFilename);
            v();

            if (value == 2)
                break;
        } while ((++cnt < WAITING_TIMEOUT) && (errCode == CONNECTOR_NO_ERROR));

        if (value != 2 && errCode != CONNECTOR_NO_ERROR)
            errCode = CONNECTOR_WAITFOR_TIMEOUT;
    }
    return (errCode == CONNECTOR_NO_ERROR);
}

void Connector::disconnect()
{
    if (!connected) 
        errCode = CONNECTOR_NOT_CONNECTED;
    else if (id == 2) {
        connected = false;
        p();
        writeVal(idsFilename, -id);    // mark that player 2 disconnect    
        v();
    } else if (id == 1) {
        connected = false;
        int cnt = 0;
        int idFromFile;
        do {
            p();
            idFromFile = readVal(idsFilename);
            v();
            if ((errCode == CONNECTOR_NO_ERROR) && (idFromFile == -2))      // player 2 has disconnected
                break;

            sleep(TIMEOUT_VALUE);
        } while (++cnt < DISCONNECT_TIMEOUT);

        p();
		removeFile(idsFilename);
        v();
    }
}

bool Connector::send(const string& data)
{
    if (!connected) 
        errCode = CONNECTOR_NOT_CONNECTED;
    else if (myTurn) {
        if (!writeStr((id == 1) ? dataFilename2 : dataFilename1, data))
            errCode = CONNECTOR_WRITE_DATA_ERROR;

        myTurn = !myTurn;
    } else
        errCode = CONNECTOR_NOT_YOUR_TURN;    

    return (errCode == CONNECTOR_NO_ERROR);
}

bool Connector::receive(string& data)
{
    if (!connected) 
        errCode = CONNECTOR_NOT_CONNECTED;
    else if (myTurn) {
        errCode = CONNECTOR_YOU_SHOULD_SEND;    
    } else {
        int cnt = 0;
        while (!readStr((id == 1) ? dataFilename1 : dataFilename2, data)) {
            cnt++;
            sleep(TIMEOUT_VALUE); 
            if (cnt >= RECEIVE_TIMEOUT) {
                errCode = CONNECTOR_RECEIVE_TIMEOUT;
                return false;
            }
        }
        myTurn = !myTurn;
    } 
    return (errCode == CONNECTOR_NO_ERROR);
}

int saveRandVal() 
{
    ifstream f;
    f.open(semFilename, ios::in);       // open stream 'f' in an input mode
    if (!f.is_open()) {
        ofstream f;
        f.open(semFilename, ios::out);  // open stream 'f' in an output mode
        int randVal = rand();
        if (f.is_open()) 
            f << randVal << endl;
        
        f.close();
        return randVal;
    } else
        f.close();

    return -1;
}

int Connector::readVal(const char filename[]) 
{
    ifstream f;
    f.open(filename, ios::in);       // open stream 'f' in an input mode
    if (f.is_open()) {
        int value;
        f >> value;
        f.close();
        if (f.bad())    
            errCode = CONNECTOR_CONNECT_READ_FAILED;
    
        return (errCode == CONNECTOR_NO_ERROR) ? value : -1;
    }
    return 0;
}

bool Connector::readStr(const char filename[], string& data) 
{
    ifstream f;
    f.open(filename, ios::in);       
    if (f.is_open()) {
        getline(f, data);
        f.close();
        if (remove(filename) != 0) {
            errCode = CONNECTOR_REMOVE_DATA;
            return false;
        }
        return (f.good());
    }
    return false;
}

bool Connector::writeStr(const char filename[], const string& data) 
{
    ofstream f;
    f.open(filename, ios::out);       
    if (f.is_open()) {
        f << data << endl;
        f.close();
        return (f.good());
    }
    return false;
}

void Connector::writeVal(const char filename[], int value) 
{
    ofstream f;
    f.open(filename, ios::out);      
    if (f.is_open()) {
        f << value;
        f.close();
        if (f.bad())
            errCode = CONNECTOR_CONNECT_WRITE_FAILED;
    } else
        errCode = CONNECTOR_CONNECT_WRITE_FAILED1;
}

// wait the sempahore
void Connector::p()
{
    int cnt = 0;
    do {
        int randVal;
        if ((randVal = saveRandVal()) != -1) {
            int randValFromFile = readVal(semFilename);
            if (randVal == randValFromFile)
                return;
        }
        sleep(TIMEOUT_VALUE);                
    } while (++cnt < SEM_TIMEOUT);

    errCode = CONNECTOR_P_TIMEOUT;        
}

// signal the semaphore
void Connector::v() 
{
    int cnt = 0;
    do {
        if (remove(semFilename) == 0) {
            return;
		}
        sleep(TIMEOUT_VALUE);                
    } while (++cnt < SEM_TIMEOUT);

    errCode = CONNECTOR_V_TIMEOUT;
}

//CSV stands for Comma Separated Values. The data fields in a CSV file are separated/delimited by a comma (‘, or ; ‘) and the individual rows are separated by a newline (‘\n’). 

#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include "dataCollection.h"

using namespace std;
long int dataCounter = 0; // The counter is íterating in main
bool dataName = true;
int maxDistance;

int dataCollection() // function is called in main after get data
{
	////////// Test varibles ////////// 
	int counter = dataCounter;//.................counter for the received data 
	float initialDistance = (float)recvArray[0] *4;
	float maxDistanceDC = (float)recvArray[0] * 4 * 1.2f;
	int handDistance = recvArray[1];		// Local variable in noteAssigner - The reason I did this was due to I  not sure whether or not recvArray would be updated by RealMIDI or if the data was directly from server
	int velocity = recvArray[2];			// velocity. Interval: 0 - 100
	float distFloat = volumeAssigner();		// float conversion of velocity. Interval: 0,0 - 0
	int note = playedSounds[0][counterStart];

	switch (playedSounds[0][counterStart])
	{
		case 0:
			note = 0;
			break;
		case 86:
			note = 1;
			break;
		case 82:
			note = 2;
			break;
		case 78:
			note = 3;
			break;
		case 74:
			note = 4;
			break;
		case 70:
			note = 5;
			break;
		case 66:
			note = 6;
			break;
		case 62:
			note = 7;
			break;
		case 58:
			note = 8;
			break;
		case 54:
			note = 9;
			break;
		case 50:
			note = 10;
			break;
		case 46:
			note = 11;
			break;
		case 42:
			note = 12;
			break;
		default:
			note = 00;
			break;
	}

	ofstream myFile; //.......................................................file pointer
	string filename = "c++ data collection.csv"; //...........................file name
	myFile.open(filename, ios::out | ios::app | ios::binary); //.................................................opens the file for input - iso::out if removed the "," needs to be changes to ";"
	if (dataName == true) {
		myFile << "counter" << ";" << "initialDistance" << ";" << "maxDistance" << ";" << "handDistance" << ";" << "velocity" << ";" << "distfloat velocity" << ";" << "note played" << endl;
		dataName = false;
	}
	myFile << counter << ";" << initialDistance << ";" << maxDistanceDC << ";" << handDistance << ";" << velocity << ";" << distFloat << ";" << note << endl;
	myFile.close();//.........................................................closes the file
	return 0;
}
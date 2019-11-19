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
	int note = noteAssigner();



	ofstream myFile; //.......................................................file pointer
	string filename = "c++ data collection.csv"; //...........................file name
	myFile.open(filename, ios::out | ios::app | ios::binary); //.................................................opens the file for input - iso::out if removed the "," needs to be changes to ";"
	if (dataName == true) {
		myFile << "counter" << "," << "initialDistance" << "," << "maxDistance" << "," << "handDistance" << "," << "velocity" << "," << "distfloat velocity" << "," << "note played" << endl;
		dataName = false;
	}
	myFile << counter << "," << initialDistance << "," << maxDistanceDC << "," << handDistance << "," << velocity << "," << distFloat << "," << note << endl;
	myFile.close();//.........................................................closes the file
	return 0;
}
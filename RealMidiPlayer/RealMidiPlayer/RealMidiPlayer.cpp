#include <iostream>
#include <string>
#include "Sound.h"
#include "server_done.h"
#include <fstream>

using namespace std;

const int maxSection = 13;			//The number of sectors that the program can choose from, representing the neck intervals of one string(1-2 and 2-3)
int recvArray[3]; //place 0 is the max distance, place 1 is current distance, and the velocity
int dividend = 3;
int playedSounds[2][10];
float sections[maxSection];         //This array stores the size of the different sectors for the sorting algorithm
bool getData = false;
int a = 0;
bool b = true;
struct Note
{
	long long int timer = clock();
	int section = noteAssigner();
	Note* _nextNote = NULL;
};
typedef Note* _NotePtr;

int write2File(string a, int b)
{
	ofstream testFile;
	testFile.open("Iteration2_test.txt", ios::out | ios::app | ios::binary);
	testFile << a;
	testFile << b;
	testFile << " !delete this! ";
	testFile.close();
	return 0;
}

void newNote(_NotePtr& _newNote)
{
	cout << "new note" << endl;
	_NotePtr _tmpPtr;
	_tmpPtr = new Note;

	_newNote-> _nextNote = _tmpPtr;

	_newNote = _tmpPtr;
}

void stopNote(_NotePtr& _QueueOUT, _NotePtr& _QueueIN)
{

	_NotePtr _tmpPtrOUT = _QueueOUT->_nextNote;
	_NotePtr _tmpPtrIN = _QueueIN->_nextNote;
	if (_QueueOUT->_nextNote != NULL)
	{

		cout << _QueueOUT->timer << endl;

		if (_QueueOUT->timer + 2000 <= clock())
		{
			cout << "okay, here is some stuff" << endl;
			endSound(_QueueOUT->section); //temp note call to an if statement in sound.cpp. This should turn the sound off and based on the clock

			if (_QueueOUT->_nextNote != _QueueIN->_nextNote);
			{
				delete _QueueOUT;
				_QueueOUT = _tmpPtrOUT;
				cout << "deleted oldest" << endl;
				b = true;
			}
		}
	}
}

void section_Calculator() {
	unsigned int maxDistance;
	maxDistance = (float)recvArray[0] * 3 * 1.2f;
	float sectionSize = maxDistance / (maxSection - 1);    //Calculates the size that each section has to have as a function of the different sectors and the distance inputted.
	for (int i = 0; i <= maxSection - 1; i++) {	//Calculates and assigns the starting point of each section.
		sections[i] = sectionSize * i;			// Assignes the value based on its postions on the neck(A to B)
	}
	cout << "Max distance for the guitar ";
	cout << maxDistance << endl;
	cout << "distance of each distance ";
	cout << sectionSize << endl;
}

int noteAssigner()
{                           //This functions runs through the different sectors assigned above and finds out which one the inputted length matches to.
	recvArray[1] = recvArray[1];// *dividend;
	
	for (int i = 0; i < maxSection; i++) {
		if (recvArray[1] >= sections[i] && recvArray[1] < sections[i + 1]) {
			int sector = i + 1;
			write2File("Segmented note-interval = ", sector);
			return sector;
			//cout << "RETURNED" << endl
		}
	}
	//cout << "The length inputted is either above or below the maximum arm distance.";
	return 1;
}

float volumeAssigner()
{
	recvArray[2] = recvArray[2]; //* dividend;

	int distInt = recvArray[2];
	return ((float)distInt / 100);
}

int main()
{
	start_Sound();
	thread ServerThread(server_main);
	ServerThread.detach();
	cout << "New Thread" << endl;

	_NotePtr _QueueIN, _QueueOUT;
	_QueueIN = new Note;
	_QueueOUT = _QueueIN;
	while (true) {
		if (getData == true) {
			if (recvArray[0] != 0) 
			{
				section_Calculator();
			}
			
			newNote(_QueueIN);
			cout << "Starting to print queue:\n";
			_NotePtr iter;
			for (iter = _QueueOUT; iter != NULL; iter = iter->_nextNote) {
				cout << iter->timer << ", " << iter->_nextNote << iter->section << "\n";
			}
			cout << "\n";
			playNote(_QueueIN->section);
			//SDL_Delay(500);
			getData = false;
		};

		stopNote(_QueueOUT, _QueueIN);
	}
}
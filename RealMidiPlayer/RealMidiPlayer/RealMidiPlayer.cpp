#include <iostream>
#include <string>
#include "Sound.h"
#include "server_done.h"
#include <fstream>
#include "tsf.h"
#include <ctime>

using namespace std;

bool getData = false;
const int maxSection = 13;			//The number of sectors that the program can choose from, representing the neck intervals of one string(1-2 and 2-3)
int dividend = 4;
int counterStart = 2;
int recvArray[3]; //place 0 is the max distance, place 1 is current distance, and the velocity
int playedSounds[2][20];
int sector;
int notes[13] = { 0, 96, 90, 84, 78, 72, 66, 60, 54, 50, 48, 46, 44 };
float sections[maxSection];         //This array stores the size of the different sectors for the sorting algorithm

void section_Calculator() {
	unsigned int maxDistance;
	maxDistance = (float)recvArray[0] * 4 * 1.2f;
	float sectionSize = maxDistance / (maxSection - 1);    //Calculates the size that each section has to have as a function of the different sectors and the distance inputted.
	for (int i = 0; i <= maxSection - 1; i++) {	//Calculates and assigns the starting point of each section.
		sections[i] = sectionSize * i;			// Assignes the value based on its postions on the neck(A to B)
	}
}

int noteAssigner()
{                           //This functions runs through the different sectors assigned above and finds out which one the inputted length matches to.
	recvArray[1] = recvArray[1] * 4;
	cout << "Semi-cooked data after treatment: " << recvArray[1] << "\n";

	for (int i = 0; i < maxSection; i++) {
		if (recvArray[1] >= sections[i] && recvArray[1] < sections[i + 1]) {
			int sector = i + 1;
			cout << "This is the sector that the thing registers as: " << sector << "\n";

			return sector;
		}
	}
	// cout << "The length inputted is either above or below the maximum arm distance. \n";
	return 1;
}

float volumeAssigner()
{
	float distFloat = (float)recvArray[2] / 100;
	// cout << "Float is:" << distFloat << "\n";
	return distFloat;
}

int main()
{
	start_Sound();
	thread ServerThread(server_main);
	ServerThread.detach();
	cout << "New Thread" << endl;

	while (true) {
		if (getData == true) {
			if (recvArray[0] != 0)
			{
				section_Calculator();
			}

			playedSounds[1][counterStart] = clock();
			playedSounds[0][counterStart] = notes[noteAssigner()];
			cout << "This is the value registered in the array: " << playedSounds[0][counterStart] << "\n";


			playNote();
			counterStart++;

			if (counterStart >= 19) {
				counterStart = 2;
			}
			//SDL_Delay(500);
			getData = false;
		};
		
		stopNote();
	}
}
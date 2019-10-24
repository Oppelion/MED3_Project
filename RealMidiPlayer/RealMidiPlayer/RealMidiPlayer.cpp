#include <iostream>
#include <String>
#include "Sound.h"
#include "server_done.h"

using namespace std;

const int maxSection = 13;			//The number of sectors that the program can choose from, representing the neck intervals of one string(1-2 and 2-3)
float sectionSize;					//Storage variable for the size of the sectors
float sections[maxSection];         //This array stores the size of the different sectors for the sorting algorithm
float DistFloat;
int playedSection;
int distInt;
int recvArray[3]; //place 0 is the max distance, place 1 is current distance, and the velocity
bool getData = false;
int dividend = 2;

int section_Calculator() {
	recvArray[0] = recvArray[0] * dividend;
	sectionSize = recvArray[0] / (maxSection-1);    //Calculates the size that each section has to have as a function of the different sectors and the distance inputted.
	for(int i = 0; i <= maxSection - 1; i++) {	//Calculates and assigns the starting point of each section.
		sections[i] = sectionSize * i;			// Assignes the value based on its postions on the neck(A to B)
	}

	return 0;
}

int note_Assigner() {                           //This functions runs through the different sectors assigned above and finds out which one the inputted length matches to.
	recvArray[1] = recvArray[1] * dividend;
	recvArray[2] = recvArray[2] * dividend;

		distInt = recvArray[2];
		DistFloat = ((float)distInt / 100);
	
	for (int i = 0; i < maxSection; i++) {
		if (recvArray[1] >= sections[i] && recvArray[1] < sections[i + 1]) {
			cout << "The interval is in sector ";            //These two lines writes which sector the length belongs to.
			cout << i + 1;
			playedSection = i + 1;
			return 0;
		}
	}
	cout << "The length inputted is either above or below the maximum arm distance.";
	return 0;
}

void playSound() {
	note_Assigner(),
	playNote();
}

int main(){
	start_Sound();
	thread ServerThread(server_main);
	cout << "New Thread" << endl;
	cout << recvArray[0] + " " + recvArray[1] + recvArray[2] << endl;
	section_Calculator();
	while (true) {
		if (getData == true) {
			playSound();
			getData = false;
		};
	}
}
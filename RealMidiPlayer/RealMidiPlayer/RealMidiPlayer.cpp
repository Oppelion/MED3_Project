#include <iostream>
#include <String>
#include "Sound.h"
#include "server_done.h"

bool getData = true;
const int maxSection = 13;			//The number of sectors that the program can choose from, representing the neck intervals of one string(1-2 and 2-3)
float sectionSize;					//Storage variable for the size of the sectors
float sections[maxSection];         //This array stores the size of the different sectors for the sorting algorithm
float DistFloat;
int playedSection;
int distInt;
int recvArray[3]; //place 0 is the max distance, place 1 is current distance, and the velocity



int section_Calculator() {
	sectionSize = recvArray[0] / (maxSection-1);    //Calculates the size that each section has to have as a function of the different sectors and the distance inputted.
	for(int i = 0; i <= maxSection - 1; i++) {	//Calculates and assigns the starting point of each section.
		std::cout << "et eller andet random";
		sections[i] = sectionSize * i;			// Assignes the value based on its postions on the neck(A to B)
		std::cout << sections[i];
	}
	if (recvArray[2] < 100) {
		distInt = recvArray[2];
		DistFloat = ((float)distInt / 100);
	}
	else {
		std::cout << "The integer sent is above 100. Please beat the IP programmers.";
	}
	return 0;
}

int note_Assigner() {                           //This functions runs through the different sectors assigned above and finds out which one the inputted length matches to.
	for (int i = 0; i <= maxSection - 1; i++) {
		if (recvArray[1] >= sections[i] && recvArray[1] < sections[i + 1]) {
			std::cout << "The interval is in sector ";            //These two lines writes which sector the length belongs to.
			std::cout << i + 1;
			playedSection = i + 1;
			return 0;
		}
	}
	std::cout << "The length inputted is either above or below the maximum arm distance.";
	return 0;
}

int main(){
	start_Sound();
	server_main();
	std::cout << "Test\n";
	while (getData == true) {
		section_Calculator();
		note_Assigner();
		playNote();
	}
}
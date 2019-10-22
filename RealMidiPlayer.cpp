#include <iostream>
#include <String>

int length;                         //Placeholder variable used to simulate the values sent from the image processing part.
float maxDistP;						//The calibrated length between the users arms
const int maxSection = 13;			//The number of sectors that the program can choose from, representing the neck intervals of one string(1-2 and 2-3)
float sectionSize;					//Storage variable for the size of the sectors
float sections[maxSection];         //This array stores the size of the different sectors for the sorting algorithm


int section_Calculator() {
	std::cout << "Enter a max distance\n";
	sectionSize = maxDistP / (maxSection-1);    //Calculates the size that each section has to have as a function of the different sectors and the distance inputted.
	for(int i = 0; i <= maxSection - 1; i++) {	//Calculates and assigns the starting point of each section.
		std::cout << "\n";
		sections[i] = sectionSize * i;			// Assignes the value based on its postions on the neck(A to B)
		std::cout << sections[i];
	}
	return 0;
}

int note_Assigner() {                           //This functions runs through the different sectors assigned above and finds out which one the inputted length matches to.
	for (int i = 0; i <= maxSection - 1; i++) {
		if (length >= sections[i] && length < sections[i + 1]) {
			std::cout << "The interval is in sector ";            //These two lines writes which sector the length belongs to.
			std::cout << i + 1;
			return 0;
		}
	}
	std::cout << "The length inputted is either above or below the maximum arm distance.";
}

int main(){
	std::cout << "Test\n";
	std::cin >> maxDistP;                          //Input the maximum distance that can possibly be between the hands.
	section_Calculator();
	std::cout << "\nenter length\n";
	std::cin >> length;                            //Inputs the distance between the hands
	note_Assigner();
	return 0;
}
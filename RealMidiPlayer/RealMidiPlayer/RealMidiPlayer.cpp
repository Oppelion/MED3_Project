#include <iostream>
#include <String>
#include "Sound.h"
#include "server_done.h"

using namespace std;

const int maxSection = 13;			//The number of sectors that the program can choose from, representing the neck intervals of one string(1-2 and 2-3)
int recvArray[3]; //place 0 is the max distance, place 1 is current distance, and the velocity
int dividend = 3;
int playedSounds[2][10];
float sections[maxSection];         //This array stores the size of the different sectors for the sorting algorithm
bool getData = false;
int a = 0;

int section_Calculator() {
	recvArray[0] = recvArray[0]; //* dividend * 1.2f;
	float sectionSize = recvArray[0] / (maxSection-1);    //Calculates the size that each section has to have as a function of the different sectors and the distance inputted.
	for(int i = 0; i <= maxSection - 1; i++) {	//Calculates and assigns the starting point of each section.
		sections[i] = sectionSize * i;			// Assignes the value based on its postions on the neck(A to B)
	}
	return 0;
}

int noteAssigner()
{                           //This functions runs through the different sectors assigned above and finds out which one the inputted length matches to.
	recvArray[1] = recvArray[1];// *dividend;
	
	for (int i = 0; i < maxSection; i++) {
		if (recvArray[1] >= sections[i] && recvArray[1] < sections[i + 1]) {
			int sector = i + 1;
			return sector;
			//cout << "RETURNED" << endl;
		}
	}
	//cout << "The length inputted is either above or below the maximum arm distance.";
}

float volumeAssigner()
{
	recvArray[2] = recvArray[2]; //* dividend;

	int distInt = recvArray[2];
	return ((float)distInt / 100);
}

//This function is for testing
void keyPressedFunction(){
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 9 + (a * 10);
		recvArray[2] = 100;
		a++;
		if (a >= 13) {
			a = 0;
		}
	/*
	if(GetKeyState('A') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 9;
		recvArray[2] = 40;
	}
	
	if(GetKeyState('S') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 19;
		recvArray[2] = 40;
	}

	if(GetKeyState('D') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 29;
		recvArray[2] = 40;
	}

	if(GetKeyState('F') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 39;
		recvArray[2] = 40;
	}
	
	if(GetKeyState('G') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 49;
		recvArray[2] = 40;
	}
	
	if(GetKeyState('H') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 59;
		recvArray[2] = 40;
	}
	
	if(GetKeyState('J') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 69;
		recvArray[2] = 40;
	}
	
	if(GetKeyState('K') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 79;
		recvArray[2] = 40;
	}
	
	if(GetKeyState('L') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 89;
		recvArray[2] = 40;
	}
	
	if(GetKeyState('F') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 99;
		recvArray[2] = 40;
	}

	if(GetKeyState('Z') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 109;
		recvArray[2] = 40;
	}
	if(GetKeyState('X') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 119;
		recvArray[2] = 40;
	}
	if(GetKeyState('C') & 0x8000)
	{
		getData = true;
		recvArray[0] = 130;
		recvArray[1] = 129;
		recvArray[2] = 40;
	}*/
} //Delete me later

int main()
{
	start_Sound();
	thread ServerThread(server_main);
	ServerThread.detach();
	cout << "New Thread" << endl;

	int whichSound = 0;
	while (true) {
		keyPressedFunction();
		if (getData == true) {
			if (recvArray[0] != 0) 
			{
				section_Calculator();
			}
			whichSound++;
			if (whichSound == 10)
			{
				whichSound = 0;
			}
			playNote(whichSound);
			//SDL_Delay(500);
			getData = false;
		};
		endSound();
	}
}
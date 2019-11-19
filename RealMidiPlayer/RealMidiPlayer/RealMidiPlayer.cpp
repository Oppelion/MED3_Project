#include <iostream>
#include <string>
#include "Sound.h"
#include "server_done.h"
#include <fstream>
#include "tsf.h"
#include "dataCollection.h"
#include <ctime>

using namespace std;

const int maxSection = 13;												                             //The number of sectors that the program can choose from, representing the neck intervals of one string(1-2 and 2-3)

int dividend = 4;														                             //Uses to multiply data recived, because the recived data is divided in the Python part of the program (Called dividend because of naming in Python part)
int counterStart = 2;                                                                                //This integer increments up as you play tunes.
int recvArray[3];                                                                                    //Place 0 is the max distance, place 1 is current distance, and the velocity (used to store recived data)
int playedSounds[2][20];												                             //Array used to store the note played and when it is started
int notes[13] = { 0, 86, 82, 78, 74, 70, 66, 62, 58, 54, 50, 46, 42 };                               //Lowest 0 highest 127 (Notes that can be played based on chosen sector)

float sections[maxSection];                                                                          //This array stores the size of the different sectors for the sorting algorithm

bool getData = false;													                             //Race condition for when to play sounds

void section_Calculator()												                             //section_Calculator is run once when the program has received the first set of data from the server. It calculates each of the sections, where a different note will be played.
{                                             
	unsigned int maxDistance;											                             //The maximum allowed distance between BLOBs (Distance can't be below zero)
	maxDistance = (float)recvArray[0] * 4 * 1.2f;                                                    //maxDistance is calculated by first multiplying the received distance by 4, to return it to its previous state, and then multiplied again by 1.2, to give the player the maximum distance their hands has to be within. 
	float sectionSize = maxDistance / (maxSection - 1);					                             //Calculates the size that each section has to have as a function of the different sectors and the distance inputted.

	for (int i = 0; i <= maxSection - 1; i++)							                             //Calculates and assigns the starting point of each section.
	{	
		sections[i] = sectionSize * i;									                             //Assignes the value based on its postions on the neck(A to B)
	}
}

int noteAssigner()                                                                                   //noteAssigner takes the received current distance and finds out which section the values is within, to choose which tone has to be played.
{
	recvArray[1] = recvArray[1] * 4;                                                                 //Returns the received value into its original value.
	for (int i = 0; i < maxSection; i++)                                                             //This for loop uses maxsection to find out how manny times it has to run.
	{
		if (recvArray[1] >= sections[i] && recvArray[1] < sections[i + 1])                           //If the received value is within these two points, you have found the sector it belongs to.
		{
			int sector = i + 1;											                             //The sector to be played (Sector not allow to be zero, hence the +1)
			cout << "sector: " << sector << endl;
			return sector;                                                                           //Returns the value to main.
		}
	}
	cout << "The length inputted is either above the maximum arm distance or below zero." << endl;   //Cout statement to point out if a flaw with the maximum distance is detected
	return 1;																						 //Default return
}

float volumeAssigner()                                                                               //This function calculates the volume that the note has to be played at.
{
	float distFloat = (float)recvArray[2] / 100;													//Converts the float to a percentage
	return distFloat;                                                                               //Returns the value to main.
}

int main()
{
	start_Sound();                                                                                  //start_Sound sets up the necessary settings for the soundfont to work, then plays one note to load the soundfont into memory.
	thread ServerThread(server_main);			                                                    //Thread for the server, so that the main and server can run independtly of each other.
	ServerThread.detach();						                                                    //Detaches the server thread, since the main and server does not need to directly communicate.
	cout << "New Thread" << endl;																	//Print statement to verify thread is succesfully created.

	while (true) {                                                                                  //This while loop runs infinitely until the program is shut down.
		if (getData == true)                                                                        //This if statement ensures that the program will not play several notes in quick succession if the user did not do it on purpose. 
		{
			if (recvArray[0] != 0)                                                                  //This function is only run once when the program has gotten its first set of data.
			{
				section_Calculator();																//Function found on line 23
			}

			playedSounds[1][counterStart] = clock();												//Sets the time at which is sound is being played using counterStart to choose the placement inside the 2D-array.
			playedSounds[0][counterStart] = notes[noteAssigner()];									//Sets the note being played by the same method as above.

			playNote();                                                                             //Function found in Sound.cpp line 32.
			dataCollection();
			counterStart++;																			//Increment counterStarter by 1 :-)
			++dataCounter;
			if (counterStart >= 19) {                                                               //Once the counterStart reaches 19, it is reset.
				counterStart = 2;																	//Resets counterStart to 2, since the array bugs if this equals 1.
			}
			getData = false;																		//Cancels the while loop until next time data is received through server.
		};
		stopNote();                                                                                 //Function found in Sound.cpp line 38
	}
}
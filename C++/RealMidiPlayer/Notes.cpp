#include "Notes.h";

using namespace std;

Notes::Notes()
{                                                                            //Place 0 is the max distance, place 1 is current distance, and place 2 is the velocity
	const int maxSection = 13;																		//The number of sectors that the program can choose from, representing the neck intervals of one string
	float sections[maxSection];																	    //This array stores the size of the different sectors for the sorting algorithm
}
void Notes::section_Calculator()												                    //section_Calculator is run once when the program has received the first set of data from the server. It calculates each of the sections, where a different note will be played.
{
	unsigned int maxDistance;											                            //The maximum allowed distance between BLOBs (Distance can't be below zero)
	maxDistance = (float)recvArray[0] * 4 * 1.2f;                                                   //maxDistance is calculated by first multiplying the received distance by 4, to return it to its previous state, and then multiplied again by 1.2, to give the player the maximum distance their hands has to be within. 
	float sectionSize = maxDistance / (maxSection - 1);					                            //Calculates the size that each section has to have as a function of the different sectors and the distance inputted.

	for (int i = 0; i <= maxSection - 1; i++)							                            //Calculates and assigns the starting point of each section.
	{
		sections[i] = sectionSize * i;									                            //Assignes the value based on its postions on the neck(A to B)
	}
}

int Notes::noteAssigner()                                                                           //noteAssigner takes the received current distance and finds out which section the values is within, to choose which tone has to be played.
{
	recvArray[1] = recvArray[1] * 4;                                                                //Returns the received value into its original value.
	for (int i = 0; i < maxSection; i++)                                                            //This for loop uses maxsection to find out how manny times it has to run.
	{
		if (recvArray[1] >= sections[i] && recvArray[1] < sections[i + 1])                          //If the received value is within these two points, you have found the sector it belongs to.
		{
			int sector = i + 1;											                            //The sector to be played (Sector not allow to be zero, hence the +1)
			cout << "sector: " << sector << endl;
			return sector;                                                                          //Returns the value to main.
		} // i + 1
	}
	cout << "The length inputted is either above the maximum arm distance or below zero." << endl;  //Cout statement to point out if a flaw with the maximum distance is detected
	return 1;																						//Default return
}
#include <iostream>				                                                                     // Header that defines the standard input/output stream objects:
#include <string>				                                                                     // Needed for c++ to use strings
#include "Sound.h"				                                                                     // includes the header file for the sound c++ file
#include "Notes.h"				                                                                     // includes the header file for the Notes c++ file
#include "server.h"		                                                                             // Header file for the server
#include <fstream>				                                                                     // Class that performs input/output operations on the files they are associated with
#include "tsf.h"				                                                                     // Header file for tinySoundFont library
#include "dataCollection.h"		                                                                     // Header file for datacollection
#include <ctime>				                                                                     // Class for functions used to manipulate date and time information

using namespace std;

// Global variables
									                            

int dividend = 4;														                             // Uses to multiply data recived, because the recived data is divided in the Python part of the program
int counterStart = 2;                                                                                // This integer increments up as you play tunes.
int recvArray[3];                                                                                    // Place 0 is the max distance, place 1 is current distance, and place 2 is the velocity received from python
int playedSounds[2][20];												                             // Array used to store the note played and when it is started
int notes[13] = { 0, 86, 82, 78, 74, 70, 66, 62, 58, 54, 50, 46, 42 };                               // These are the notes that can be played in the MIDI 
bool getData = false;													                             // Used to stop repeat notes when new data has not been sent

float volumeAssigner()                                                                               // This function calculates the volume that the note has to be played at.
{
	float distFloat = (float)recvArray[2] / 100;													 // Converts the float to a percentage
	return distFloat;                                                                                // Returns the value to main.
}

int main()
{
	Server* server = new Server();
	thread serverThread(&Server::server_main, server);				                                 // Thread for the server, so that the main and server can run independtly of each other.
	Notes note;
	Play Playnotes;
	Playnotes.start_Sound();                                                                         // start_Sound sets up the necessary settings for the soundfont to work, then plays one note to load the soundfont into memory.

	while (true) {                                                                                   // This while loop runs infinitely until the program is shut down.
		if (getData == true)                                                                         // This if statement ensures that the program will not play several notes in quick succession if the user did not do it on purpose. 
		{
			if (recvArray[0] != 0)                                                                   // This function is only run once when the program has gotten its first set of data.
			{
				note.section_Calculator();														     // Function found on line 23
			}

			playedSounds[1][counterStart] = clock();												 // Sets the time at which is sound is being played using counterStart to choose the placement inside the 2D-array.
			playedSounds[0][counterStart] = notes[note.noteAssigner()];								 // Sets the note being played by the same method as above.

			Playnotes.playNote();                                                                    // Function found in Sound.cpp line 32.
			dataCollection();																		 // Function found in DataCollection.cpp line 14
			counterStart++;																			 // Increment counterStarter by 1 :-) (Used for time management)
			++dataCounter;																			 // Increment dataCounter by 1 :-) (Used for datacollection management)
			if (counterStart >= 19) {                                                                // Once the counterStart reaches 19, it is reset.
				counterStart = 2;																	 // Resets counterStart to 2, since the array bugs if this equals 1.
			}
			getData = false;																		 // Cancels the while loop until next time data is received through server.
		};
		Playnotes.stopNote();                                                                        // Function found in Sound.cpp line 38
	}
}
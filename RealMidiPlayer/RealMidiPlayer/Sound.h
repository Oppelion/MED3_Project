/* Header file 
"The compiler has no knowledge of what names are declared in other compilation units. That means that if you define a class or function or global variable, 
you must provide a declaration of that thing in each additional .cpp file that uses it. Each declaration of that thing must be exactly identical in all files. 
A slight inconsistency will cause errors, or unintended behavior, when the linker attempts to merge all the compilation units into a single program."
https://docs.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=vs-2019 (Accessed 21-11-2019, 10:36)
------------------------------------------------

	 #####
	#### _\_  ________
	##=-[.].]| \      \
	#(    _\ |  |------|
	 #   __| |  ||||||||
	  \  _/  |  ||||||||
   .--'--'-. |  | ____ |
  / __      `|__|[o__o]|
_(____nm_______ /____\____

------------------------------------------------
*/

#ifndef SOUND_H
#define SOUND_H
#include <iostream>
#include <thread>				//Used for multithreading
#include <chrono>				//Used for clock access
#include <string>
#include "minisdl_audio.h"
#include <fstream>

// These variables and functions are need in Sound c++, so they are added to Sound C++ files scopes.
void playNote();
void stopNote();
int noteAssigner();
int start_Sound();
float volumeAssigner();
extern bool getData;
extern int sector;
extern int playedSounds[2][20];
extern int notes[13];
extern int counterStart;
extern int recvArray[3];
#endif
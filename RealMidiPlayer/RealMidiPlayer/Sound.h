#ifndef SOUND_H
#define SOUND_H
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "minisdl_audio.h"
#include <fstream>
void playNote();
int noteAssigner();
int start_Sound();
float volumeAssigner();
void stopNote();
extern bool getData;
extern int sector;
extern int playedSounds[2][20];
extern int notes[13];
extern int counterStart;
extern int recvArray[3];
#endif
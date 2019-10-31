#ifndef SOUND_H
#define SOUND_H
#include <iostream>
#include <thread>
#include <chrono>
#include "minisdl_audio.h"
//Ask Jesper why we need to declare an int and a float to times for them to accessible  by two cpp files with a header file 
void playNote(int section);
int noteAssigner();
int start_Sound();
void endSound(int section);
float volumeAssigner();
#endif
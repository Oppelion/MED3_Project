#ifndef SOUND_H
#define SOUND_H
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "minisdl_audio.h"
#include <fstream>
int write2File(std::string a, int b);
void playNote(int section);
int noteAssigner();
int start_Sound();
void endSound(int section);
float volumeAssigner();
#endif
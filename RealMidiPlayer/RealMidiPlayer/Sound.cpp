#include "Sound.h";
#define TSF_IMPLEMENTATION
#include "tsf.h"
#include <string>
#include <queue>

using namespace std;

queue <int> soundQueue;                                                                                    //The queue is implemented to make a first-in-first-out system when shutting off tones.
bool soundLoad = true;                                                                                     //soundLoad toggles the note that is played when the program is initially started.
int counterEnd = 2;                                                                                        //Serves the same purpose as counterStart in RealMidiPLayer.cpp

// Holds the global instance pointer(copy)

static tsf* soundFont;                                                                                     //Creates an object that will be referred to through the entire code.


static void AudioCallback(void* data, Uint8* stream, int len)                                              //This function is responsible for taking ths setup data and applying it to the note we are playing.
{
	int SampleCount = (len / (2 * sizeof(float))); //2 output channels
	tsf_render_float(soundFont, (float*)stream, SampleCount, 0);
}

/*
Link to the Library: https://github.com/schellingb/TinySoundFont/blame/master/tsf.h
Start playing a note
   preset_index: preset index >= 0 and < tsf_get_presetcount()
   key: note value between 0 and 127 (60 being middle C)
 vel: velocity as a float between 0.0 (equal to note off) and 1.0 (full)
 */

void playNote()																	                           //Function starts the sound to be played and pushes to the queue.
{
	tsf_note_on(soundFont, 29, playedSounds[0][counterStart], volumeAssigner());                           //Starts sound using the soundfont, index of the instrument, the note, and the volume.
	soundQueue.push(playedSounds[1][counterStart] + 1000);						                           //Puts the timer into the queue, so it end 1000 milliseconds after the note was initially played.
}

void stopNote()																	                           //Function that stops sound which is currently being played.
{
	if (soundQueue.empty() == false)                                                                       //If the queue is read when there is no data in it, the program will crash. This will prohibit the code from running this part if the queue is empty.
	{
		if (clock() >= soundQueue.front())                                                                 //If the current clock is equal to the time registered in the foremost value, run the rest of this function.
		{
			tsf_note_off(soundFont, 29, playedSounds[0][counterEnd]);                                      //This stops the note from playing, by using the counterEnd to find the note that has to be closed.
			soundQueue.pop();                                                                              //pop destroys the foremost value in the queue, automatically moving the value behind to the front.
			counterEnd++;
			if (counterEnd >= 19)                                                                          //When counterEnd reaches 19, reset it.
			{
				counterEnd = 2;
			}
		}
	}
}


int start_Sound() 
{
	//Define the desired audio output format we request
	SDL_AudioSpec OutputAudioSpec;
	OutputAudioSpec.freq = 44100;                                                                          //Sets the frequency of which the audio needs to be played on.
	OutputAudioSpec.format = AUDIO_F32;                                                                    //Sets the audio format.
	OutputAudioSpec.channels = 2;                                                                          //Sets the channel the audio will be played on.
	OutputAudioSpec.samples = 4096;
	OutputAudioSpec.callback = AudioCallback;

	//Initialize the audio system
	if (SDL_AudioInit(TSF_NULL) < 0)
	{
		fprintf(stderr, "Could not initialize audio hardware or driver\n");
		return 1;
	}

	//Load the SoundFont from a file
	soundFont = tsf_load_filename("Soundfont1.sf2");
	if (!soundFont)
	{
		fprintf(stderr, "Could not load SoundFont\n");
		return 1;
	}

	//Set the SoundFont rendering output mode
	tsf_set_output(soundFont, TSF_STEREO_INTERLEAVED, OutputAudioSpec.freq, 0);

	//Request the desired audio output format
	if (SDL_OpenAudio(&OutputAudioSpec, TSF_NULL) < 0)
	{
		fprintf(stderr, "Could not open the audio hardware or the desired audio output format\n");
		return 1;
	}

	//Start the actual audio playback here
	//The audio thread will begin to call our AudioCallback function
	//Interval for guitar 29 starts at 23 to 126
	//Interval for guitar 30 starts at 0 to 126


	SDL_PauseAudio(0);
	if (soundLoad == true) 
	{
		tsf_note_on(soundFont, 30, 60, 0.0f);
		cout << "Sound is loaded" << endl;
		soundLoad = false;
	}
	return 0;
}
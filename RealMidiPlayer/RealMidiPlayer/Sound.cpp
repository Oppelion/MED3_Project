#include "Sound.h";
#define TSF_IMPLEMENTATION
#include "tsf.h"
#include <String>
bool soundLoad = true;
int notes[13] = { 0, 96, 90, 84, 78, 72, 66, 60, 54, 48, 42, 36, 30 };
// Holds the global instance pointer(copy)
static tsf* soundFont;


static void AudioCallback(void* data, Uint8* stream, int len)
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

void playNote(int whichSound) {
	//These three lines below play the three notes that make up the cord for each section             //int i, Notes[7] = { 48, 50, 52, 53, 55, 57, 59 };
	if (playedSounds[1][whichSound] == 0)
	{
		playedSounds[0][whichSound] = clock();
		playedSounds[1][whichSound] = noteAssigner();
		tsf_note_on(soundFont, 29, notes[playedSounds[1][whichSound]] - 2, volumeAssigner());
		tsf_note_on(soundFont, 29, notes[playedSounds[1][whichSound]], volumeAssigner());
		tsf_note_on(soundFont, 29, notes[playedSounds[1][whichSound]] + 2, volumeAssigner());

	}
	
																													/*for (int i = 0; i <= 127; i++) {
																														SDL_Delay(1000);
																														tsf_note_off(soundFont, 29, i);
																														tsf_note_on(soundFont, 29, 98, 1.0f);
																														std::cout << "\nThis is note ";
																														std::cout << i;
																													}
																													*/
																													/* this part of the code is for looping through and getting the entire list of instruments
																													for (i = 0; i < tsf_get_presetcount(soundFont); i++)
																													{
		
																														printf("Play note %d with preset #%d '%s'\n", Notes[i % 7], i, tsf_get_presetname(soundFont, i));
																														tsf_note_off(soundFont, i - 1, Notes[(i - 1) % 7]);
																														tsf_note_on(soundFont, i, Notes[i % 7], 1.0f);
																														SDL_Delay(1);
																													}
																													*/
}

void endSound()
{
	for (int i = 0; i < 10; i++)
	{
		if (clock() >= playedSounds[0][i] + 1500)
		{
			/*std::cout << "Played sound note: ";
			std::cout << playedSounds[1][i] << std::endl;
			

			std::cout << "TURN OFF";*/
			tsf_note_off(soundFont, 29, notes[playedSounds[1][i] - 2]);
			tsf_note_off(soundFont, 29, notes[playedSounds[1][i]]);
			tsf_note_off(soundFont, 29, notes[playedSounds[1][i] + 2]);
			playedSounds[1][i] = 0;
		}
	}
}

int start_Sound() {
	// Define the desired audio output format we request
	SDL_AudioSpec OutputAudioSpec;
	OutputAudioSpec.freq = 44100;
	OutputAudioSpec.format = AUDIO_F32;
	OutputAudioSpec.channels = 2;
	OutputAudioSpec.samples = 4096;
	OutputAudioSpec.callback = AudioCallback;

	// Initialize the audio system
	if (SDL_AudioInit(TSF_NULL) < 0)
	{
		fprintf(stderr, "Could not initialize audio hardware or driver\n");
		return 1;
	}

	// Load the SoundFont from a file
	soundFont = tsf_load_filename("Soundfont1.sf2");
	if (!soundFont)
	{
		fprintf(stderr, "Could not load SoundFont\n");
		return 1;
	}

	// Set the SoundFont rendering output mode
	tsf_set_output(soundFont, TSF_STEREO_INTERLEAVED, OutputAudioSpec.freq, 0);

	// Request the desired audio output format
	if (SDL_OpenAudio(&OutputAudioSpec, TSF_NULL) < 0)
	{
		fprintf(stderr, "Could not open the audio hardware or the desired audio output format\n");
		return 1;
	}

	// Start the actual audio playback here
	// The audio thread will begin to call our AudioCallback function
	//Interval for guitar 29 starts at 23 to 126
	//Interval for guitar 30 starts at 0 to 126


	SDL_PauseAudio(0);
	if (soundLoad == true) {
		tsf_note_on(soundFont, 30, 60, 0.0f);
			std::cout << "Sound is loaded \n";
		soundLoad = false;
	}
	return 0;
}
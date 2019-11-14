#include "Sound.h";
#define TSF_IMPLEMENTATION
#include "tsf.h"
#include <string>
#include <queue>

using namespace std;

queue <int> soundQueue;
bool soundLoad = true;
int counterEnd = 2;

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

void playNote()
{
	//These three lines below play the three notes that make up the cord for each section
	tsf_note_on(soundFont, 29, playedSounds[1][counterStart], 0.8f);
	soundQueue.push(playedSounds[2][counterStart] + 1000);
	
	if (counterStart == 1) {
		soundQueue.pop();
		soundQueue.push(playedSounds[2][counterStart / 9 + 1000]);
	}
}

void stopNote() {
	if (soundQueue.empty() == false) {
		if (clock() >= soundQueue.front()) {
			tsf_note_off(soundFont, 29, playedSounds[1][counterEnd]);
			cout << "CounterEnd: " << counterEnd << "\n";
			soundQueue.pop();
			counterEnd++;
			if (counterEnd >= 19) {
				counterEnd = 2;
			}
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